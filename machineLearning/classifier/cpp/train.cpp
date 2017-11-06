// Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string>

// Testes do tempo de execucao
#include <ctime>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include "opencv2/objdetect.hpp"

// TinyDir
#include "extra_libs/tinydir.h"

using namespace std;
using namespace cv;

// Rotulos dos arquivos de treino
vector<int> labels; 
vector<string> trainingFilenames;

//Pega os arquivos e teste e salva os rotulos/arquvios em uma classe vector
void getsTrainingFiles(){
    
        //Abre o diretorio que contem as imagens 
        tinydir_dir training_root_dir;
        tinydir_open(&training_root_dir, "training_files");
    
        // itera pelo diretorio 
        while (training_root_dir.has_next){
            // pega o arquivo
            tinydir_file file;
            tinydir_readfile(&training_root_dir, &file);
    
            // se for um diretorio 
            if (file.is_dir){
    
                string numbersDirName = file.name;
    
                // pula . / .. / .DS_Store (OSX)
                if (numbersDirName != "." && numbersDirName != ".." && numbersDirName != ".DS_Store"){
    
                    // atoi nao é muito seguro, porem suficiente para testes 
                    int currentLabel = atoi(file.name);
    
                    // pega o diretorio com os aquivos de numeros
                    numbersDirName.insert(0, "training_files/");
    
                    // abre o diretorio que contem os numeros
                    tinydir_dir training_number_dir;
                    tinydir_open(&training_number_dir, numbersDirName.c_str());
    
                    // itera pelo diretorio
                    while (training_number_dir.has_next) {
                        //pega o aquivo
                        tinydir_file trainingJpgFile;
                        tinydir_readfile(&training_number_dir, &trainingJpgFile);
    
                        // pega o nome
                        string trainingJpgFileName = trainingJpgFile.name;
    
                        // pula . / .. / .DS_Store (OSX)
                        if (trainingJpgFileName != "." && trainingJpgFileName != ".." && trainingJpgFileName != ".DS_Store"){
    
                            // diretorio foi iterado completamente
                            trainingJpgFileName.insert(0, numbersDirName + "/");
    
                            //salva  o nome do arquivo de treinamento e seu rotulo
                            trainingFilenames.push_back(trainingJpgFileName);
                            labels.push_back(currentLabel);
                        }
    
                        // pega o proximo arquivo
                        tinydir_next(&training_number_dir);
                    }
    
                    // fecha o diretorio
                    tinydir_close(&training_number_dir);
                }
            }
    
            //pega o proximo arquivo
            tinydir_next(&training_root_dir);
        }
    
    // fecha o diretorio
    tinydir_close(&training_root_dir);
}

HOGDescriptor hog(
    Size(300,300), //winSize, tamanho das imagens
    Size(40,40), //blocksize, lida com variacoes de iluminacao (2 x cellSize - normalmente)
    Size(20,20), //blockStride, controla o grau de normalização do contraste (0.5 x blockSize)
    Size(20,20), //cellSize, tamanho da descritor que é escolhido com base na escala dos recursos importantes para fazer a classificação 
             9, //nbins
              1, //derivAper
             -1, //winSigma
              0, //histogramNormType
            0.2, //L2HysThresh
              1,//gammal correction
              64,//nlevels=64
              1//Use signed gradients 
);

//Cria os descritores HOG das imagens
void createTrainHOG(vector<vector<float>> &trainHOG, vector<string> trainingFilenames){

    for (int index = 0; index < trainingFilenames.size(); index++){
        // le a imagem(grayscale)
        Mat imgMat = imread(trainingFilenames[index], 0);

        vector<float> descriptors;
        hog.compute(imgMat, descriptors);
        trainHOG.push_back(descriptors);
    }
    
}

//converte os descritores em matrizes
void convertVectortoMatrix(vector<vector<float>> &trainHOG, Mat &trainMat, int descriptor_size){
    for(int i = 0;i<trainHOG.size();i++){
        for(int j = 0;j<descriptor_size;j++){
           trainMat.at<float>(i,j) = trainHOG[i][j]; 
        }
    }
}

//Mostra os parametros da SVM
void SVMParams(ml::SVM *svm){
    cout << "Kernel type     : " << svm->getKernelType() << endl;
    cout << "Type            : " << svm->getType() << endl;
    cout << "C               : " << svm->getC() << endl;
    cout << "Degree          : " << svm->getDegree() << endl;
    cout << "Nu              : " << svm->getNu() << endl;
    cout << "Gamma           : " << svm->getGamma() << endl;
}

//Todas as ações da SVM
void SVMtrain(Mat &trainMat,Mat &labelsMat){    
    // Configura a SVM
    // 'Seta' os parametros(optimal(ish)) da SVM's    
    //Kernel do tipo polinomial de grau 3 (best one so far)
    Ptr<ml::SVM> svm = cv::ml::SVM::create();
    svm->setKernel(ml::SVM::POLY);
	svm->setType(ml::SVM::C_SVC);
    svm->setC(12.5);
    svm->setDegree(3);
    svm->setGamma(1e-05);
    /*
    best:
    Numero de classificacoes: 57
    Corretas:  34 (59.6491%)
    Erradas: 23 (40.3509%)
    */
    
    /*
    //Kernel do tipo RBF (nao apresentou bons resultados)
    Ptr<ml::SVM> svm = ml::SVM::create();
    svm->setType(ml::SVM::C_SVC);
    svm->setKernel(ml::SVM::RBF);
    svm->setGamma(0.50625);
    svm->setC(12.5);
    */

    /*
    //kernel do tipo CHI2
    Ptr<ml::SVM> svm = ml::SVM::create();
    svm->setType(ml::SVM::C_SVC);
    svm->setKernel(ml::SVM::CHI2);
    //parametros do auto train
    svm->setC(2.5);
    svm->setGamma(1e-5);
    */
    /*
    best:
    Numero de classificacoes: 57
    Corretas:  19 (33.3333%)
    Erradas: 38 (66.6667%)
    */
    
    //Treina o classificador 
    int i = clock();
    cout << "Treinando o classificador ...\n";
    svm->train(trainMat, ml::ROW_SAMPLE, labelsMat);
    //svm->trainAuto(trainingMat, ml::ROW_SAMPLE, labelsMat);
    int f = clock();
    cout << "O treinamento levou " << (f-i)/(float)CLOCKS_PER_SEC << "s\n";

    // Salva a SVM
    cout << "Salvando a SVM ...\n";
    svm->save("HOG_RATS.yml");
    cout <<  endl;
    SVMParams(svm);
}


int main(int argc, char **argv){
    cout << "******Classificacao de Imagens******\n";

    cout << "Adquirindo arquivos ...\n";
    // pega os arquivos de treino
    getsTrainingFiles();

    cout << "Criando os descritores HOG ...\n";
    vector<vector<float>> trainHOG;    
    createTrainHOG(trainHOG, trainingFilenames);

    int descriptor_size = trainHOG[0].size();
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    Mat trainMat(trainHOG.size(),descriptor_size,CV_32FC1);
    convertVectortoMatrix(trainHOG, trainMat, descriptor_size);

    //Processa os rotulos 
    int labelsArray[labels.size()];    
    // itera pelos rotulos
    for (int index = 0; index < labels.size(); index++){
        labelsArray[index] = labels[index];
    }
    
    Mat labelsMat(labels.size(), 1, CV_32S, labelsArray);

    SVMtrain(trainMat, labelsMat);

    return 0;    
}
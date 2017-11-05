// Bibliotecas Padrao
#include <iostream>
#include <iomanip>  
#include <vector>
#include <string>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include "opencv2/objdetect.hpp"

// TinyDir
#include "extra_libs/tinydir.h"

// Testes do tempo de execucao
#include <ctime>

using namespace std;
using namespace cv;

// Rotulos dos arquivos de treino
vector<int> expectedLabels;
vector<int> predictedLabels;
vector<string> testFileNames;

//Pega os arquivos e teste e salva os rotulos/arquvios em uma classe vector
void getTestFiles(){

    //Abre o diretorio que contem as imagens
    tinydir_dir test_root_dir;
    tinydir_open(&test_root_dir, "test_files");

    // iterate over directories
    while (test_root_dir.has_next){
        // pega o arquivo
        tinydir_file file;
        tinydir_readfile(&test_root_dir, &file);

        // se for um diretorio
        if (file.is_dir){

            string numbersDirName = file.name;

            // pula . / .. / .DS_Store (OSX)
            if (numbersDirName != "." && numbersDirName != ".." && numbersDirName != ".DS_Store"){

                // atoi nao é muito seguro, porem suficiente para testes
                int currentLabel = atoi(file.name);

                // pega o diretorio com os aquivos de numeros
                numbersDirName.insert(0, "test_files/");

                // abre o diretorio que contem os numeros
                tinydir_dir test_number_dir;
                tinydir_open(&test_number_dir, numbersDirName.c_str());

                // itera pelo diretorio
                while (test_number_dir.has_next){
                    //pega o aquivo
                    tinydir_file testJpgFile;
                    tinydir_readfile(&test_number_dir, &testJpgFile);

                    // pega o nome
                    string testJpgFileName = testJpgFile.name;

                    // pula . / .. / .DS_Store (OSX)
                    if (testJpgFileName != "." && testJpgFileName != ".." && testJpgFileName != ".DS_Store"){

                        // diretorio foi iterado completament
                        testJpgFileName.insert(0, numbersDirName + "/");

                        //salva  o nome do arquivo de teste e seu rotulo
                        testFileNames.push_back(testJpgFileName);
                        expectedLabels.push_back(currentLabel);
                    }

                    // pega o proximo arquivo
                    tinydir_next(&test_number_dir);
                }

                // fecha o diretorio
                tinydir_close(&test_number_dir);
            }
        }

        // pega o proximo arquivo
        tinydir_next(&test_root_dir);
    }

    // close directory
    tinydir_close(&test_root_dir);
}

//Cria o descritor HOG
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
void createTestHOG(vector<vector<float>> &testHOG, vector<string> testFileNames){
    
    for (int index = 0; index < testFileNames.size(); index++){
        // le a imagem(grayscale)
        Mat imgMat = imread(testFileNames[index], 0);

        vector<float> descriptors;
        hog.compute(imgMat, descriptors);
        testHOG.push_back(descriptors);
    }
        
}

//converte os descritores em matrizes
void convertVectortoMatrix(vector<vector<float>> &testHOG, Mat &testMat, int descriptor_size){

    for(int i = 0;i<testHOG.size();i++){
        for(int j = 0;j<descriptor_size;j++){
            testMat.at<float>(i,j) = testHOG[i][j]; 
        }
    }

}


void SVMtest(Mat &testMat, Mat &testResponse){

    //Carrega a SVM
    cout << "Carregando a svm ...\n";
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("HOG_RATS.yml");

    svm->predict(testMat, testResponse); 
}

void SVMevaluate(Mat &testResponse, vector<int> expectedLabels){
    
    // Informacoes
    int totalClassifications = 0;
    int totalCorrect = 0;

    for(int i = 0; i < testResponse.rows; i++){
        cout << "Predito: "<< setw(2) << testResponse.at<float>(i,0) << " | Esperado: " << expectedLabels[i] << endl;
        if(testResponse.at<float>(i,0) == expectedLabels[i]){
            totalCorrect++;
        } 
        totalClassifications++;
    }
    
    int totalWrong = totalClassifications - totalCorrect;
    
    float percentageCorrect = ((float)totalCorrect / totalClassifications) * 100;
    float percentageIncorrect = 100 - percentageCorrect;
    
    cout << endl;
    cout << "Numero de classificacoes: " << totalClassifications << endl;
    cout << "Corretas:  " << totalCorrect << " (" << percentageCorrect << "%)" << endl;
    cout << "Erradas: " << totalWrong << " (" << percentageIncorrect << "%)" << endl;
    cout << endl;
    
    
}

int main(int argc, char **argv){
    cout << "******Testando o classificador******\n";
    
    cout << "Adquirindo arquivos ...\n";
    //Pega os arquivos de teste
    getTestFiles();

    cout << "Criando os descritores HOG ...\n";
    vector<vector<float>> testHOG;
    createTestHOG(testHOG, testFileNames);

    int descriptor_size = testHOG[0].size();
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    Mat testMat(testHOG.size(),descriptor_size,CV_32FC1);
    convertVectortoMatrix(testHOG, testMat, descriptor_size);

    Mat testResponse;
    SVMtest(testMat, testResponse);
        
    SVMevaluate(testResponse, expectedLabels);
    
    return 0;
}

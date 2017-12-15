// Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string> 

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;

// Rotulos dos arquivos
vector<int> trainLabels, testLabels; 

void load_images( String dirname, vector<Mat> &img_lst, int classe, vector<int> &labels){
    vector< String > files;
    glob( dirname, files );
    for ( size_t i = 0; i < files.size(); ++i ){
        //cout << files[i] << endl;
        Mat img = imread( files[i] ); // load the image
        img_lst.push_back( img );
        labels.push_back(classe);
    }    
}

void getsTrainingFiles(vector<Mat> &traningImages){
    for(int i=1;i<9;i++){
        load_images("training_files/"+to_string(i), traningImages, i, trainLabels);
    }
}

void getTestFiles(vector<Mat> &testImages){
    for(int i=1;i<9;i++){
        load_images("test_files/"+to_string(i), testImages, i, testLabels);
    }
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
              0//Use signed gradients 
);

//Cria os descritores HOG das imagens
void createHOG(vector<vector<float>> &trainHOG, vector<Mat> &images){
    for(int i=0; i<images.size(); i++){
        cvtColor( images[i], images[i], CV_BGR2GRAY );
        //elimina ruidos pelo metodo gaussiano 
        GaussianBlur(images[i], images[i], Size(3,3), 0, 0, BORDER_DEFAULT );
        vector<float> descriptors;
        hog.compute(images[i], descriptors);
        trainHOG.push_back(descriptors);  
    }      
}

//converte os descritores em uma unica matriz
void convertVectortoMatrix(vector<vector<float>> &HOG, Mat &Mat, int descriptor_size){
    for(int i = 0;i<HOG.size();i++){
        for(int j = 0;j<descriptor_size;j++){
           Mat.at<float>(i,j) = HOG[i][j]; 
        }
    }
}

int main(){
    cout << "******Descritores HOG******\n";
    FileStorage fs("ymls/hog/trainMat.yml", FileStorage::WRITE);
    FileStorage fs2("ymls/hog/testMat.yml", FileStorage::WRITE);

    cout << "Adquirindo arquivos ...\n";
    // pega os arquivos de treino e teste
    vector<Mat> traningImages, testImages;
    getsTrainingFiles(traningImages);
    getTestFiles(testImages);
   
    cout << "Criando os descritores HOG ...\n";

    //treinamento
    vector<vector<float>> trainHOG; 
    int i = clock();   
    createHOG(trainHOG, traningImages);

    int descriptor_size = trainHOG[0].size();
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    Mat trainMat(trainHOG.size(), descriptor_size, CV_32FC1);
    convertVectortoMatrix(trainHOG, trainMat, descriptor_size);
    int f = clock();
    cout << "\tA analise das imagens de treino levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s" << endl;


    fs << "labelsMat" << Mat(trainLabels);
    fs << "trainMat" << trainMat;    
    fs.release(); 

    //teste
    vector<vector<float>> testHOG;
    i = clock();
    createHOG(testHOG, testImages);

    Mat testMat(testHOG.size(),descriptor_size,CV_32FC1);
    convertVectortoMatrix(testHOG, testMat, descriptor_size);
    f = clock();
    cout << "\tA analise das imagens de teste levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s" << endl;


    fs2 << "testLabels" << testLabels;
    fs2 << "testMat" << testMat;
    fs2.release();

    cout << "Descitores HOG salvos com sucesso!\n";
    return 0;
}
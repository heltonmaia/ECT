//Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include "opencv2/objdetect.hpp"


using namespace std;
using namespace cv;


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
void createTestHOG(vector<vector<float>> &testHOG, Mat imgMat){
    
    vector<float> descriptors;
    hog.compute(imgMat, descriptors);
    testHOG.push_back(descriptors);
            
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


int main(int argc, char **argv){
    cout << "******Testando o classificador em uma unica imagem (img.jpg)******\n";
    //Carrega a SVM
    cout << endl <<"Carregando a svm..." << endl;
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("rats_everywhere.yml");

    // le a imagem (grayscale)
    Mat imgMat = imread("img.jpg", 0);

    vector<vector<float>> testHOG;
    createTestHOG(testHOG, imgMat);

    int descriptor_size = testHOG[0].size();
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    Mat testMat(testHOG.size(),descriptor_size,CV_32FC1);
    convertVectortoMatrix(testHOG, testMat, descriptor_size);


    Mat testResponse;
    SVMtest(testMat, testResponse);
    cout << "Predito -> " << testResponse << endl;
   
    return 0;
}
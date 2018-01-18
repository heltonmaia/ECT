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

// Testes do tempo de execucao
#include <ctime>

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
void createHOG(vector<vector<float>> &testHOG, Mat imgMat){
    
    vector<float> descriptors;
    hog.compute(imgMat, descriptors);
    testHOG.push_back(descriptors);
            
}

//Cria os descritores de contorno das imagens
void createEdges(Mat &edges, Mat imgMat){
    //trandforma a imagem para grayscale
    //cvtColor(imgMat, imgMat, CV_BGR2GRAY);

    //elimina ruidos pelo metodo gaussiano 
    GaussianBlur(imgMat, imgMat, Size(3,3), 0, 0, BORDER_DEFAULT );

    Canny(imgMat, edges, 80, 80, 3);

    
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
    cout << "******Descritores de uma unica imagem******\n";
    //Carrega a SVM
    //cout << endl <<"Carregando a svm..." << endl;
    //Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("ymls/hog/RATS_POLY.yml");

    // le a imagem (grayscale)
    Mat imgMat = imread("visualizations/1787.jpg", 0);

    cout << "HOG:\n";

    vector<vector<float>> HOG;
    
    int i = clock();
    createHOG(HOG, imgMat);
    int f = clock();
    cout << "Tempo para criação do descritor: " << (f-i)/(float)CLOCKS_PER_SEC << "s\n";


    int descriptor_size = HOG[0].size();
    cout << "Tamanho do descritor: " << descriptor_size << endl;

    Mat testMat(HOG.size(),descriptor_size,CV_32FC1);
    convertVectortoMatrix(HOG, testMat, descriptor_size);

    cout << "EDGES:\n";

    Mat edges;

    int j = clock();
    createEdges(edges, imgMat);
    int k = clock();
    cout << "Tempo para criação do descritor: " << (k-j)/(float)CLOCKS_PER_SEC << "s\n";

    cout << "Tamanho do descritor: " << edges.rows * edges.cols << endl;
   
    return 0;
}
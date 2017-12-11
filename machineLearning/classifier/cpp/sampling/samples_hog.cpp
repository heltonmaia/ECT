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

void load_images( String dirname, vector<Mat> &img_lst){
    vector<String> files;
    glob( dirname, files );
    for ( size_t i = 0; i < files.size(); ++i ){
        //cout << files[i] << endl;
        Mat img = imread( files[i] ); // load the image
        img_lst.push_back( img );
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
    FileStorage fs("sampleMat.yml", FileStorage::WRITE);
    
    cout << "Adquirindo arquivos ...\n";
    // pega os arquivos sem labels
    vector<Mat> sampleImages;

    load_images("figures/", sampleImages);
   
    cout << "Criando os descritores HOG ...\n";

    //Samples
    vector<vector<float>> sampleHOG; 
    int i = clock();   
    createHOG(sampleHOG, sampleImages);

    int descriptor_size = sampleHOG[0].size();
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    Mat sampleMat(sampleHOG.size(), descriptor_size, CV_32FC1);
    convertVectortoMatrix(sampleHOG, sampleMat, descriptor_size);
    int f = clock();
    cout << "\tA analise das imagens levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s" << endl;

    fs << "sampleMat" << sampleMat;    
    fs.release();     
    
    cout << "Descitores HOG salvos com sucesso!\n";
    return 0;
}
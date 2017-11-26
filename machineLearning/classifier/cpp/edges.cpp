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

//Cria os descritores de contorno das imagens
void createEdges(vector<Mat> &trainEdge, vector<Mat> &images){
    Mat image, gray, blurImage, edge, cedge;
    for(int i=0; i<images.size(); i++){
        cedge.create(images[i].size(), image.type());
        cvtColor(image, gray, COLOR_BGR2GRAY);

        blur(gray, blurImage, Size(3,3));
        // Run the edge detector on grayscale
        Canny(cedge, edge, 100, 300, 3);
        cedge = Scalar::all(0);
        images[i].copyTo(cedge, edge);
        trainEdge.push_back(cedge);        
    }

}
/*
//converte os descritores em matrizes
void convertVectortoMatrix(vector<Mat> &Edges, Mat &Mat, int descriptor_size){
    for(int i = 0;i<Edges.size();i++){
        for(int j = 0;j<descriptor_size;j++){
           Mat.at<float>(i,j) = Edges[i][j]; 
        }
    }
}
*/

int main(){
    cout << "******Descritores de Contorno******\n";
    FileStorage fs("ymls/trainMatEdges.yml", FileStorage::WRITE);
    FileStorage fs2("ymls/testMatEdges.yml", FileStorage::WRITE);

    cout << "Adquirindo arquivos ...\n";
    // pega os arquivos de treino e teste
    vector<Mat> traningImages, testImages;
    getsTrainingFiles(traningImages);
    getTestFiles(testImages);
   
    cout << "Criando os descritores de contorno...\n";

    //treinamento
    vector<Mat> trainEdge;    
    createEdges(trainEdge, traningImages);

    int descriptor_size = trainEdge[0].rows;
    cout << "Tamanho dos descritores: " << descriptor_size << endl;

    //Mat trainMatEdges(trainEdge.size(), descriptor_size, CV_32FC1);
    //convertVectortoMatrix(trainEdge, trainMatEdges, descriptor_size);

    fs << "labelsMat" << Mat(trainLabels);
    fs << "trainMat" << trainEdge;    
    fs.release(); 

    //teste
    vector<Mat> testEdge;
    createEdges(testEdge, testImages);

    //Mat testMatEdges(testEdge.size(),descriptor_size,CV_32FC1);
    //convertVectortoMatrix(testEdge, testMatEdges, descriptor_size);

    fs2 << "testLabels" << testLabels;
    fs2 << "testMat" << testEdge;
    fs2.release();


    cout << "Descitores HOG salvos com sucesso\n";
    return 0;
}
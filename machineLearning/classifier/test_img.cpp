//Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

// POSIX
#include <unistd.h>

using namespace std;
using namespace cv;


int main(int argc, char **argv){

    //Carrega a SVM
    cout << endl <<"Carregando a svm..." << endl;
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("rats_everywhere.yml");

    // le a imagem (grayscale)
    Mat imgMat = imread("img.jpg", 0);

    // converte de 2d para 1d
    Mat testMat = imgMat.clone().reshape(1, 1);
    testMat.convertTo(testMat, CV_32F);

    // Tenta prever qual numero foi desenhado 
    try{
        int predicted = svm->predict(testMat);

        cout << endl
                  << "Classe reconhecida -> " << predicted << endl
                  << endl;

        string notifyCmd = "notify-send -t 1000 Classe reconhecida: " + to_string(predicted);
        system(notifyCmd.c_str());
    }
    catch (Exception ex){
    }
}
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


int main(int argc, char **argv){

    //Carrega a SVM
    cv::Ptr<cv::ml::SVM> svm = cv::ml::StatModel::load<cv::ml::SVM>("classifier.yml");

    // le a imagem (grayscale)
    cv::Mat imgMat = cv::imread("img.png", 0);

    // converte de 2d para 1d
    cv::Mat testMat = imgMat.clone().reshape(1, 1);
    testMat.convertTo(testMat, CV_32F);

    // Tenta prever qual numero foi desenhado 
    try{
        int predicted = svm->predict(testMat);

        std::cout << std::endl
                  << "Numero reconhecido -> " << predicted << std::endl
                  << std::endl;

        std::string notifyCmd = "notify-send -t 1000 Recognized: " + std::to_string(predicted);
        system(notifyCmd.c_str());
    }
    catch (cv::Exception ex){
    }
}
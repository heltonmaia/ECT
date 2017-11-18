// Bibliotecas Padrao
#include <iostream>
#include <vector>

// Testes do tempo de execucao
#include <ctime>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

using namespace std;
using namespace cv;

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
    //Kernel do tipo polinomial de grau 3 (best one so far)
    
    Ptr<ml::SVM> svm = cv::ml::SVM::create();
    svm->setKernel(ml::SVM::POLY);
	svm->setType(ml::SVM::C_SVC);
    svm->setC(1);
    svm->setDegree(1);
    svm->setGamma(0.50625);
    
    /*
    //Kernel do tipo RBF 
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
    svm->setC(1);
    svm->setGamma(1e-5);
    */
    /*
    //kernel do tipo SIGMOID
    Ptr<ml::SVM> svm = ml::SVM::create();
    svm->setType(ml::SVM::C_SVC);
    svm->setKernel(ml::SVM::SIGMOID);
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
    svm->save("ymls/HOG_RATS_POLY.yml");
    cout <<  endl;
    SVMParams(svm);
}


int main(int argc, char **argv){
    cout << "******Classificacao de Imagens******\n";

    cout << "Lendo os dados ...\n";
    FileStorage fs("ymls/trainMat.yml", FileStorage::READ);
    Mat trainMat, labelsMat;
    fs["labelsMat"] >> labelsMat;
    fs["trainMat"] >> trainMat;
    fs.release(); 

    SVMtrain(trainMat, labelsMat);

    return 0;    
}
// Bibliotecas Padrao
#include <iostream>
#include <iomanip>  
#include <vector>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

#include "extra_libs/evaluation.hpp"

// Testes do tempo de execucao
#include <ctime>

using namespace std;
using namespace cv;

void SVMpredict(Mat &testMat, Mat &testResponse){

    //Carrega a SVM
    cout << "Carregando a svm ...\n";
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("ymls/HOG_RATS_POLY.yml");

    cout << "Classificando ...\n";
    svm->predict(testMat, testResponse); 
    cout << "Salvando as classificacoes ...\n";
    FileStorage fs("ymls/testResponse.yml", FileStorage::WRITE);
    fs << "testResponse" << testResponse;
    fs.release(); 
}

void SVMevaluate(Mat &testResponse, vector<int> testLabels){
    
    // Informacoes
    int totalClassifications = 0, totalCorrect = 0, totalWrong = 0;

    for(int i = 0; i < testResponse.rows; i++){
        //cout << "Predito: "<< setw(2) << testResponse.at<float>(i,0) << " | Esperado: " << testLabels[i] << endl;
        if(testResponse.at<float>(i,0) == testLabels[i]){
            totalCorrect++;
        }else{
            totalWrong++;
        } 
        totalClassifications++;
    }
       
    float percentageCorrect = ((float)totalCorrect / totalClassifications) * 100;
    float percentageIncorrect = 100 - percentageCorrect;
    
    cout << endl;
    cout << "Numero de classificacoes: " << totalClassifications << endl;
    cout << "Corretas:  " << totalCorrect << " (" << percentageCorrect << "%)" << endl;
    cout << "Erradas: " << totalWrong << " (" << percentageIncorrect << "%)" << endl;
    cout << endl;
    
    
}

void in_n_out(vector<int> &in, vector<int> &out){
 
    cout << "[ ";
    for(int i=0; i<in.size(); i++){
        cout << in[i] << ", ";
    }
    cout << "]" <<endl;
    cout << "[ ";
    for(int i=0; i<in.size(); i++){
        cout << out[i] << ", ";
    }
    cout<< "]" <<endl;
    
}

void conf_mat(){
    vector<int> targets = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8};
    vector<int> outputs = { 1, 1, 1, 1, 1, 6, 2, 2, 2, 2, 3, 3, 4, 3, 3, 4, 4, 8, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 4};

    Confusion confusion = Confusion(targets, outputs);
    confusion.print();

    Evaluation evaluation = Evaluation(confusion);
    evaluation.print();
}

int main(int argc, char **argv){
    cout << "******Testando o classificador******\n";

    cout << "Lendo os dados ...\n";
    FileStorage fs("ymls/testMat.yml", FileStorage::READ);

    vector<int> testLabels;
    fs["testLabels"] >> testLabels;

    Mat testMat, testResponse;
    fs["testMat"] >> testMat;
    fs.release(); 
    
    //classifica as imagens de teste
    SVMpredict(testMat, testResponse);
   
    //avalia as classificações feitas
    SVMevaluate(testResponse, testLabels);

    //Métricas 
    vector<int> outputs;
    for(int i=0;i<testResponse.rows;i++){
        outputs.push_back(testResponse.at<float>(i,0) );
    }

    conf_mat();

    return 0;
}

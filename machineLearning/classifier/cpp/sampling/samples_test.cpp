// Bibliotecas Padrao
#include <iostream> 
#include <vector>
#include <cstdlib>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

// Testes do tempo de execucao
#include <ctime>

using namespace std;
using namespace cv;

void SVMpredict(Mat &testMat, Mat &testResponse){

    //Carrega a SVM
    cout << "Carregando a svm ...\n";
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("RATS_POLY.yml");

    cout << "Classificando ...\n";
    svm->predict(testMat, testResponse); 
    cout << "Salvando as classificacoes ...\n";
    FileStorage fs("testResponse.yml", FileStorage::WRITE);
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

int breakThing(){
    return 0;
}

int main(int argc, char **argv){
    cout << "******Classificador******\n";
    
    cout << "Lendo os dados ...\n";
    FileStorage fs("sampleMat.yml", FileStorage::READ);

    Mat sampleMat, testResponse;
    fs["sampleMat"] >> sampleMat;
    fs.release(); 
    
    //classifica as imagens de teste
    int i = clock();
    SVMpredict(sampleMat, testResponse);
    int f = clock();
    cout << "A classficacao levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s\n";

    vector<String> files;
    glob( "figures/", files );

    for(int i = 0; i < testResponse.rows; i++){
        //cout << "Predito: "<< setw(2) << testResponse.at<float>(i,0) << " | Esperado: " << testLabels[i] << endl;
        string str = "cp "+ files[i] +" classifications/"+ to_string(int(testResponse.at<float>(i,0)));
        const char * c = str.c_str();
        system(c);
    }
    
    breakThing();
    return 0;
}

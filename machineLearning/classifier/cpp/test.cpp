// Bibliotecas Padrao
#include <iostream> 
#include <vector>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

// Testes do tempo de execucao
#include <ctime>

using namespace std;
using namespace cv;

void SVMpredict(Mat &testMat, Mat &testResponse, string &metodo){

    //Carrega a SVM
    cout << "Carregando a SVM ...\n";
    Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("ymls/"+ metodo +"/RATS_POLY.yml");

    cout << "Classificando imagens de teste ...\n";
    svm->predict(testMat, testResponse); 
    cout << "Salvando as classificacoes ...\n";
    FileStorage fs("ymls/"+ metodo +"/testResponse.yml", FileStorage::WRITE);
    fs << "testResponse" << vector<int>(testResponse);
    fs.release(); 
}

void SVMevaluate(Mat &testResponse, vector<int> testLabels, vector<String> names, vector<String> &wrongs){
    
    // Informacoes
    int totalClassifications = 0, totalCorrect = 0, totalWrong = 0;

    for(int i = 0; i < testResponse.rows; i++){
        //cout << "Predito: "<< setw(2) << testResponse.at<float>(i,0) << " | Esperado: " << testLabels[i] << endl;
        if(testResponse.at<float>(i,0) == testLabels[i]){
            totalCorrect++;
        }else{
            totalWrong++;
            wrongs.push_back( names[i] );
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

int main(int argc, char **argv){
    cout << "******Testando o classificador******\n";

    string metodo = argv[1];

    cout << "Lendo os dados ...\n";

    FileStorage fs("ymls/"+ metodo +"/testMat.yml", FileStorage::READ);

    vector<int> testLabels;
    fs["testLabels"] >> testLabels;

    Mat testMat, testResponse;
    fs["testMat"] >> testMat;
    fs.release(); 

    FileStorage fs2("ymls/"+ metodo +"/fileNames.yml", FileStorage::READ);
    vector<String> fileNames;
    fs2["test_files"] >> fileNames;
    fs2.release(); 
    
    //classifica as imagens de teste
    int i = clock();
    SVMpredict(testMat, testResponse, metodo);
    int f = clock();
    cout << "A classficacao levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s\n";
    
    vector<String> wrongs;
    //avalia as classificações feitas
    SVMevaluate(testResponse, testLabels, fileNames, wrongs);

    FileStorage fs3("ymls/"+ metodo +"/testResponse.yml", FileStorage::APPEND);
    fs3 << "wrongs" << wrongs;
    fs3.release();     

    return 0;
}

// Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string>

// Testes do tempo de execucao
 #include <ctime>
 #include <cmath>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;

// Rotulos dos arquivos
vector<int> trainLabels, testLabels; 

vector<float>times;

void load_images( String dirname, vector<Mat> &img_lst, int classe, vector<int> &labels){
    vector< String > files;
    glob( dirname, files );
    for ( size_t i = 0; i < files.size(); ++i ){
        //cout << files[i] << endl;
        Mat img = imread(files[i]); // load the image
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
void createEdges(Mat &edges, vector<Mat> &images){
     int start, end;   
    for(int index=0; index < images.size(); index++){

        start = clock();
        //trandforma a imagem para grayscale
        cvtColor(images[index], images[index], CV_BGR2GRAY);

        //elimina ruidos pelo metodo gaussiano 
        GaussianBlur(images[index], images[index], Size(3,3), 0, 0, BORDER_DEFAULT );
    
        Canny(images[index], images[index], 80, 80, 3);

        //usando o operador lapaciano com o fato de que a segunda derivada nas extremidades do objeto sera zero
        //Laplacian(images[i], edge, CV_16S, 3, 1, 0 , BORDER_DEFAULT);

        int ii = 0; //coluna atual
        
        for (int i = 0; i < images[index].rows; i++){
            for (int j = 0; j < images[index].cols; j++){
                edges.at<float>(index, ii++) = images[index].at<uchar>(i, j);
            }
        } 
        
        end = clock();
        times.push_back( (end-start)/(float)CLOCKS_PER_SEC );                  
    }

}

void showTimes() {
    cout << "Times: [ \n";
    for(auto i : times){
        cout << '\t' << i << '\n';
    }
    cout << "] \n";
}

void timeStatistics(float mean){

    FileStorage timesFile("ymls/edges/timesFile.yml", FileStorage::WRITE);

    float variance = 0.0;
    for(auto i : times){
        variance += ( pow((i - mean), 2) ) / (float)times.size();
    }
    cout << "\nStatistics"
         << "\nVariance: " << variance
         << "\nSTD: " << sqrt(variance) << endl;  

    timesFile << "variance" << variance
        << "std" << sqrt(variance)
        << "times" << times;
}

int main(){
    cout << "******Descritores de Contorno******\n";
    FileStorage fs("ymls/edges/trainMat.yml", FileStorage::WRITE);
    FileStorage fs2("ymls/edges/testMat.yml", FileStorage::WRITE);

    cout << "Adquirindo arquivos ...\n";
    // pega os arquivos de treino e teste
    vector<Mat> traningImages, testImages;
    getsTrainingFiles(traningImages);
    getTestFiles(testImages);
    int imgArea = 300 * 300;
   
    cout << "Criando os descritores de contorno:\n";

    //treinamento
    Mat trainEdge(traningImages.size(), imgArea, CV_32FC1); 
    int i = clock();
    createEdges(trainEdge, traningImages);
    int f = clock();
    float sumTimes = (f-i)/(float)CLOCKS_PER_SEC; 
    cout << "\tA analise das imagens de treino levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s" << endl;

    fs << "labelsMat" << Mat(trainLabels);
    fs << "trainMat" << trainEdge;    
    fs.release(); 

    //teste
    Mat testEdge(testImages.size(), imgArea, CV_32FC1);
    i = clock();
    createEdges(testEdge, testImages);
    f = clock();
    sumTimes += (f-i)/(float)CLOCKS_PER_SEC;
    cout << "\tA analise das imagens de teste levou: " << (f-i)/(float)CLOCKS_PER_SEC << "s" << endl;

    fs2 << "testLabels" << testLabels;
    fs2 << "testMat" << testEdge;
    fs2.release();

    cout << "Descitores de contorno salvos com sucesso!\n";
    
    //Mostra o resultado de uma imagem
    /*
    imshow("Contorno",testImages[10]);
    waitKey(0);
    */

    timeStatistics( sumTimes/1800.0 );

    return 0;
}
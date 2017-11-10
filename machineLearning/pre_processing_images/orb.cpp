#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Point zero(0,0);

    //declaração das variaveis utilizadas
    int frame,frame_inicial,frame_final, porcentagem=0, totalkeys=0, cont=0;

    //cria o arquivo arquivo Keypoints.yml e lê o coordenadas.yml
    FileStorage fs("results/keypoints_orb.yml", FileStorage::WRITE);
    FileStorage fsd("results/descriptors_orb.yml", FileStorage::WRITE);
   FileStorage fs2("results/coordenadas.yml", FileStorage::READ);

    //lê o local onde se encontra os dados salvos
    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_and = features.end();
    FileNodeIterator it2=it_and;
    it2--;

    //variaveis iniciais da arena e primeiro frame
    frame_final=(int)(*it2)["frame"];
    it++;
    frame=(int)(*it)["frame"];
    frame_inicial=frame;

    char nome[30];
    sprintf(nome,"figures/%d.jpg",frame);
    Mat img=imread(nome);
    Mat thres;

    do
    {   
	//calcula a porcentagem para do procedimento nas imagens
        if(porcentagem<((frame-frame_inicial)*100)/(frame_final-frame_inicial))
           cout<<((frame-frame_inicial)*100)/(frame_final-frame_inicial)<<"% \n";
        porcentagem=((frame-frame_inicial)*100)/(frame_final-frame_inicial);
	
	

	//declaração dos keypoints 
        std::vector<KeyPoint> kp;

	//coverte para preto e branco e aplica um tratamento na imagem para retirada do contorno
        cvtColor(img,img,CV_BGR2GRAY);
        threshold(img, thres, 110, 255, CV_THRESH_BINARY | CV_THRESH_TRUNC);

        //detecta os keypoints
        Mat descriptors;
        OrbFeatureDetector detector(700, 1.2f, 6 , 75, 0);
        OrbDescriptorExtractor extractor;
        detector.detect(thres, kp);
        detector.compute(thres, kp, descriptors);
        Mat out;
   
        
	//escreve os keypoints na imagem
        char keys[20], des[20];
        sprintf(keys,"keypoints_%d",frame);
        sprintf(des,"descriptors_%d",frame);
        
        write(fs, keys, kp);
        write(fsd, des, descriptors);
       
        drawKeypoints(img, kp, out, Scalar::all(255));
        if (waitKey(30) >= 0)
            break;

        char nome[30];
        sprintf(nome,"figures/%d.jpg",frame);
        img=imread(nome);
      
       it++;
        frame=(int)(*it)["frame"];
    }
    while (it!=it_and);
    return 0;
  
    //fechamento os arquivos 
    fs.release();
   fs2.release();
}

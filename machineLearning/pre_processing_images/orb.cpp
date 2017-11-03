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
    int x,y,frame, xini,yini, xfim,yfim, parada, tam_cortex,tam_cortey,frame_inicial,frame_final, porcentagem=0;
    int adicionalx, adicionaly;
    //cria o arquivo arquivo Keypoints.yml e lê o coordenadas.yml
    FileStorage fs("results/keypoints_orb.yml", FileStorage::WRITE);
    FileStorage fsd("results/descriptors_orb.yml", FileStorage::WRITE);
    FileStorage fs2("results/coordenadas.yml", FileStorage::READ);

    //lê o local onde se encontra os dados salvos
    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    FileNodeIterator it2=it_end;
    it2--;

    //variaveis iniciais da arena e primeiro frame
    frame_final=(int)(*it2)["frame"];
    xini= (int)(*it)["quadr_x1"];
    yini= (int)(*it)["quadr_y1"];
    xfim= (int)(*it)["quadr_x2"];
    yfim= (int)(*it)["quadr_y2"];
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
	
	//variaveis iniciais do corte e o tamanho feito
        x= (int)(*it)["x"];
        y= (int)(*it)["y"];
        tam_cortex=(int)(*it)["tam_cortex"];
        tam_cortey=(int)(*it)["tam_cortex"];
        adicionalx=(int)(*it)["adicional_x"];
        adicionaly=(int)(*it)["adicional_y"];

	//declaração dos keypoints 
        std::vector<KeyPoint> kp;

	//coverte para preto e branco e aplica um tratamento na imagem para retirada do contorno
        cvtColor(img,img,CV_BGR2GRAY);
        threshold(img, thres, 100, 255, CV_THRESH_BINARY | CV_THRESH_TRUNC);

        //detecta os keypoints
        Mat descriptors;
        OrbFeatureDetector detector(700, 1.2f, 8, 31, 0);
        OrbDescriptorExtractor extractor;
        detector.detect(thres, kp);
        detector.compute(thres, kp, descriptors);
        Mat out;
   
        //verifica se os keypoints estao fora da arena, se verdadeiro os elimina
        for(int i=0; i<kp.size(); i++)
        {
            if((y+tam_cortey-yfim)>=0 || (x+tam_cortex-xfim)>=0 || x<=xini || y<=yini)
            {

                if (kp[i].pt.x<(adicionalx + xini-x) || kp[i].pt.x>(adicionalx + tam_cortex-(x+tam_cortex-xfim)))kp[i].pt=zero; 

 	        if (kp[i].pt.y<(adicionaly + yini-y+1) || kp[i].pt.y>( tam_cortey-(y+tam_cortey-yfim)-10))kp[i].pt=zero;



            }
        }

	//escreve os keypoints na imagem
        char keys[20], des[20];
        sprintf(keys,"keypoints_%d",frame);
        sprintf(des,"descriptors_%d",frame);
        
        write(fs, keys, kp);
        write(fsd, des, descriptors);
        
        drawKeypoints(img, kp, out, Scalar::all(255));
        sprintf(nome,"fotorb/%d.jpg",frame);		
        imwrite(nome, out); //salva a imagem com os pontos

        if (waitKey(30) >= 0)
            break;

        char nome[30];
        sprintf(nome,"figures/%d.jpg",frame);
        img=imread(nome);
        parada=frame;
        it++;
        frame=(int)(*it)["frame"];

    }
    while (it!=it_end);

    return 0;
  
    //fechamento os arquivos 
    fs.release();
    fs2.release();
}

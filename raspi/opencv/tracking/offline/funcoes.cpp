#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
#define MICRO_PER_SECOND 1000000

using namespace std;
using namespace cv;

//variaveis utilizadas
int blue=0, green=0, red=0, num_foto=1, Range_rgb=20;
int posicao[4]= {0}, coord=0,tam_total_final=300;
int xpos, ypos, frame_width, frame_height, regiao=0;

//variaveis utilizadas para condições especificas
bool gravar_video=false, gravar_vid_restrito=false, trava=false, foto=false, adcnlx=false,adcnly=false, direcionalx=true,direcionaly=true, canto=true;

//Matrizes das imagens utilizadas
Mat cameraFrame,frame_restrito, imagem_salva;


Point centro_massa,centro_orig, Rectp1, Rectp2;

//abre o video para captura
VideoCapture cap;

//variavel para salvament do video posterior
VideoWriter video;

//cria o arquivo para salvamento do dados
FileStorage fs;

void condicoes_esp_fot( int regiao, Mat mat)
{
    Mat saida;
    int adicionalx=0, adicionaly=0;
    adicionaly=tam_total_final-mat.rows;
    adicionalx=tam_total_final-mat.cols;
//conjunto de condiçoes para deixar o camundongo sempre no cento da imagem
    cout<< regiao<<endl;
    adicionaly=tam_total_final-mat.rows;
    adicionalx=tam_total_final-mat.cols;

    Mat completxy(mat.rows,adicionalx, CV_8UC3, Scalar(255,255,255));
    Mat completx(tam_total_final,adicionalx, CV_8UC3, Scalar(255,255,255));
    Mat complety(adicionaly,tam_total_final, CV_8UC3, Scalar(255,255,255));
    cout<<adicionalx<<" "<<adicionaly<<endl;
    switch(regiao)
    {
    case 1:
        hconcat(completxy,mat, saida);
        vconcat(complety,saida, saida);
        break;

    case 2:
        vconcat(complety,mat,saida);
        break;

    case 3:
        hconcat(mat,completxy, saida);
        vconcat(complety,saida, saida);
        break;

    case 4:
        hconcat(completx,mat, saida);
        break;

    case 5:
        hconcat(mat,completx, saida);
        break;

    case 6:
        hconcat(completxy,mat, saida);
        vconcat(saida,complety, saida);
        break;

    case 7:
        vconcat(mat,complety, saida);
        break;

    case 8:
        hconcat(mat,completxy, saida);
        vconcat(saida,complety, saida);
        break;

    case 9:
        vconcat(complety,mat, saida);
        break;

    case 10:
        vconcat(mat,complety, saida);
        break;

    case 11:
        vconcat(complety,mat, saida);
        break;

    case 12:
        vconcat(mat,complety, saida);
        break;

    case 13:
        hconcat(completx,mat, saida);
        break;

    case 14:
        hconcat(mat,completx, saida);
        break;

    case 15:
        hconcat(completx,mat, saida);
        break;

    case 16:
        hconcat(mat,completx, saida);
        break;
    }

// salva a foto
    char nome[30];
    sprintf(nome,"figures/%d.jpg",num_foto);
    if(regiao==0)
    {
        imwrite( nome, mat );

    }
    else imwrite( nome, saida );
}


//função relacionada a detecção do mouse
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
    if (event == EVENT_RBUTTONDOWN)
    {
        Vec3f intensity = frame_restrito.at<Vec3b>(y, x);
        blue = intensity.val[0];
        green = intensity.val[1];
        red = intensity.val[2];
        gravar_video=true;
        video.open("video/video_resultado.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
    }
    //pega as posicoes de area desejada para rasteamento do rato
    if (event == EVENT_LBUTTONDOWN)
    {
        //coordenads iniciais e finais da arena
        posicao[coord]=x;
        coord++;
        posicao[coord]=y;
        coord++;

        if(coord==4)
        {
            gravar_vid_restrito=true;

            //Algumas variáveis que definem o tamanho e os limites dos frames utilizados para todo o processo
            xpos=posicao[2]-posicao[0];
            ypos=posicao[3]-posicao[1];

            //coordenads iniciais e finais da arena
            Rectp1.x=posicao[0];
            Rectp1.y=posicao[1];
            Rectp2.x=posicao[2];
            Rectp2.y=posicao[3];
            fs.open("results/coordenadas.yml", FileStorage::WRITE);
            //classe onde vai ser salvos os dados
            fs << "features" << "[";

            //posiçoes salvas
            fs  << "{:" <<"quadr_x1"<<posicao[0]<< "quadr_y1" << posicao[1] << "quadr_x2" << posicao[2] << "quadr_y2" << posicao[3]<< "}";


        }
    }
}

//função de modificação da imagem,onde ocorre uma varredura e seleção de pixels em determinado intervalo
// efeitos de redução de ruido, cálculo de centro de massa, e recorte da magem que será salva
void transform(Mat frame)
{
    Mat saida2, restrit_cor;
    cvtColor(frame,frame,CV_BGR2GRAY);
    threshold(frame, frame, 110, 255, CV_THRESH_BINARY | CV_THRESH_TRUNC);
    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz restrit_cor
    inRange(frame, Scalar(blue - Range_rgb, green - Range_rgb, red - Range_rgb), Scalar(blue + Range_rgb, green + Range_rgb, red + Range_rgb), restrit_cor);

    //efeitos para reduzir ruido
    erode(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
    dilate(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //retorna aos valores de rgb
    bitwise_and(frame, frame, saida2, restrit_cor = restrit_cor);

    //centro de massa
    Moments mu = moments(restrit_cor, true);

    centro_massa.x = mu.m10 / mu.m00;
    centro_massa.y = mu.m01 / mu.m00;

    //captura de imagens tam_total_finalxtam_total_final a partir da imagem original
    if(foto==true)
    {

        //Verifica a posição do corte e se ajusta para nao pegar fora do frame
        int tam_medio=150;
        int xcorte = posicao[0]+centro_massa.x-tam_medio;
        int ycorte = posicao[1]+centro_massa.y-tam_medio;
        int tam_cortex=tam_total_final, tam_cond_x=xcorte+tam_cortex;
        int tam_cortey=tam_total_final, tam_cond_y=ycorte+tam_cortey;
        cout<<" ini "<<ycorte<<" "<<xcorte<<" "<<posicao[0]<<" "<<posicao[1]<<" "<<posicao[2]<<" "<<posicao[3]<<endl;
        //Verifica a posição do corte e se ajusta para nao pegar fora do frame
        cout<< " antes" <<regiao<<endl;
        if(xcorte<posicao[0] && ycorte<=posicao[1] ) regiao=1;

        else if((xcorte+300)>posicao[2] && ycorte<posicao[1] ) regiao=3;

        else if((xcorte+300)>posicao[2] && (ycorte+300)>posicao[3] ) regiao=8;

        else if(xcorte<posicao[0] && (ycorte+300)>posicao[3] ) regiao=6;

        else if(xcorte<posicao[0] && ycorte>posicao[1] && ycorte<posicao[3] ) regiao=4;

        else if(ycorte<posicao[1] && xcorte>posicao[0] && xcorte<posicao[2] ) regiao=2;

        else if((xcorte+300)>posicao[2] && ycorte>posicao[1] && ycorte<posicao[3] ) regiao=5;

        else if((ycorte+300)>posicao[3] && xcorte>posicao[0] && xcorte<posicao[2] ) regiao=7;

        if(xcorte==posicao[0] && ycorte<posicao[1])regiao=9;
        else if(xcorte==posicao[0] && (ycorte+300)>posicao[3])regiao=10;

        if((xcorte+300)==posicao[2] && ycorte<posicao[1])regiao=11;
        else if((xcorte+300)==posicao[2] && (ycorte+300)>posicao[3])regiao=12;

        if(ycorte==posicao[1] && xcorte<posicao[0])regiao=13;
        else if(ycorte==posicao[1] && (xcorte+300)>posicao[2])regiao=14;

        if((ycorte+300)==posicao[3] && xcorte<posicao[0])regiao=15;
        else if((ycorte+300)==posicao[3] && (xcorte+300)>posicao[2])regiao=16;
        cout<< " depois" <<regiao<<endl;

        if(xcorte==posicao[0] || (xcorte+300)==posicao[2] || ycorte==posicao[1] || (ycorte+300)==posicao[3])imwrite("nova.jpg",cameraFrame);


        if(ycorte>(frame_height-tam_total_final) || ycorte>(posicao[3]-tam_total_final))
        {
            if(ycorte>(frame_height-tam_total_final))
            {
                tam_cortey=tam_total_final-(ycorte-(frame_height-tam_total_final))-(frame_height-posicao[3]);
            }
            else
            {
                tam_cortey=posicao[3]-ycorte;
            }
        }
        if(xcorte>(frame_width-tam_total_final) || xcorte>(posicao[2]-tam_total_final) )
        {
            if(xcorte>(frame_width-tam_total_final) )
            {
                tam_cortex=tam_total_final-(xcorte-(frame_width-tam_total_final))-(frame_width-posicao[2]);
            }
            else
            {
                tam_cortex=posicao[2]-xcorte;
            }
        }
        if(ycorte<0 || ycorte<=posicao[1])
        {
            if(ycorte<0 )
            {
                tam_cortey=tam_total_final+ycorte-posicao[1];
                ycorte=posicao[1];
            }
            else
            {
                tam_cortey=tam_total_final-(posicao[1]-ycorte);
                ycorte=posicao[1];
            }

        }
        if(xcorte<0 || xcorte<=posicao[0])
        {
            if(xcorte<0 )
            {
                tam_cortex=tam_total_final+xcorte-posicao[0];
                xcorte=posicao[0];
            }
            else
            {
                tam_cortex=tam_total_final+xcorte-posicao[0];
                xcorte=posicao[0];
            }

        }



        //recorte limitado ou nao pelas laterais da arena
        Mat imagem_Primaria = cameraFrame( Rect(xcorte,ycorte,tam_cortex,tam_cortey));

        //fs <<numero do frame<<" "<< x do corte << " " << y do corte <<tamanho do corte em x<< tamanho do corte em y<< endl;
        fs << "{:" <<"frame"<<num_foto<< "x" << xcorte << "y" << ycorte <<"largura"<<tam_cortex<<"altura"<<tam_cortey<< "regiao"<<regiao<<"}";
        condicoes_esp_fot( regiao, imagem_Primaria);
        regiao=0;



    }
}

//função de exibição da imagem capturada e ja modificada
void frame(Mat original)
{

    //seleciona uma parte indicada pelo usuario
    if(gravar_vid_restrito==true)
        frame_restrito = original( Rect(posicao[0],posicao[1],xpos,ypos) );

    transform(frame_restrito);
    namedWindow("original", 1);

    //posição do contro na imagem original
    centro_orig.x=centro_massa.x+posicao[0];
    centro_orig.y=centro_massa.y+posicao[1];

    //Pequeno circulo que marca o centro de massa
    circle(original, centro_orig, 3, Scalar(0, 0, 255), -1);

    //função responsável de gravar os videos
    if (gravar_video==true)
    {

        video.write(original);
    }

    //Retangulo que mostra a área onde acontece o tracking
    rectangle(original, Rectp1, Rectp2,Scalar(0, 0, 255),1, 8, 0);

    //exibe o video
    imshow("original", original);
}

//função principal, onde ocorre a captura da imagem
void principal(char *argv[])
{

    char nome_vid[50];
    sprintf(nome_vid,"%s",argv[1]);
    cap.open(nome_vid);

    //variaveis tamanho do video
    frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);


    cap >> cameraFrame;

    //mostra o primeiro frame, para o usuário poder selecionar a área do tracking
    if(!cameraFrame.empty())
        imshow("original",cameraFrame);
    else
    {
        cout <<  "Could not open the video file" << endl ;
    }
    while (true)
    {

        //contagem dos frames
        if(trava==true)num_foto++;

        //captura do frame
        if(trava==true) cap >> cameraFrame;

        //funcoes do mouse
        setMouseCallback("original", CallBackFunc, NULL);

        if(trava==true) frame(cameraFrame);
        char c = (char)waitKey(1);

        //esc clicada fecha o prog.
        if (c == 27)
            break;

        //play e pause do video
        if (c == 'p' || c=='P')
        {
            if(trava==true)trava=false;
            else trava=true;
        }
        //captura uma foto do camundongo
        if (c == 'f' || c=='F')foto=true;
        if (c == 'r' || c=='R')coord=0;
    }
    cap.release();
    video.release();
    fs << "]";
    // Closes all the windows
    destroyAllWindows();

    fs.release();
}

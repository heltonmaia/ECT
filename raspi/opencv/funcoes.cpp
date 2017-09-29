#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

int blue, green, red,fps, salvar=0;
bool gravar_video=false,gravar_vid_restrito=false,trava=false, foto=false;
Mat cameraFrame,frame_restrito;
int posicao[3][3], coord=0;
VideoCapture cap("/home/lucas/Downloads/vid.AVI");
ofstream myfile;

#define MICRO_PER_SECOND 1000000

//codigos de salvamento do video
int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
VideoWriter video("video_sem_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
VideoWriter video2("video_com_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));


//função de modificação da imagem
Mat transform(Mat frame)
{
    Mat frame2, mask;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz mask
    inRange(frame, Scalar(blue - 20, green - 20, red - 20), Scalar(blue + 20, green + 20, red + 20), mask);
    
    

    //efeitos para reduzir ruido
   erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
    dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    //retorna aos valores de rgb
    bitwise_and(frame, frame, frame2, mask = mask);
      
    //centro de massa
    Moments mu = moments(mask, true);
    Point center;
    center.x = mu.m10 / mu.m00;
    center.y = mu.m01 / mu.m00;

//captura de imagens 200x200 a partir da imagem origonal
if(foto==true){
Mat img = cameraFrame( Rect(posicao[0][0]+center.x-100,posicao[0][1]+center.y-100,200,200));
char nome[30];
sprintf(nome,"/home/lucas/Downloads/%d.jpg",salvar);
imwrite( nome, img );
salvar++;
//foto=false;

}

    if (gravar_video==true) {
      myfile << center.x << " " << center.y << endl;
        video.write(frame2);
    }
    //coloca um disco como ponto de centro de massa
    circle(frame2, center, 3, Scalar(0, 0, 255), -1);
    if (gravar_video==true)
        video2.write(frame2);

    return frame2;
}

//função de exibição da imagem capturada e ja modificada
void frame(Mat frame)
{

//seleciona uma parte indicada pelo usuario
if(gravar_vid_restrito==true){frame = frame( Rect(posicao[0][0],posicao[0][1],posicao[1][1]-posicao[0][0],posicao[1][2]-posicao[0][1]) );
}

    Mat Framevid = transform(frame);

    //exibe a imagem em conjunto com os frames
    putText(Framevid, format("FPS=%d ", fps), Point2f(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255, 255));

    imshow("Identificação", Framevid);
    imshow("original", frame);
}

//função relacionada a detecção do mouse
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
   //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
   

    if (event == EVENT_RBUTTONDOWN) {
        Vec3f intensity = cameraFrame.at<Vec3b>(y, x);
        blue = intensity.val[0];
        green = intensity.val[1];
        red = intensity.val[2];
gravar_video=true;
    }

//pega as posicoes de area desejada para rasteamento do rato
if (event == EVENT_LBUTTONDOWN) {

posicao[coord][coord]=x;

posicao[coord][coord+1]=y;

coord++;
if(coord==2)gravar_vid_restrito=true;
}
}


//funnção principal, onde ocorre a captura da imagem
void principal()
{
    double resul, tempo = 0;
int cont_frames = 0;
    struct timeval start_time;

    struct timeval stop_time;

    myfile.open("coordenadas.txt");

cap >> cameraFrame;
imshow("original",cameraFrame);
    gettimeofday(&start_time, NULL);

    while (true) {
        if(trava==true) cap >> cameraFrame;
 
        cont_frames++;
        gettimeofday(&stop_time, NULL);
        resul = (float)(stop_time.tv_sec - start_time.tv_sec);

        resul += (stop_time.tv_usec - start_time.tv_usec) / (float)MICRO_PER_SECOND;
        tempo += resul;

        if (tempo >= 1.0000) {

            fps = cont_frames;
            tempo = 0;
            cont_frames = 0;
            resul = 0;
            gettimeofday(&start_time, NULL);
           
        }
        
        setMouseCallback("original", CallBackFunc, NULL); //funcoes do mouse
    if(trava==true) frame(cameraFrame);

//imshow("teste",contornos (cameraFrame));
        char c = (char)waitKey(1); //esc clicada fecha o prog.
        if (c == 27)
            break;
//da play no video
if (c == 'p' || c=='P') {
if(trava==true)trava=false;
else trava=true;

}
//captura uma foto do rato
if (c == 'f' || c=='F')foto=true;
    }
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
    myfile.close();
}

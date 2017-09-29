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

int xpos, ypos, blue, green, red;
Mat cameraFrame;
double fps;
VideoCapture cap(0);
ofstream myfile;

#define MICRO_PER_SECOND 1000000

int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
VideoWriter video("video_sem_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
VideoWriter video2("video_com_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

//função de medição do fps

//função de modificação da imagem
Mat transform(Mat frame)
{
    Mat frame2, mask;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz mask
    inRange(frame, Scalar(blue - 20, green - 20, red - 20), Scalar(blue + 20, green + 20, red + 20), mask);

    

    //efeitos para reduzir ruido
    erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    //retorna aos valores de rgb
    bitwise_and(frame, frame, frame2, mask = mask);

    //centro de massa
    Moments mu = moments(mask, true);
    Point center;
    center.x = mu.m10 / mu.m00;
    center.y = mu.m01 / mu.m00;
    if (center.x >= 0) {
        myfile << center.x << " " << center.y << endl;
        video.write(frame2);
    }
    //coloca um disco como ponto de centro de massa
    circle(frame2, center, 3, Scalar(0, 0, 255), -1);
    if (center.x >= 0)
        video2.write(frame2);
    return frame2;
}

//função de exibição da imagem capturada e ja modificada
void frame(Mat frame)
{
    Mat Framevid = transform(frame);

    //exibe a imagem em conjunto com os frames
    putText(Framevid, format("FPS=%d", fps), Point2f(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255, 255));

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
    }
}

//funnção principal, onde ocorre a captura da imagem
void principal()
{
    double resul, tempo = 0, cont = 0;
    struct timeval start_time;

    struct timeval stop_time;

    myfile.open("coordenadas.txt");

    gettimeofday(&start_time, NULL);

    while (true) {
        cap >> cameraFrame;
        cont++;
        gettimeofday(&stop_time, NULL);
        resul = (float)(stop_time.tv_sec - start_time.tv_sec);

        resul += (stop_time.tv_usec - start_time.tv_usec) / (float)MICRO_PER_SECOND;
        tempo += resul;

        if (tempo >= 1.0000) {

            fps = cont;
            tempo = 0;
            cont = 0;
            resul = 0;
            gettimeofday(&start_time, NULL);
           
        }
        namedWindow("Identificação", 1);
        namedWindow("original", 1);
        setMouseCallback("original", CallBackFunc, NULL); //funcoes do mouse
        frame(cameraFrame);

        char c = (char)waitKey(1); //esc clicada fecha o prog.
        if (c == 27)
            break;

    }
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
    myfile.close();
}

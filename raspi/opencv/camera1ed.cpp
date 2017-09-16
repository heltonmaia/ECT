#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

int xpos, ypos, blue, green, red;
Mat cameraFrame;
VideoCapture stream1(0);

int frameCounter, tick, timeBegin, fps;

int fps_vid()
{
    frameCounter++;
    time_t timeNow = time(0) - timeBegin;
    if (timeNow - tick >= 1) {
        tick++;
        fps = frameCounter;
        frameCounter = 0;
    }
    return fps;
}

void frame(Mat frame)
{
    int height, width, limit=20;
    Mat frame2, mask;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz mask
    inRange(frame, Scalar(blue - limit, green - limit, red - limit), Scalar(blue + limit, green + limit, red + limit), mask);
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

    //efeitos para reduzir ruido
    erode(mask, mask, element);
    dilate(mask, mask, element);

    //centro de massa
    Moments mu = moments(mask, true);
    Point center;
    center.x = mu.m10 / mu.m00;
    center.y = mu.m01 / mu.m00;

    //retorna aos valores de rgb
    bitwise_and(frame, frame, frame2, mask = mask);

    //coloca um disco como ponto de centro de massa
    circle(frame2, center, 3, Scalar(0, 0, 255), -1);

    //exibe a imagem em conjunto com os frames
    putText(frame2, format("FPS=%d", fps_vid()), Point2f(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255, 255));

    imshow("Identificação", frame2);
    imshow("original", frame);
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    xpos = x; //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
    ypos = y;

    if (event == EVENT_RBUTTONDOWN) {
        Vec3f intensity = cameraFrame.at<Vec3b>(ypos, xpos);
        blue = intensity.val[0];
        green = intensity.val[1];
        red = intensity.val[2];
    }
}

int main(int argc, char** argv)
{
    frameCounter = 0;
    tick = 0;
    timeBegin = time(0);

    while (true) {
        stream1 >> cameraFrame;
        namedWindow("Identificação", 1);

        setMouseCallback("original", CallBackFunc, NULL); //funcoes do mouse
        frame(cameraFrame);

        char c = (char)waitKey(1); //esc clicada fecha o prog.
        if (c == 27)
            break;
    }

    return 0;
}

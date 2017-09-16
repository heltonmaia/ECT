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

  int frameCounter,tick,timeBegin, fps;
 


 int fps_vid()
 {
    frameCounter++;
    time_t timeNow = time(0) - timeBegin;
    if (timeNow - tick >= 1) 
    {
        tick++;
        fps = frameCounter;
        frameCounter = 0;
    }
    return fps;
 }

 void frame(Mat frame)
 {
    Mat frame2, mask;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz mask
    inRange(frame, Scalar(blue - 20, green - 20, red - 20), Scalar(blue + 20, green + 20, red + 20), mask);

    //retorna aos valores de rgb
    bitwise_and(frame, frame, frame2, mask = mask);

    putText(frame2, format("FPS=%d", fps_vid()), Point2f(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255, 255));

    imshow("Identificação", frame2);
    imshow("original", frame);
 }

 void CallBackFunc(int event, int x, int y, int flags, void* userdata)
 {
    xpos = x; //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
    ypos = y;

    if (event == EVENT_RBUTTONDOWN) 
    {
        Scalar intensity = cameraFrame.at<Vec3b>(ypos, xpos);
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

    while (true) 
      {
        stream1 >> cameraFrame;
        namedWindow("Identificação", 1);

        setMouseCallback("original", CallBackFunc, NULL); //funcoes do mouse
        frame(cameraFrame);

        char c = (char)waitKey(1); //esc clicada fecha o prog.
        if (c == 27) break;
    
      }

    return 0;
  }

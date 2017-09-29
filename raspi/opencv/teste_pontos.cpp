#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
 
using namespace std;
using namespace cv;
 
int main(){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("/home/lucas/Rasp-opencv-testes/video_sem_pontos.avi"); 
    ifstream coord("coordenadas.txt");
Point center;

 int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
 int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
 VideoWriter video("video_com_pontos_teste.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
     
  while(1){
 
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

 if(!coord.eof()){
coord>>center.x;
coord>>center.y;
}
circle(frame, center, 3, Scalar(0, 0, 255), -1);
video.write(frame);
    // Display the resulting frame
    imshow( "Frame", frame );
 
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
  
  // When everything done, release the video capture object
  cap.release();
 video.release();
  // Closes all the frames
  destroyAllWindows();
     coord.close();
  return 0;
}

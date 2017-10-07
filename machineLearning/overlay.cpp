#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv ){

	Mat src1;

	int angle;
	int length = 120;
	Point P1(150,150);
	Point P2;

	//input test
    if (argc < 3){
    	cout << "Error: Use ./contorno image" << endl;
    	return -1;
    }
    src1  = imread(argv[1]);

    if(!src1.data ){
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

	//create a circle
	circle(src1, P1, 120.0, Scalar( 0, 0, 255 ), 1, 8 );

	//draw informations
	char txt[5];
	for(angle=0; angle<=360; angle+=30){
		P2.x =  (int)round(P1.x + length * cos(angle * CV_PI / 180.0));
		P2.y =  (int)round(P1.y + length * sin(angle * CV_PI / 180.0));
		line(src1, P2, P1, Scalar( 0, 0, 255 ), 1, CV_AA );

		if(angle<360){
			sprintf(txt, "%d", 360-angle);
			putText(src1, txt, P2, FONT_HERSHEY_PLAIN, 0.7, cvScalar(255,255,255), 1, CV_AA);
  		}
  	}

	if( !src1.data ){
 		cout << "Error loading src1 ";
 		return -1;
 	}

	// Create Windows
	namedWindow("angle", 1);
	imshow( "angle", src1 );

    //save image
    imwrite(argv[2], src1 );

	//waitKey(0);
	return 0;
}

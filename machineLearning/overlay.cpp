#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv ){

	Mat src1, dst;
	
	int angle;
	int length = 150;
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
	
	circle( src1, Point( 150, 150 ), 150.0, Scalar( 0, 0, 255 ), 1, 8 );
	
	
	for(angle=0; angle<=360; angle+=30){
		P2.x =  (int)round(P1.x + length * cos(angle * CV_PI / 180.0));
		P2.y =  (int)round(P1.y + length * sin(angle * CV_PI / 180.0));
		line(src1, P2, P1, Scalar( 0, 0, 255 ), 1, CV_AA );
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

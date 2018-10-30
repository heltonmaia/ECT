#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include "funcoes.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
   
if (argc < 2){
    	cout << "Error: Use ./track_offline video.avi" << endl;
    	return -1;
}
    principal(argv);


    return 0;
}

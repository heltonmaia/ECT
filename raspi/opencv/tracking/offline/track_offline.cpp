#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/features2d/features2d.hpp>
#include "funcoes_toff.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

    if (argc < 2){
    	cout << "Error: Use ./track_offline video.avi" << endl;
    	return -1;
    }

    principal(argv);

    return 0;
}

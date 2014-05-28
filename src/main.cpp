#include <iostream>
#include <fstream>
#include <opencv2/highgui.hpp>
#include "stitching.h"

using namespace std;
using namespace cv;

vector<Mat> imgs;
string result_name = "result.jpg";

void printUsage();
int parseCmdArgs(int argc, char** argv);

int main(int argc, char* argv[])
{
    int retval = parseCmdArgs(argc, argv);
    if (retval) return -1;

    Mat pano;
    Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
    Stitcher::Status status = stitcher.stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return -1;
    }

    imwrite(result_name, pano);
    return 0;
}

int parseCmdArgs(int argc, char** argv){
    if (argc == 1){
        printUsage();
        return -1;
    }
    for (int i = 1; i < argc; ++i){
        if (string(argv[i]) == "--output"){
            result_name = argv[i + 1];
            i++;
        }
        else{
            Mat img = imread(argv[i]);
            if (img.empty()){
                cout << "Can't read image '" << argv[i] << "'\n";
                return -1;
            }
            imgs.push_back(img);
        }
    }
    return 0;
}
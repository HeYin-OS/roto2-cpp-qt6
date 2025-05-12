//
// Created by 12544 on 25-5-9.
//

#ifndef ROTO_2_CPP_VIDEOHANDLER_H
#define ROTO_2_CPP_VIDEOHANDLER_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class VideoHandler {
public:
    VideoHandler(string fileUrl);

    Mat getFrame(int idx) const;

private:
    vector<Mat> frames;
    int num_frame;
    double fps;
    int width;
    int height;

};

#endif //ROTO_2_CPP_VIDEOHANDLER_H

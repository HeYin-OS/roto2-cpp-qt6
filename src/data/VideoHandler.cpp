//
// Created by 12544 on 25-5-9.
//

#include "VideoHandler.h"

VideoHandler::VideoHandler(string fileUrl) {
    VideoCapture cap(fileUrl);
    if (!cap.isOpened()) {
        cerr << "Cannot Open Target Video File(s)." << endl;
    }
    {
        Mat frame;
        while (cap.read(frame)) {
            this->frames.push_back(frame);
        }
    }
    this->num_frame = frames.size();
    this->fps = cap.get(CAP_PROP_FPS);
    this->width = cap.get(CAP_PROP_FRAME_WIDTH);
    this->height = cap.get(CAP_PROP_FRAME_HEIGHT);
}

Mat VideoHandler::getFrame(int idx) const {

    if (idx < 0 || idx >= num_frame) {
        return Mat::zeros(height, width, CV_8UC3);
    }
    return frames[idx];

}

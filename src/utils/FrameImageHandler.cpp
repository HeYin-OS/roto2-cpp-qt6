//
// Created by 12544 on 25-5-12.
//

#include "FrameImageHandler.h"

FrameImgHandler::FrameImgHandler(string url) :
        frame_url_head(url),
        frame_num(FRAME_NUM) {
    this->initFrameCache();
    this->width_max = frame_cache[0].width();
    this->height_max = frame_cache[0].height();;
}

string FrameImgHandler::getFrameUrl(int idx) {
    ostringstream oss;
    oss << setw(5) << setfill('0') << idx;
    auto str = oss.str();
    auto full_url = frame_url_head + str + ".jpg";
    qDebug() << full_url;
    return full_url;
}

int FrameImgHandler::getFrameNum() const {
    return this->frame_num;
}

void FrameImgHandler::initFrameCache() {
    for (int i = 0; i < this->frame_num; ++i) {
        this->frame_cache.push_back(QPixmap(getFrameUrl(i).c_str()));
    }
}

QPixmap &FrameImgHandler::getFrame(int idx) {
    return frame_cache[idx];
}

int FrameImgHandler::getMaxWidth() const {
    return this->width_max;
}

int FrameImgHandler::getMaxHeight() const {
    return this->height_max;
}

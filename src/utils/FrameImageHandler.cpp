//
// Created by 12544 on 25-5-12.
//

#include "FrameImageHandler.h"

FrameImgHandler::FrameImgHandler(string url) :
        frame_url_head(url),
        frame_num(FRAME_NUM) {
    // 初始化全部帧
    this->initFrameCache();
    // 初始化最大宽度
    this->width_max = frame_cache[0].width();
    // 初始化最大高度
    this->height_max = frame_cache[0].height();;
}

string FrameImgHandler::getFrameUrl(int idx) {
    // 定义输出字符串流 宽度为5 填充为0
    ostringstream oss;
    oss << setw(5) << setfill('0') << idx;
    // 输出字符串
    auto str = oss.str();
    // 拼接路径字符串
    auto full_url = frame_url_head + str + ".jpg";
    return full_url;
}

int FrameImgHandler::getFrameNum() const {
    // 返回总帧数
    return this->frame_num;
}

void FrameImgHandler::initFrameCache() {
    // 初始化帧缓存
    for (int i = 0; i < this->frame_num; ++i) {
        this->frame_cache.push_back(QPixmap(getFrameUrl(i).c_str()));
    }
}

QPixmap &FrameImgHandler::getFrame(int idx) {
    // 返回帧
    return frame_cache[idx];
}

int FrameImgHandler::getMaxWidth() const {
    // 返回最大宽度
    return this->width_max;
}

int FrameImgHandler::getMaxHeight() const {
    // 返回最大高度
    return this->height_max;
}

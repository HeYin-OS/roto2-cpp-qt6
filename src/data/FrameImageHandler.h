//
// Created by 12544 on 25-5-12.
//

#ifndef ROTO_2_CPP_FRAMEIMAGEHANDLER_H
#define ROTO_2_CPP_FRAMEIMAGEHANDLER_H
#include "../macros.h"

using namespace std;

class FrameImgHandler {
public:
    FrameImgHandler(const string &url);

    string getFrameUrl(int idx) const;

    int getFrameNum() const;

    int getMaxWidth() const;

    int getMaxHeight() const;

    QPixmap& getFrame(int idx);

private:
    int frame_num;
    string frame_url_head;
    vector<QPixmap> frame_cache;
    int width_max;
    int height_max;

    void initFrameCache();
};

#endif //ROTO_2_CPP_FRAMEIMAGEHANDLER_H

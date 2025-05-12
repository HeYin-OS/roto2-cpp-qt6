//
// Created by 12544 on 25-4-14.
//

#include "../utils/CurveUtils.h"
#include "../utils/FrameImageHandler.h"
#include "../macros.h"

#ifndef ROTO_2_CPP_CANVASWIDGET_H
#define ROTO_2_CPP_CANVASWIDGET_H

class CanvasWidget : public QWidget {
public:
    CanvasWidget(QWidget *parent = nullptr);

    int getFrameCursor() const;

    void frameCursorAutoIncrease();

    void frameCursorAutoDecrease();

    void replaceFrame();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool isMousePressing = false;
    array<int, FRAME_NUM> curve_insert_cursor{};
    int frame_cursor;

    array<BezierCurveContainer, FRAME_NUM> bezier_container;
    FrameImgHandler frameHandler;
};

#endif //ROTO_2_CPP_CANVASWIDGET_H

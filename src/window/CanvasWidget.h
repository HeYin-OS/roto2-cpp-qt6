//
// Created by 12544 on 25-4-14.
//

#include "../data/CurveUtils.h"
#include "../data/FrameImageHandler.h"
#include "../macros.h"

#ifndef ROTO_2_CPP_CANVASWIDGET_H
#define ROTO_2_CPP_CANVASWIDGET_H

class CanvasWidget : public QWidget {
public:
    CanvasWidget(QWidget *parent = nullptr);

    void curveInsertCursorRewind();

    int getFrameCursor() const;

    int getPointNum() const;

    void setFrameCursor(int val);

    void frameCursorAutoIncrease();

    void frameCursorAutoDecrease();

    void toggleDirectionLineVisibility();

    void toggleEndPointVisibility();

    void fitBetween(int idx1, int idx2);

    void inline reDraw();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool isMousePressing = false;
    array<int, g_frame_num> current_insert_idx{};
    int current_frame;

    array<BezierCurve, g_frame_num> curves;
    FrameImgHandler frameHandler;
};

#endif //ROTO_2_CPP_CANVASWIDGET_H

//
// Created by 12544 on 25-4-14.
//
#pragma once

#include "../data/CurveUtils.h"
#include "../data/FrameImageHandler.h"
#include "../macros.h"

#ifndef ROTO_2_CPP_CANVASWIDGET_H
#define ROTO_2_CPP_CANVASWIDGET_H

class CanvasWidget final : public QWidget {
public:
    explicit CanvasWidget(QWidget *parent = nullptr);

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
    // 鼠标按压判断
    bool isMousePressing = false;
    // 当前帧的插入序号
    array<int, g_frame_num> current_insert_idx{};
    // 当前的帧号
    int current_frame;
    // 全部曲线
    array<BezierCurve, g_frame_num> curves;
    // 全部帧
    FrameImgHandler frames;
};

#endif //ROTO_2_CPP_CANVASWIDGET_H

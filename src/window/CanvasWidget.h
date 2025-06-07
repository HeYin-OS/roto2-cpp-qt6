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
    // 曲线绘制后退
    void curveInsertRewind();
    // 帧号增加
    void frameCursorAutoIncrease();
    // 帧号减少
    void frameCursorAutoDecrease();
    // 切换手柄线可见度
    void toggleDirectionLineVisibility();
    // 切换端点可见度
    void toggleEndPointVisibility();
    // 优化操作
    void fitBetween(int idx1, int idx2);
    // 重画
    void inline reDraw();

    int getCurrentFrameIdx() const;
    int getPointNum() const;
    void setFrameCursor(int val);
    void switchToInsert();
    void switchToMove();

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
    // 显示手柄参考线
    bool show_direction_line = true;
    // 显示曲线上的控制点
    bool show_end_point = true;
    // 插入和移动的切换
    bool is_insert = true;


    // 绘制手柄参考线
    void drawReferLine(QPainter& painter) const;
    // 绘制贝塞尔曲线
    void drawBezierCurve(QPainter& painter) const;
};

#endif //ROTO_2_CPP_CANVASWIDGET_H

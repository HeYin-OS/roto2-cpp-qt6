//
// Created by 12544 on 25-4-13.
//
#pragma once

#include "../macros.h"
#include "CanvasWidget.h"

#ifndef ROTO_2_CPP_SKETCHWINDOW_H
#define ROTO_2_CPP_SKETCHWINDOW_H

class SketchWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SketchWindow(QWidget* parent = nullptr);
    ~SketchWindow();

private slots:
    void onFrameLeftButtonClicked();
    void onFrameRightButtonClicked();
    void onFrameSliderValueChange();
    void onToFrameOneButtonClicked();
    void onToFrameTwoButtonClicked();
    void onSwitchToInsertClicked();
    void onSwitchToMoveClicked();
    void onDeletePrevClicked();
    void onClearCanvasButtonClicked();
    void onToggleDirLineButtonClicked();
    void onToggleEndPointButtonClicked();
    void onFitButtonClicked();

private:
    CanvasWidget canvas;

    // 帧控制功能区
    QGroupBox frame_box;
    QLabel frame_label; //当前帧
    QPushButton left_button; //帧后退
    QSlider slider; //帧滚动条
    QPushButton right_button; //帧前进
    QPushButton to_frame1_button; //转移1按钮
    QPushButton to_frame2_button; //转移2按钮
    // 绘画功能控制区
    QGroupBox draw_box;
    QPushButton insert_button;
    QPushButton move_button;
    QPushButton delete_prev_button; //删除最近绘画点
    QPushButton canvas_clear_button; //清除当前画布
    // 显示功能控制区
    QGroupBox show_box;
    QPushButton toggle_dir_line_button; //切换辅助线按钮
    QPushButton toggle_endpoint_button; //切换端点显示按钮
    // 优化功能控制区
    QGroupBox opt_box;
    QPushButton fit_button; //拟合按钮
    QLabel frame1_label; //帧1序号显示
    QLabel frame2_label; //帧2序号显示



    void initComponentsAndLayout();
    void initSignalAndSlots();
    void moveToCenter();
};

#endif //ROTO_2_CPP_SKETCHWINDOW_H

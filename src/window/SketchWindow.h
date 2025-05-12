//
// Created by 12544 on 25-4-13.
//
#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QScreen>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>

#include "../macros.h"
#include "CanvasWidget.h"

#ifndef ROTO_2_CPP_SKETCHWINDOW_H
#define ROTO_2_CPP_SKETCHWINDOW_H

class SketchWindow : public QMainWindow {
    Q_OBJECT

public:
    SketchWindow(QWidget* parent = nullptr);
    ~SketchWindow();

protected:

private slots:
    void onFrameLeftButtonClicked();
    void onFrameRightButtonClicked();

private:
    CanvasWidget canvas;

    QLabel frame_label; //当前帧
    QPushButton left_button; //帧后退
    QSlider slider; //帧滚动条
    QPushButton right_button; //帧前进

    void initComponentsAndLayout();
    void initSignalAndSlots();
    void moveToCenter();
};

#endif //ROTO_2_CPP_SKETCHWINDOW_H

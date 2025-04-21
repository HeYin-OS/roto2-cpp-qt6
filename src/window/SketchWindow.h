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

#include "CanvasWidget.h"

#ifndef ROTO_2_CPP_SKETCHWINDOW_H
#define ROTO_2_CPP_SKETCHWINDOW_H

class SketchWindow : public QMainWindow {
    Q_OBJECT

public:
    SketchWindow(QWidget* parent = nullptr);
    ~SketchWindow();

protected:

private:
    CanvasWidget canvas;

    void initComponentsAndLayout();
    void moveToCenter();
};

#endif //ROTO_2_CPP_SKETCHWINDOW_H

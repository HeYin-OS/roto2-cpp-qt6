//
// Created by 12544 on 25-4-14.
//
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>

#include "../utils/CurveUtils.h"
#include "../utils/FrameImageHandler.h"

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
    int curve_insert_cursor;
    int frame_cursor;

    BezierCurveContainer container;
    FrameImgHandler frameHandler;

};

#endif //ROTO_2_CPP_CANVASWIDGET_H

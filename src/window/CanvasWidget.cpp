//
// Created by 12544 on 25-4-14.
//

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
        QWidget(parent),
        test_pic("../test/cat.jpg") {
    setMinimumSize(test_pic.size());
    setMouseTracking(true);
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    // 设置画笔
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    // 画布
    painter.drawPixmap(0, 0, test_pic);
    // 贝塞尔曲线和手柄描绘
    container.drawBezierCurve(painter);
    container.drawReferLine(painter);
    QWidget::paintEvent(event);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    // 鼠标按压
    isMousePressing = true;
    // 采集曲线起点
    auto p = event->position().toPoint();
    container.addStartEndPoint(p, curve_insert_cursor);
    update();
    QWidget::mousePressEvent(event);
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    // 采集控制点
    if (isMousePressing) {
        auto p = event->position().toPoint();
        container.addControlPoint(p, curve_insert_cursor, test_pic.width(), test_pic.height());
    }
    update();
    QWidget::mouseMoveEvent(event);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    // 鼠标释放
    isMousePressing = false;
    curve_insert_cursor++;
    //container.printAll();
    update();
    QWidget::mouseReleaseEvent(event);
}

//
// Created by 12544 on 25-4-14.
//

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(QWidget *parent, string url) :
        QWidget(parent),
        test_pic(url.c_str()) {
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
    // 采集点
    auto p = event->position().toPoint();
    // 鼠标活动范围
    if (p.x() < 0 || p.y() < 0 || p.x() > test_pic.width() || p.y() > test_pic.height()) return;
    // 加入至管理容器
    container.addStartEndPoint(p, curve_insert_cursor);
    container.addControlPoint(p, curve_insert_cursor, test_pic.width(), test_pic.height());
    // 重画
    update();
    // 其余工作
    QWidget::mousePressEvent(event);
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    // 采集点
    auto p = event->position().toPoint();
    // 鼠标活动范围
    if (p.x() < 0 || p.y() < 0 || p.x() > test_pic.width() || p.y() > test_pic.height()) return;
    // 仅按压时加入容器
    if (isMousePressing) {
        container.addControlPoint(p, curve_insert_cursor, test_pic.width(), test_pic.height());
    }
    // 重画
    update();
    // 其余工作
    QWidget::mouseMoveEvent(event);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    // 鼠标释放
    isMousePressing = false;
    // 曲线指示游标后移
    curve_insert_cursor++;
    // 测试
    container.printAll();
    // 重画
    update();
    // 其余工作
    QWidget::mouseReleaseEvent(event);
}

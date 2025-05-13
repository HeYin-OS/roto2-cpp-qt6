//
// Created by 12544 on 25-4-14.
//

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
        QWidget(parent),
        isMousePressing(false),
        frame_cursor(0),
        frameHandler(TEST_VIDEO_FIRST_FRAME_URL) {
    setMinimumSize(frameHandler.getFrame(0).size());
    setMouseTracking(true);
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    // 设置画笔
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    // 画布
    painter.drawPixmap(0, 0, frameHandler.getFrame(frame_cursor));
    // 贝塞尔曲线和手柄描绘
    bezier_container[frame_cursor].drawBezierCurve(painter);
    bezier_container[frame_cursor].drawReferLine(painter);
    QWidget::paintEvent(event);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    // 鼠标按压
    isMousePressing = true;
    // 采集点
    auto p = event->position().toPoint();
    // 鼠标活动范围
    auto max_width = frameHandler.getMaxWidth();
    auto max_height = frameHandler.getMaxHeight();
    if (p.x() < 0 || p.y() < 0 || p.x() > max_width || p.y() > max_height) return;
    // 加入至管理容器
    bezier_container[frame_cursor].addStartEndPoint(p, curve_insert_cursor[frame_cursor]);;
    bezier_container[frame_cursor].addControlPoint(p, curve_insert_cursor[frame_cursor], max_width, max_height);
    // 重画
    update();
    // 其余工作
    QWidget::mousePressEvent(event);
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    // 采集点
    auto p = event->position().toPoint();
    // 鼠标活动范围
    auto max_width = frameHandler.getMaxWidth();
    auto max_height = frameHandler.getMaxHeight();
    if (p.x() < 0 || p.y() < 0 || p.x() > max_width || p.y() > max_height) return;
    // 仅按压时加入容器
    if (isMousePressing) {
        bezier_container[frame_cursor].addControlPoint(p, curve_insert_cursor[frame_cursor], max_width, max_height);
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
    curve_insert_cursor[frame_cursor]++;
    // 测试
    bezier_container[frame_cursor].printAll();
    // 重画
    update();
    // 其余工作
    QWidget::mouseReleaseEvent(event);
}

int CanvasWidget::getFrameCursor() const {
    // 返回当前帧号
    return this->frame_cursor;
}

void CanvasWidget::setFrameCursor(int val) {
    // 设置值
    this->frame_cursor = val;
    // 防止越界
    if (this->frame_cursor >= frameHandler.getFrameNum()) {
        this->frame_cursor = frameHandler.getFrameNum() - 1;
    }
    // 防止越界
    if (this->frame_cursor < 0) {
        this->frame_cursor = 0;
    }
}

void CanvasWidget::frameCursorAutoIncrease() {
    // 往后移动帧
    this->frame_cursor++;
    // 防止越界
    if (this->frame_cursor >= frameHandler.getFrameNum()) {
        this->frame_cursor = frameHandler.getFrameNum() - 1;
    }
}

void CanvasWidget::frameCursorAutoDecrease() {
    // 往前移动帧
    this->frame_cursor--;
    // 防止越界
    if (this->frame_cursor < 0) {
        this->frame_cursor = 0;
    }
}

void CanvasWidget::reDraw() {
    // 重新按照帧号绘制
    update();
}

void CanvasWidget::curveInsertCursorRewind() {
    // 通过插入序号删除
    bezier_container[frame_cursor].deleteFromLast();
    // 测试
    bezier_container[frame_cursor].printAll();
    // 插入序号后退
    curve_insert_cursor[frame_cursor]--;
    // 防止越界
    if (curve_insert_cursor[frame_cursor] < 0) curve_insert_cursor[frame_cursor] = 0;
}

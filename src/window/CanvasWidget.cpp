//
// Created by 12544 on 25-4-14.
//

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
        QWidget(parent),
        isMousePressing(false),
        current_frame(0),
        frameHandler(g_frame0_url_head) {
    setMinimumSize(frameHandler.getFrame(0).size());
    setMouseTracking(true);
}

void CanvasWidget::curveInsertCursorRewind() {
    // 通过插入序号删除
    curves[current_frame].deleteFromLast();
    // 测试
    curves[current_frame].printAll();
    // 插入序号后退
    current_insert_idx[current_frame]--;
    // 防止越界
    if (current_insert_idx[current_frame] < 0) current_insert_idx[current_frame] = 0;
}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    // 设置画笔
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    // 画布
    painter.drawPixmap(0, 0, frameHandler.getFrame(current_frame));
    // 贝塞尔曲线和手柄描绘
    curves[current_frame].drawBezierCurve(painter);
    curves[current_frame].drawReferLine(painter);
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
    curves[current_frame].addStartEndPoint(p, current_insert_idx[current_frame]);
    curves[current_frame].addControlPoint(p, current_insert_idx[current_frame], max_width, max_height);
    // 重画
    this->reDraw();
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
        curves[current_frame].addControlPoint(p, current_insert_idx[current_frame], max_width, max_height);
    }
    // 重画
    this->reDraw();
    // 其余工作
    QWidget::mouseMoveEvent(event);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    // 鼠标释放
    isMousePressing = false;
    // 曲线指示游标后移
    current_insert_idx[current_frame]++;
    // 测试
    curves[current_frame].printAll();
    // 重画
    this->reDraw();
    // 其余工作
    QWidget::mouseReleaseEvent(event);
}

int CanvasWidget::getFrameCursor() const {
    // 返回当前帧号
    return this->current_frame;
}

int CanvasWidget::getPointNum() const {
    return curves[current_frame].getPointCount();
}

void CanvasWidget::setFrameCursor(int val) {
    // 设置值
    this->current_frame = val;
    // 防止越界
    if (this->current_frame >= frameHandler.getFrameNum()) {
        this->current_frame = frameHandler.getFrameNum() - 1;
    }
    // 防止越界
    if (this->current_frame < 0) {
        this->current_frame = 0;
    }
}

void CanvasWidget::frameCursorAutoIncrease() {
    // 往后移动帧
    this->current_frame++;
    // 防止越界
    if (this->current_frame >= frameHandler.getFrameNum()) {
        this->current_frame = frameHandler.getFrameNum() - 1;
    }
}

void CanvasWidget::frameCursorAutoDecrease() {
    // 往前移动帧
    this->current_frame--;
    // 防止越界
    if (this->current_frame < 0) {
        this->current_frame = 0;
    }
}

void CanvasWidget::toggleDirectionLineVisibility() {
    // 切换
    this->curves[current_frame].setDirectionLineVisibility(!this->curves[current_frame].getDirectionLineVisibility());
}

void CanvasWidget::toggleEndPointVisibility() {
    // 切换
    this->curves[current_frame].setEndPointVisibility(!this->curves[current_frame].getEndPointVisibility());
}

void CanvasWidget::fitBetween(int idx1, int idx2) {
    // 拷贝全部曲线到全部帧
    for (auto i = idx1 + 1; i <= idx2; ++i) {
        this->curves[i].cloneControlPoints(this->curves[idx1]);
    }
    // 获得采样点的位置

    // 计算能量

    // 更新控制点位置

    // 重画
    this->reDraw();
}

void inline CanvasWidget::reDraw() {
    // 重新按照帧号绘制
    update();
}

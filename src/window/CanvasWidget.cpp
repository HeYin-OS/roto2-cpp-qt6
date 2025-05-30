//
// Created by 12544 on 25-4-14.
//

#include "CanvasWidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent),
                                              current_frame(0),
                                              frames(g_frame0_url_head) {
    setMinimumSize(frames.getFrame(0).size());
    setMouseTracking(true);
}

void CanvasWidget::curveInsertRewind() {
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
    painter.drawPixmap(0, 0, frames.getFrame(current_frame));
    // 贝塞尔曲线和手柄描绘
    this->drawBezierCurve(painter);
    this->drawReferLine(painter);
    QWidget::paintEvent(event);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    // 鼠标按压
    isMousePressing = true;
    // 采集点
    const auto p = event->position().toPoint();
    // 鼠标活动范围
    const auto max_width = frames.getMaxWidth();
    const auto max_height = frames.getMaxHeight();
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
    const auto p = event->position().toPoint();
    // 鼠标活动范围
    const auto max_width = frames.getMaxWidth();
    const auto max_height = frames.getMaxHeight();
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

void CanvasWidget::setFrameCursor(const int val) {
    // 设置值
    this->current_frame = val;
    // 防止越界
    if (this->current_frame >= frames.getFrameNum()) {
        this->current_frame = frames.getFrameNum() - 1;
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
    if (this->current_frame >= frames.getFrameNum()) {
        this->current_frame = frames.getFrameNum() - 1;
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
    this->show_direction_line = !this->show_direction_line;
}

void CanvasWidget::toggleEndPointVisibility() {
    // 切换
    this->show_end_point = !this->show_end_point;
}

void CanvasWidget::fitBetween(const int idx1, const int idx2) {
    // 拷贝全部曲线到全部帧并且拷贝插入位置
    for (auto i = idx1 + 1; i <= idx2; ++i) {
        this->curves[i].cloneControlPoints(this->curves[idx1]);
        this->current_insert_idx[i] = this->curves[idx1].getPointCount();
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

void CanvasWidget::drawReferLine(QPainter &painter) const {
    auto &control_points = curves[current_frame].getControlPoints();
    // 绘制手柄线
    if (this->show_direction_line) {
        painter.setPen(QPen(QColor(0, 255, 0), 1)); // 绿色
        for (int i = 0; i < control_points.size(); i += 2) {
            auto [x0, y0] = control_points[i];
            auto [x1, y1] = control_points[i + 1];
            // 跳过空点
            if (x0 == 0.f && y0 == 0.f) break;
            painter.drawLine(x0, y0, x1, y1);
        }
    }
    // 绘制手柄线的端点
    painter.setPen(QPen(QColor(255, 0, 0), 4)); // 加粗的红色
    for (int i = 0; i < control_points.size(); i += 4) {
        auto [x0, y0] = control_points[i];
        auto [x1, y1] = control_points[i + 3];
        // 绘制第一个点
        painter.drawPoint(x0, y0);
        // 检查是否为空点
        if (x1 == 0.f && y1 == 0.f) break;
        painter.drawPoint(x1, y1);
    }
    // 绘制曲线上的控制点
    if (this->show_end_point) {
        painter.setPen(QPen(QColor(0, 255, 0), 4)); // 加粗的绿色
        for (int i = 0; i < control_points.size(); i += 4) {
            auto [x0, y0] = control_points[i + 1];
            auto [x1, y1] = control_points[i + 2];
            painter.drawPoint(x0, y0);
            // 跳过空点
            if (x1 == 0.f && y1 == 0.f) break;
            painter.drawPoint(x1, y1);
        }
    }
}

void CanvasWidget::drawBezierCurve(QPainter &painter) const {
    auto &control_points = curves[current_frame].getControlPoints();
    painter.setPen(QPen(QColor(255, 255, 0), 4)); // 黄色
    for (int i = 0; i < control_points.size(); i += 4) {
        auto [x0, y0] = control_points[i];
        auto [x1, y1] = control_points[i + 1];
        auto [x2, y2] = control_points[i + 2];
        auto [x3, y3] = control_points[i + 3];
        if (x2 == 0.f && y2 == 0.f) break;
        // 绘制曲线
        QPainterPath path;
        path.moveTo(QPointF(x0, y0));
        path.cubicTo(QPointF(x1, y1),
                     QPointF(x2, y2),
                     QPointF(x3, y3));
        painter.drawPath(path);
    }
}

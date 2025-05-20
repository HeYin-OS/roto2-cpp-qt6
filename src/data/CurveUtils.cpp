//
// Created by 12544 on 25-4-14.
//
#include "CurveUtils.h"

void BezierCurveContainer::addStartEndPoint(QPoint &point, int index) {
    // allocate room for 4 points
    for (int i = 0; i < 4; ++i) points.push_back({0, 0});
    // the start point of the current curve
    points[index * 4] = {point.x(), point.y()};
    // when it is the first curve
    if (index == 0) return;
    // the end point of the last curve
    points[index * 4 - 1] = {point.x(), point.y()};
    return;
}

void BezierCurveContainer::addControlPoint(QPoint &point, int index, int x_max, int y_max) {
    // first control point of the current curve
    auto x = point.x();
    auto y = point.y();
    // add first control point
    points[index * 4 + 1] = {x, y};
    // when it is the first curve
    if (index == 0) return;
    // get the anchor point
    auto [anchor_x, anchor_y] = points[index * 4];
    // compute the second control point of the last curve
    auto control_x = 2 * anchor_x - x;
    auto control_y = 2 * anchor_y - y;
    // out of range
    if (control_x < 0 || control_y < 0 || control_x > x_max || control_y > y_max) return;
    // update the second control point of the last curve
    points[index * 4 - 2] = {control_x, control_y};
    return;
}

void BezierCurveContainer::drawBezierCurve(QPainter &painter) {
    // initials
    painter.setPen(QPen(QColor(255, 255, 0), 4)); // yellow
    // the number of curves
    for (int i = 0; i < points.size(); i += 4) {
        auto [x0, y0] = points[i];
        auto [x1, y1] = points[i + 1];
        auto [x2, y2] = points[i + 2];
        auto [x3, y3] = points[i + 3];
        if (x2 == 0.f && y2 == 0.f) break;
        // draw bezier curve
        QPainterPath path;
        path.moveTo(QPointF(x0, y0));
        path.cubicTo(QPointF(x1, y1),
                     QPointF(x2, y2),
                     QPointF(x3, y3));
        painter.drawPath(path);
    }
    return;
}

void BezierCurveContainer::drawReferLine(QPainter &painter) {
    // draw anchor lines
    if (this->show_direction_line)
    {
        painter.setPen(QPen(QColor(0, 255, 0), 1)); // green
        for (int i = 0; i < points.size(); i += 2) {
            auto [x0, y0] = points[i];
            auto [x1, y1] = points[i + 1];
            // skip empty lines
            if (x0 == 0.f && y0 == 0.f) break;
            painter.drawLine(x0, y0, x1, y1);
        }
    }
    // draw anchor points
    painter.setPen(QPen(QColor(255, 0, 0), 4)); // Red with bold
    for (int i = 0; i < points.size(); i += 4) {
        auto [x0, y0] = points[i];
        auto [x1, y1] = points[i + 3];
        // incomplete points due to pen tool
        painter.drawPoint(x0, y0);
        // skip empty points
        if (x1 == 0.f && y1 == 0.f) break;
        painter.drawPoint(x1, y1);
    }
    // draw control points
    if (this->show_end_point)
    {
        painter.setPen(QPen(QColor(0, 255, 0), 4)); // Green with bold
        for (int i = 0; i < points.size(); i += 4) {
            auto [x0, y0] = points[i + 1];
            auto [x1, y1] = points[i + 2];
            painter.drawPoint(x0, y0);
            // skip empty points
            if (x1 == 0.f && y1 == 0.f) break;
            painter.drawPoint(x1, y1);
        }
    }

}

pair<float, float> BezierCurveContainer::getPoint(int curve_index, int point_index) const {
    return points[curve_index * 4 + point_index];
}

void BezierCurveContainer::printAll() const {
    int i = 0;
    for (auto &p: points) {
        qDebug() << "[" << i << "]:" << p.first << " " << p.second;
        ++i;
    }
    qDebug() << "------------------------";
}

void BezierCurveContainer::moveAnchorPoint(QPoint &point) {

}

void BezierCurveContainer::moveControlPoint(QPoint &point) {

}

void BezierCurveContainer::deleteFromLast() {
    if (points.size() >= 4) {
        points.erase(points.end() - 4, points.end());
    }
    if (points.size() > 0) {
        points[points.size() - 1].first = 0;
        points[points.size() - 1].second = 0;
        points[points.size() - 2].first = 0;
        points[points.size() - 2].second = 0;
    }
}

int BezierCurveContainer::getPointCount() const {
    return points.size();
}

void BezierCurveContainer::setDirectionLineVisibility(bool val) {
    show_direction_line = val;
}

void BezierCurveContainer::setEndPointVisibility(bool val) {
    show_end_point = val;
}

bool BezierCurveContainer::getDirectionLineVisibility() const {
    return show_direction_line;
}

bool BezierCurveContainer::getEndPointVisibility() const {
    return show_end_point;
}
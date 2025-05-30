//
// Created by 12544 on 25-4-14.
//

#include "CurveUtils.h"

void BezierCurve::addStartEndPoint(const QPoint &point, const int index) {
    // allocate room for 4 points
    for (int i = 0; i < 4; ++i) control_points.push_back({0, 0});
    // the start point of the current curve
    control_points[index * 4] = {point.x(), point.y()};
    // when it is the first curve
    if (index == 0) return;
    // the end point of the last curve
    control_points[index * 4 - 1] = {point.x(), point.y()};
}

void BezierCurve::addControlPoint(const QPoint &point, const int index, const int x_max, const int y_max) {
    // first control point of the current curve
    auto x = point.x();
    auto y = point.y();
    // add first control point
    control_points[index * 4 + 1] = {x, y};
    // when it is the first curve
    if (index == 0) return;
    // get the anchor point
    auto [anchor_x, anchor_y] = control_points[index * 4];
    // compute the second control point of the last curve
    auto control_x = 2 * anchor_x - x;
    auto control_y = 2 * anchor_y - y;
    // out of range
    if (control_x < 0 || control_y < 0 || control_x > x_max || control_y > y_max) return;
    // update the second control point of the last curve
    control_points[index * 4 - 2] = {control_x, control_y};
}

pair<float, float> BezierCurve::getPoint(int curve_index, const int point_index) const {
    return control_points[curve_index * 4 + point_index];
}

void BezierCurve::printAll() const {
    int i = 0;
    for (auto &p: control_points) {
        qDebug() << "[" << i << "]:" << p.first << " " << p.second;
        ++i;
    }
    qDebug() << "------------------------";
}

void BezierCurve::moveAnchorPoint(QPoint &point) {
}

void BezierCurve::moveControlPoint(QPoint &point) {
}

void BezierCurve::deleteFromLast() {
    if (control_points.size() >= 4) {
        control_points.erase(control_points.end() - 4, control_points.end());
    }
    if (control_points.size() > 0) {
        control_points[control_points.size() - 1].first = 0;
        control_points[control_points.size() - 1].second = 0;
        control_points[control_points.size() - 2].first = 0;
        control_points[control_points.size() - 2].second = 0;
    }
}

int BezierCurve::getPointCount() const {
    return control_points.size();
}

const vector<pair<float, float> > &BezierCurve::getControlPoints() const {
    return control_points;
}

void BezierCurve::cloneControlPoints(const BezierCurve &source) {
    this->control_points = {};
    this->control_points = source.control_points;
}

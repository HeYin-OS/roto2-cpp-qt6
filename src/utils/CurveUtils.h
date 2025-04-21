//
// Created by 12544 on 25-4-14.
//
#include <vector>
#include <algorithm>
#include <QPoint>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QThread>

#ifndef ROTO_2_CPP_CURVECONTAINER_H
#define ROTO_2_CPP_CURVECONTAINER_H

using namespace std;

class BezierCurveContainer {
public:
    void addStartEndPoint(QPoint point, int index);

    void addControlPoint(QPoint point, int index, int x_max, int y_max);

    void drawReferLine(QPainter& painter);

    void drawBezierCurve(QPainter& painter);

    pair<float, float> getPoint(int curve_index, int point_index) const;

    void printAll() const;

protected:


private:
    vector<pair<float, float>> points;

};

#endif //ROTO_2_CPP_CURVECONTAINER_H

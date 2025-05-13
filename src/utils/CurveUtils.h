//
// Created by 12544 on 25-4-14.
//
#include "../macros.h"

#ifndef ROTO_2_CPP_CURVECONTAINER_H
#define ROTO_2_CPP_CURVECONTAINER_H

using namespace std;

class BezierCurveContainer {
public:
    // point addition
    void addStartEndPoint(QPoint& point, int index);

    void addControlPoint(QPoint& point, int index, int x_max, int y_max);

    // drawer function
    void drawReferLine(QPainter& painter);

    void drawBezierCurve(QPainter& painter);

    // moving function
    void moveAnchorPoint(QPoint& point);

    void moveControlPoint(QPoint& point);

    // delete function
    void deleteFromLast();

    // point access
    pair<float, float> getPoint(int curve_index, int point_index) const;

    // debug
    void printAll() const;

protected:


private:
    vector<pair<float, float>> points;

};

#endif //ROTO_2_CPP_CURVECONTAINER_H

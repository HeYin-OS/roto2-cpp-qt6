//
// Created by 12544 on 25-4-14.
//
#include "../macros.h"

#ifndef ROTO_2_CPP_CURVECONTAINER_H
#define ROTO_2_CPP_CURVECONTAINER_H

using namespace std;

class BezierCurve {
public:
    // point addition
    void addStartEndPoint(const QPoint& point, int index);

    void addControlPoint(const QPoint& point, int index, int x_max, int y_max);

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

    // clone
    void cloneControlPoints(const BezierCurve& source);

    // setters
    void setDirectionLineVisibility(bool val);
    void setEndPointVisibility(bool val);

    // getters
    bool getDirectionLineVisibility() const;
    bool getEndPointVisibility() const;
    int getPointCount() const;

    // debug
    void printAll() const;

protected:


private:
    vector<pair<float, float>> control_points;
    bool show_direction_line = true;
    bool show_end_point = true;
};

#endif //ROTO_2_CPP_CURVECONTAINER_H

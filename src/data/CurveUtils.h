//
// Created by 12544 on 25-4-14.
//
#pragma once
#include "../macros.h"

#ifndef ROTO_2_CPP_CURVECONTAINER_H
#define ROTO_2_CPP_CURVECONTAINER_H

using namespace std;

class BezierCurve {
public:
    // point addition
    void addStartEndPoint(const QPoint& point, int index);

    void addControlPoint(const QPoint& point, int index, int x_max, int y_max);

    // move function
    void moveTo(const QPoint& point, int x_max, int y_max);

    // delete function
    void deleteFromLast();

    // point access
    pair<double, double> getPoint(int curve_index, int point_index) const;
    pair<double, double>& operator[](int index);
    const pair<double, double>& operator[](int index) const;

    // clone
    void cloneControlPoints(const BezierCurve& source);

    int getPointCount() const;
    const vector<pair<double, double>>& getControlPoints() const;

    // resize
    void resizeControlPoints(int num);

    // debug
    void printAll() const;

private:
    vector<pair<double, double>> control_points;
};

#endif //ROTO_2_CPP_CURVECONTAINER_H

//
// Created by 12544 on 25-5-12.
//

#ifndef ROTO_2_CPP_MACROS_H
#define ROTO_2_CPP_MACROS_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QScreen>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>
#include <QPainterPath>
#include <QGroupBox>

#include <opencv2/opencv.hpp>

#include <ceres/ceres.h>

#include <Eigen/Dense>

const std::string g_frame0_url_head("../test/bear/"); // 测试路径头
const int g_frame_num = 82; // 测试总帧数

const double g_w_v = 0.1;
const int g_w_l = 500;
const int g_w_c = 40000;
const int g_w_i = 1;
const int g_w_g = 1000;

#endif //ROTO_2_CPP_MACROS_H

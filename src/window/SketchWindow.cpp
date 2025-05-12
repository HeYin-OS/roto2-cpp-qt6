//
// Created by 12544 on 25-4-13.
//

#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include "SketchWindow.h"

SketchWindow::SketchWindow(QWidget *parent) :
        QMainWindow(parent),
        canvas(this) {
    this->initComponentsAndLayout();
    setMouseTracking(true);
}

SketchWindow::~SketchWindow() {}

void SketchWindow::initComponentsAndLayout() {
    // 窗体名
    this->setWindowTitle("Sketching Board");
    // 由于工具栏扩展窗体尺寸
    int tool_expansion_space = 240;
    QPixmap test_image("../test/cat.jpg");
    this->setFixedSize(test_image.width() + tool_expansion_space, test_image.height());
    // 窗体移动至屏幕中央
    this->moveToCenter();
    // 总体布局
    // QHBoxLayout *layout = new QHBoxLayout(this->centralWidget());
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->setSpacing(0);
    // 加入绘画控件
    canvas.setGeometry(0, 0, test_image.width(), test_image.height());
    // 帧控制相关
    // 加入标签显示当前帧的序号
    QLabel *frame_label = new QLabel("1234", this);
    frame_label->setGeometry(test_image.width() + 10, 10, 30, 30);
    // 加入左移按钮
    QPushButton *left_button = new QPushButton("◀", this);
    left_button->setGeometry(test_image.width() + 50, 10, 30, 30);
    // 加入滚动条
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    slider->setGeometry(test_image.width() + 90, 10, 100, 30);
    // 加入右移按钮
    QPushButton *right_button = new QPushButton("▶", this);
    right_button->setGeometry(test_image.width() + 200, 10, 30, 30);

}

void SketchWindow::moveToCenter() {
    auto qr = this->geometry();
    auto cp = this->screen()->availableGeometry().center();
    qr.moveCenter(cp);
    move(qr.topLeft());
}

//
// Created by 12544 on 25-4-13.
//

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
    int tool_expansion_space = 300;
    QPixmap test_image("../test/cat.jpg");
    this->setFixedSize(test_image.width() + tool_expansion_space, test_image.height());
    // 窗体移动至屏幕中央
    this->moveToCenter();
    // 总体布局
    QHBoxLayout *layout = new QHBoxLayout(this->centralWidget());
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    // 加入绘画控件
    layout->addWidget(&canvas, 1);
    // 加入按钮控件
    /*
     *
     * */
}

void SketchWindow::moveToCenter() {
    auto qr = this->geometry();
    auto cp = this->screen()->availableGeometry().center();
    qr.moveCenter(cp);
    move(qr.topLeft());
}

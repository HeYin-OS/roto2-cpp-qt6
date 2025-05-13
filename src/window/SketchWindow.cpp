//
// Created by 12544 on 25-4-13.
//
#include "SketchWindow.h"

SketchWindow::SketchWindow(QWidget *parent) :
        QMainWindow(parent),
        canvas(this) {
    // 初始化窗口控件和各种布局调整
    this->initComponentsAndLayout();
    // 初始化信号和槽
    this->initSignalAndSlots();
    // 启用鼠标捕捉
    setMouseTracking(true);
}

SketchWindow::~SketchWindow() {}

void SketchWindow::initComponentsAndLayout() {
    // 窗体名
    this->setWindowTitle("Sketching Board");
    // 由于工具栏扩展窗体尺寸
    int tool_expansion_space = 240;
    QPixmap test_image((string(TEST_VIDEO_FIRST_FRAME_URL) + "00000.jpg").c_str());
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
    frame_label.setParent(this);
    frame_label.setText(QString::number(1));
    frame_label.setGeometry(test_image.width() + 10, 10, 30, 30);
    // 加入左移按钮
    left_button.setParent(this);
    left_button.setText("◀");
    left_button.setGeometry(test_image.width() + 50, 10, 30, 30);
    // 加入滚动条
    slider.setParent(this);
    slider.setOrientation(Qt::Horizontal);
    slider.setGeometry(test_image.width() + 90, 10, 100, 30);
    // 加入右移按钮
    right_button.setParent(this);
    right_button.setText("▶");
    right_button.setGeometry(test_image.width() + 200, 10, 30, 30);

}

void SketchWindow::initSignalAndSlots() {
    // 帧前进键的点击事件
    connect(&left_button, &QPushButton::clicked, this, &SketchWindow::onFrameLeftButtonClicked);
    // 帧后退键的点击事件
    connect(&right_button, &QPushButton::clicked, this, &SketchWindow::onFrameRightButtonClicked);

}

void SketchWindow::moveToCenter() {
    // 当前窗口几何位置成员
    auto qr = this->geometry();
    // 获取屏幕的中心点
    auto cp = this->screen()->availableGeometry().center();
    // 移动至中心点
    qr.moveCenter(cp);
    // 偏左上
    move(qr.topLeft());
}

void SketchWindow::onFrameLeftButtonClicked() {
    // 帧号自减
    canvas.frameCursorAutoDecrease();
    // 替换帧
    canvas.replaceFrame();
    // 变更帧号显示
    this->frame_label.setText(QString::number(canvas.getFrameCursor() + 1));
}

void SketchWindow::onFrameRightButtonClicked() {
    // 帧号自加
    canvas.frameCursorAutoIncrease();
    // 替换帧
    canvas.replaceFrame();
    // 变更帧号显示
    this->frame_label.setText(QString::number(canvas.getFrameCursor() + 1));
}

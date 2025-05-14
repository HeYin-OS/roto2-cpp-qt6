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
    int tool_expansion_space = 250;
    QPixmap test_image((g_frame0_url_head + "00000.jpg").c_str());
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
    // 加入帧功能区控件盒
    frame_box.setParent(this);
    frame_box.setTitle("Frame Control");
    frame_box.setGeometry(test_image.width() + 10, 0, 230, 60);
    // 加入标签显示当前帧的序号
    frame_label.setParent(this);
    frame_label.setText(QString::number(1));
    frame_label.setGeometry(frame_box.x() + 10, frame_box.y() + 20, 20, 30);
    // 加入左移按钮
    left_button.setParent(this);
    left_button.setText("◀");
    left_button.setGeometry((frame_label.x() + frame_label.width()) + 10, frame_box.y() + 20, 30, 30);
    // 加入滚动条
    slider.setParent(this);
    slider.setOrientation(Qt::Horizontal);
    slider.setGeometry((left_button.x() + left_button.width()) + 10, frame_box.y() + 20, 100, 30);
    slider.setRange(1, g_frame_num);
    slider.setSingleStep(1);
    slider.setTickPosition(QSlider::TicksBelow);
    // 加入右移按钮
    right_button.setParent(this);
    right_button.setText("▶");
    right_button.setGeometry((slider.x() + slider.width()) + 10, frame_box.y() + 20, 30, 30);
    // 加入绘画功能区控件盒
    draw_box.setParent(this);
    draw_box.setTitle("Draw Control");
    draw_box.setGeometry(frame_box.x(), frame_box.y() + frame_box.height() + 10, 230, 120);
    // 加入删除最近点组合按钮
    delete_prev_button.setParent(this);
    delete_prev_button.setText("Delete Prev");
    delete_prev_button.setGeometry(draw_box.x() + 10, draw_box.y() + 20, 100, 30);

}

void SketchWindow::initSignalAndSlots() {
    // 帧前进键的点击事件
    connect(&left_button, &QPushButton::clicked, this, &SketchWindow::onFrameLeftButtonClicked);
    // 帧后退键的点击事件
    connect(&right_button, &QPushButton::clicked, this, &SketchWindow::onFrameRightButtonClicked);
    // 滑动条的值改变事件
    connect(&slider, &QSlider::valueChanged, this, &SketchWindow::onFrameSliderValueChange);
    // 删除最近按钮的点击事件
    connect(&delete_prev_button, &QPushButton::clicked, this, &SketchWindow::onDeletePrevClicked);

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
    // 重画
    canvas.reDraw();
    // 变更帧号显示
    this->frame_label.setText(QString::number(canvas.getFrameCursor() + 1));
    // 更改滑块位置
    this->slider.setValue(canvas.getFrameCursor() + 1);
}

void SketchWindow::onFrameRightButtonClicked() {
    // 帧号自加
    canvas.frameCursorAutoIncrease();
    // 重画
    canvas.reDraw();
    // 变更帧号显示
    this->frame_label.setText(QString::number(canvas.getFrameCursor() + 1));
    // 更改滑块位置
    this->slider.setValue(canvas.getFrameCursor() + 1);
}

void SketchWindow::onFrameSliderValueChange() {
    // 按照滑块位置设置值
    canvas.setFrameCursor(this->slider.value() - 1);
    // 重画
    canvas.reDraw();
    // 变更帧号显示
    this->frame_label.setText(QString::number(canvas.getFrameCursor() + 1));
}

void SketchWindow::onDeletePrevClicked() {
    // 退回最近一次绘画操作
    canvas.curveInsertCursorRewind();
    // 重画
    canvas.reDraw();
}

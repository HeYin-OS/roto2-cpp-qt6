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

void SketchWindow::initSignalAndSlots() {
    // 帧前进键的点击事件
    connect(&left_button, &QPushButton::clicked, this, &SketchWindow::onFrameLeftButtonClicked);
    // 帧后退键的点击事件
    connect(&right_button, &QPushButton::clicked, this, &SketchWindow::onFrameRightButtonClicked);
    // 滑动条的值改变事件
    connect(&slider, &QSlider::valueChanged, this, &SketchWindow::onFrameSliderValueChange);
    // 帧1按钮的点击事件
    connect(&to_frame1_button, &QPushButton::clicked, this, &SketchWindow::onToFrameOneButtonClicked);
    // 帧2按钮的点击事件
    connect(&to_frame2_button, &QPushButton::clicked, this, &SketchWindow::onToFrameTwoButtonClicked);
    // 删除最近按钮的点击事件
    connect(&delete_prev_button, &QPushButton::clicked, this, &SketchWindow::onDeletePrevClicked);
    // 删除当前画布按钮的点击事件
    connect(&canvas_clear_button, &QPushButton::clicked, this, &SketchWindow::onClearCanvasButtonClicked);
    // 切换水平线可见度按钮的点击事件
    connect(&toggle_dir_line_button, &QPushButton::clicked, this, &SketchWindow::onToggleDirLineButtonClicked);
    // 切换终点可见度按钮的点击事件
    connect(&toggle_endpoint_button, &QPushButton::clicked, this, &SketchWindow::onToggleEndPointButtonClicked);
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

void SketchWindow::onToFrameOneButtonClicked() {
    // 从滚动条获取值
    auto frame_num = this->slider.value();
    // 设置值
    this->frame1_label.setText(QString::number(frame_num));
}

void SketchWindow::onToFrameTwoButtonClicked() {
    // 从滚动条获取值
    auto frame_num = this->slider.value();
    // 设置值
    this->frame2_label.setText(QString::number(frame_num));
}

void SketchWindow::onDeletePrevClicked() {
    // 退回最近一次绘画操作
    canvas.curveInsertCursorRewind();
    // 重画
    canvas.reDraw();
}

void SketchWindow::onClearCanvasButtonClicked() {
    // 重复删除
    while (canvas.getPointNum() > 0) {
        canvas.curveInsertCursorRewind();
    }
    // 重画
    canvas.reDraw();
}

void SketchWindow::onToggleDirLineButtonClicked() {
    // 切换可见度
    canvas.toggleDirectionLineVisibility();
    // 重画
    canvas.reDraw();
}

void SketchWindow::onToggleEndPointButtonClicked() {
    // 切换可见度
    canvas.toggleEndPointVisibility();
    // 重画
    canvas.reDraw();
}

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
    //
    // 帧功能区
    //
    frame_box.setParent(this);
    frame_box.setTitle("Frame");
    frame_box.setGeometry(test_image.width() + 10, 0, 230, 100);
    // 加入标签显示当前帧的序号
    frame_label.setParent(this);
    frame_label.setText(QString::number(1));
    frame_label.setGeometry(frame_box.x() + 10, frame_box.y() + 20, 20, 30);
    // 加入左移按钮
    left_button.setParent(this);
    left_button.setText("◀");
    left_button.setGeometry((frame_label.x() + frame_label.width()) + 10, frame_label.y(), 30, 30);
    // 加入滚动条
    slider.setParent(this);
    slider.setOrientation(Qt::Horizontal);
    slider.setGeometry(left_button.x() + left_button.width() + 10, frame_label.y(), 100, 30);
    slider.setRange(1, g_frame_num);
    slider.setSingleStep(1);
    slider.setTickPosition(QSlider::TicksBelow);
    // 加入右移按钮
    right_button.setParent(this);
    right_button.setText("▶");
    right_button.setGeometry(slider.x() + slider.width() + 10, frame_label.y(), 30, 30);
    // 加入转移键1
    to_frame1_button.setParent(this);
    to_frame1_button.setText("As 1st Frame");
    to_frame1_button.setGeometry(frame_label.x(), frame_label.y() + frame_label.height() + 10, 100, 30);
    // 加入转移键2
    to_frame2_button.setParent(this);
    to_frame2_button.setText("As 2nd Frame");
    to_frame2_button.setGeometry(to_frame1_button.x() + to_frame1_button.width() + 10, to_frame1_button.y(), 100, 30);
    //
    // 绘画功能区
    //
    draw_box.setParent(this);
    draw_box.setTitle("Edit");
    draw_box.setGeometry(frame_box.x(), frame_box.y() + frame_box.height() + 10, 230, 60);
    // 加入删除最近点组合按钮
    delete_prev_button.setParent(this);
    delete_prev_button.setText("Delete Latest");
    delete_prev_button.setGeometry(draw_box.x() + 10, draw_box.y() + 20, 100, 30);
    // 加入清楚当前帧全部笔迹按钮
    canvas_clear_button.setParent(this);
    canvas_clear_button.setText("Clear Canvas");
    canvas_clear_button.setGeometry(delete_prev_button.x() + delete_prev_button.width() + 10, delete_prev_button.y(), 100, 30);
    //
    // 显示功能区
    //
    show_box.setParent(this);
    show_box.setTitle("Display");
    show_box.setGeometry(draw_box.x(), draw_box.y() + draw_box.height() + 10, 230, 100);
    // 加入方向线显示按钮
    toggle_dir_line_button.setParent(this);
    toggle_dir_line_button.setText("Toggle Direction Line(s)");
    toggle_dir_line_button.setGeometry(show_box.x() + 10, show_box.y() + 20, 150, 30);
    // 加入端点显示按钮
    toggle_endpoint_button.setParent(this);
    toggle_endpoint_button.setText("Toggle End Point(s)");
    toggle_endpoint_button.setGeometry(toggle_dir_line_button.x(), toggle_dir_line_button.y() + toggle_dir_line_button.height() + 10, 150, 30);
    //
    // 优化功能区
    //
    opt_box.setParent(this);
    opt_box.setTitle("Optimize");
    opt_box.setStyleSheet( "QGroupBox {"
                           "    color: green;"
                           "    border: 1px solid green;"
                           "    margin-top: 1.5ex;"
                           "}"
                           "QGroupBox::title {"
                           "    subcontrol-origin: margin;"
                           "    left: 7px;"
                           "}"
                          );
    opt_box.setGeometry(show_box.x(), show_box.y() + show_box.height() + 10, 230, 60);
    // 加入拟合按钮
    fit_button.setParent(this);
    fit_button.setText("Fit Between");
    fit_button.setGeometry(opt_box.x() + 10, opt_box.y() + 20, 100, 30);
    // 加入帧1序号标签
    frame1_label.setParent(this);
    frame1_label.setText(QString::number(1));
    frame1_label.setAlignment(Qt::AlignCenter);
    frame1_label.setFrameStyle(QFrame::Panel | QFrame::Plain);
    frame1_label.setLineWidth(1);
    frame1_label.setGeometry(fit_button.x() + fit_button.width() + 10, fit_button.y(), 40, 30);
    // 加入帧2序号标签
    frame2_label.setParent(this);
    frame2_label.setText(QString::number(2));
    frame2_label.setAlignment(Qt::AlignCenter);
    frame2_label.setFrameStyle(QFrame::Panel | QFrame::Plain);
    frame2_label.setLineWidth(1);
    frame2_label.setGeometry(frame1_label.x() + frame1_label.width() + 20, frame1_label.y(), 40, 30);
}

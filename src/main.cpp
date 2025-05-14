#include "window/SketchWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", "1"); // 固定缩放比为 1
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0"); // 禁用自动缩放
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "0"); // 禁用高 DPI 缩放支持
    QApplication app(argc, argv);
    {
        QFont font = QApplication::font();
        font.setPixelSize(12);
        QApplication::setFont(font);
    }
    SketchWindow window(nullptr);
    window.show();
    return app.exec();
}
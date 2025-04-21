#include "window/SketchWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SketchWindow window(nullptr);
    window.show();
    return app.exec();
}
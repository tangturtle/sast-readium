#include "Widget.h"
#include <QApplication>
#include <controls/Slider.h>
#include <config.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setStyle("fusion");

    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VER);
    app.setApplicationDisplayName(APP_NAME);

    Widget w;
    w.show();

    return QApplication::exec();
}
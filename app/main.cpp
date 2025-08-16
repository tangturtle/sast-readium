#include <QApplication>
#include <config.h>
#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setStyle("fusion");

    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VER);
    app.setApplicationDisplayName(APP_NAME);

    MainWindow w;
    w.show();

    return QApplication::exec();
}
#include <QApplication>
#include <config.h>
#include "MainWindow.h"
#include "components/view/Views.h"
#include "components/model/PageModel.h"
#include "components/controller/Controller.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setStyle("fusion");

    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VER);
    app.setApplicationDisplayName(APP_NAME);

    PageModel model(5);
    Controller controller(&model);
    WidgetFactory factory(&controller);
    QLabel pageLabel;
    PageNavigationDelegate delegate(&pageLabel);
    Viewers viewers(&factory, &model, &delegate);
    
    MainWindow w;
    w.show();

    return QApplication::exec();
}
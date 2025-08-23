#pragma once

#include <QMainWindow>
#include <QSplitter>
#include "ui/MenuBar.h"
#include "ui/SideBar.h"
#include "ui/StatusBar.h"
#include "ui/ToolBar.h"
#include "ui/ViewWidget.h"
#include "components/controller/CoreController.h"
#include "components/model/DocumentModel.h"
#include "components/controller/Controller.h"
#include "components/model/PageModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private slots:
    void applyTheme(const QString &theme);

private:
    void initWindow();
    void initContent();

    MenuBar* menuBar;
    ToolBar* toolBar;
    SideBar* sideBar;
    StatusBar* statusBar;
    ViewWidget* viewWidget;
    
    QSplitter* mainSplitter;

    CoreController* controller;
    DocumentModel* doc;
    Controller* Ccontroller;
    PageModel* poc;
};
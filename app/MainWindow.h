#pragma once

#include <QMainWindow>
#include "components/MenuBar.h"
#include "components/SideBar.h"
#include "components/StatusBar.h"
#include "components/ToolBar.h"
#include "components/ViewWidget.h"

namespace Ui { 
    class MainWindow; 
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MenuBar *menuBar;
    ToolBar *toolBar;
    SideBar *sideBar;
    StatusBar *statusBar;
    ViewWidget *viewWidget;
};
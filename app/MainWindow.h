#pragma once

#include <QMainWindow>
#include <QSplitter>
#include "components/MenuBar.h"
#include "components/SideBar.h"
#include "components/StatusBar.h"
#include "components/ToolBar.h"
#include "components/ViewWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void initWindow();
    void initContent();

    MenuBar* menuBar;
    ToolBar* toolBar;
    SideBar* sideBar;
    StatusBar* statusBar;
    ViewWidget* viewWidget;
    
    QSplitter* mainSplitter;
};
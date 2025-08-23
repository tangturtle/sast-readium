#pragma once

#include <QMainWindow>
#include <QSplitter>
#include "controller/DocumentController.h"
#include "controller/PageController.h"
#include "model/DocumentModel.h"
#include "model/PageModel.h"
#include "ui/MenuBar.h"
#include "ui/SideBar.h"
#include "ui/StatusBar.h"
#include "ui/ToolBar.h"
#include "ui/ViewWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() noexcept;

private slots:
    void applyTheme(const QString& theme);

private:
    void initWindow();
    void initContent();
    void initModel();
    void initController();

    MenuBar* menuBar;
    ToolBar* toolBar;
    SideBar* sideBar;
    StatusBar* statusBar;
    ViewWidget* viewWidget;

    QSplitter* mainSplitter;

    DocumentController* documentController;
    // PageController* pageController;

    DocumentModel* documentModel;
    // PageModel* pageModel;
};
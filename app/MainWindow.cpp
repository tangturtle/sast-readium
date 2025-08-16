#include "MainWindow.h"
#include <QBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SAST Readium");
    resize(800, 600);

    menuBar = new MenuBar(this);
    toolBar = new ToolBar(this);
    sideBar = new SideBar(this);
    statusBar = new StatusBar(this);
    viewWidget = new ViewWidget(this);
    
    setMenuBar(menuBar);
    addToolBar(toolBar);
    setStatusBar(statusBar);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(viewWidget);
}

MainWindow::~MainWindow()
{
}
#include "MainWindow.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QFrame>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    initWindow();
    initContent();
}

MainWindow::~MainWindow() {}

void MainWindow::initWindow()
{
    resize(1280, 800);
}

void MainWindow::initContent()
{
    menuBar = new MenuBar(this);
    toolBar = new ToolBar(this);
    sideBar = new SideBar(this);
    statusBar = new StatusBar(this);
    viewWidget = new ViewWidget(this);

    setMenuBar(menuBar);
    addToolBar(toolBar);
    setStatusBar(statusBar);

    mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    mainSplitter->addWidget(sideBar);
    mainSplitter->addWidget(viewWidget);
    
    mainSplitter->setCollapsible(0, true);
    mainSplitter->setCollapsible(1, false);
    mainSplitter->setStretchFactor(1, 1); 
    mainSplitter->setSizes({200, 1000});  

    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(mainSplitter);
    setCentralWidget(centralWidget);
}
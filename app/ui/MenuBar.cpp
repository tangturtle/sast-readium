#include "MenuBar.h"
#include <QMenu>
#include <QAction>
#include <QActionGroup>

MenuBar::MenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    createFileMenu();
    createViewMenu();
    createThemeMenu();
}

void MenuBar::createFileMenu()
{
    QMenu* fileMenu = new QMenu(tr("文件(F)"), this);
    addMenu(fileMenu);

    QAction* openAction = new QAction(tr("打开"), this);
    openAction->setShortcut(QKeySequence("Ctrl+O"));

    QAction* saveAction = new QAction(tr("保存"), this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));

    QAction* exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));  

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    connect(openAction, &QAction::triggered, this, [this](){
        emit onExecuted(ActionMap::openFile);
    });
}

void MenuBar::createViewMenu()
{
    QMenu* viewMenu = new QMenu(tr("视图(V)"), this);
    addMenu(viewMenu);

    QAction* fullScreenAction = new QAction(tr("全屏"), this);
    fullScreenAction->setShortcut(QKeySequence("Ctrl+Shift+F"));

    QAction* zoomInAction = new QAction(tr("放大"), this);
    zoomInAction->setShortcut(QKeySequence("Ctrl++"));

    QAction* zoomOutAction = new QAction(tr("缩小"), this);
    zoomOutAction->setShortcut(QKeySequence("Ctrl+-"));

    viewMenu->addAction(fullScreenAction);
    viewMenu->addSeparator();
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
}

void MenuBar::createThemeMenu()
{
    QMenu* themeMenu = new QMenu(tr("主题(T)"), this);
    addMenu(themeMenu);
    
    QAction* lightThemeAction = new QAction(tr("浅色"), this);
    lightThemeAction->setCheckable(true);
    
    QAction* darkThemeAction = new QAction(tr("深色"), this);
    darkThemeAction->setCheckable(true);
    
    QActionGroup* themeGroup = new QActionGroup(this);
    themeGroup->addAction(lightThemeAction);
    themeGroup->addAction(darkThemeAction);

    connect(lightThemeAction, &QAction::triggered, this, [this](bool checked) {
        if (checked) {
            emit themeChanged("light");
        }
    });

    connect(darkThemeAction, &QAction::triggered, this, [this](bool checked) {
        if (checked) {
            emit themeChanged("dark");
        }
    });

    themeMenu->addAction(lightThemeAction);
    themeMenu->addAction(darkThemeAction);

    // init
    darkThemeAction->setChecked(true);
}
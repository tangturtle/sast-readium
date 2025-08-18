#include "MenuBar.h"
#include <QMenu>
#include <QAction>

MenuBar::MenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    createFileMenu();
    createViewMenu();
}

void MenuBar::createFileMenu()
{
    QMenu* fileMenu = new QMenu(tr("文件"));
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
}

void MenuBar::createViewMenu()
{
    QMenu* viewMenu = new QMenu(tr("视图"));
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
#include "MenuBar.h"
#include <QMenu>
#include <QAction>

MenuBar::MenuBar(QWidget *parent)
    : QMenuBar(parent)
{
    createFileMenu();
    createHelpMenu();
}

void MenuBar::createFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("File"));
    addMenu(fileMenu);

    QAction *openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));

    QAction *saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));

    QAction *exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));  

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void MenuBar::createHelpMenu()
{
    QMenu *fileMenu = new QMenu(tr("Help"));
    addMenu(fileMenu);

    QAction *AboutAction = new QAction(tr("About"), this);

    QAction *MoreAction = new QAction(tr("More"), this);

    fileMenu->addAction(AboutAction);
    fileMenu->addAction(MoreAction);
}
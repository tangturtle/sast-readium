#include "ToolBar.h"
#include <QAction>

ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(true);

    addAction(new QAction("ToolA", this));
    addAction(new QAction("ToolB", this));
}
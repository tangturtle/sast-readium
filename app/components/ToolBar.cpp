#include "ToolBar.h"
#include <QAction>

ToolBar::ToolBar(QWidget* parent)
    : QToolBar(parent)
{
    setMovable(true);

    addAction(new QAction("工具A", this));
    addAction(new QAction("工具B", this));
}
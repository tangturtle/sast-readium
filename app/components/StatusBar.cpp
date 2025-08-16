#include "StatusBar.h"
#include <QLabel>

StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent)
{
    QLabel *label = new QLabel(tr("Ready"));
    label->setAlignment(Qt::AlignCenter);
    addPermanentWidget(label);
}
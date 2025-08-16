#include "SideBar.h"
#include <QVBoxLayout>
#include <QLabel>

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("SideBar Content", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
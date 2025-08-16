#include "ViewWidget.h"
#include <QVBoxLayout>
#include <QLabel>

ViewWidget::ViewWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("PDF Content Here");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
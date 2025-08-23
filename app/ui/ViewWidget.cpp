#include "ViewWidget.h"
#include <QLabel>
#include <QVBoxLayout>

ViewWidget::ViewWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("PDF渲染窗口");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
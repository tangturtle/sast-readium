#include "StatusBar.h"
#include <QHBoxLayout>
#include <QLabel>

StatusBar::StatusBar(QWidget* parent) : QStatusBar(parent) {
    // init
    pageLabel = new QLabel("页: 1/1", this);
    pageLabel->setMinimumWidth(100);
    pageLabel->setAlignment(Qt::AlignCenter);

    zoomLabel = new QLabel("比例: 100%", this);
    zoomLabel->setMinimumWidth(100);
    zoomLabel->setAlignment(Qt::AlignCenter);

    addPermanentWidget(pageLabel);
    addPermanentWidget(zoomLabel);
}

StatusBar::StatusBar(WidgetFactory* factory, QWidget* parent)
    : StatusBar(parent)
{
    QPushButton* prevButton = factory->createButton(actionID::prev, "Prev");
    QPushButton* nextButton = factory->createButton(actionID::next, "Next");

    addWidget(prevButton);
    addWidget(nextButton);
}

void StatusBar::setPageInfo(int current, int total) {
    pageLabel->setText(QString("页: %1/%2").arg(current).arg(total));
}

void StatusBar::setZoomLevel(int percent) {
    zoomLabel->setText(QString("比例: %1%").arg(percent));
}

void StatusBar::setMessage(const QString& message) {
    showMessage(message, 3000);
}
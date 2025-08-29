
#include "ViewWidget.h"

ViewWidget::ViewWidget(QWidget* parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setRenderHint(QPainter::TextAntialiasing, true);
    view->setRenderHint(QPainter::SmoothPixmapTransform, true);
    view->setAlignment(Qt::AlignCenter);
    pixmapItem = nullptr;
    layout->addWidget(view);
    setLayout(layout);
    setMinimumSize(200, 200);
    setAutoFillBackground(true);
}


void ViewWidget::changeImage(const QImage& image) {
    scene->clear();
    if (image.isNull()) {
        pixmapItem = nullptr;
        return;
    }
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmapItem = scene->addPixmap(pixmap);
    pixmapItem->setTransformationMode(Qt::SmoothTransformation);
    scene->setSceneRect(pixmap.rect());
    view->fitInView(pixmapItem, Qt::KeepAspectRatio);
}
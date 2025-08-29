#include "ViewWidget.h"

ViewWidget::ViewWidget(QWidget* parent) : QGraphicsView(parent), currentScale(1.0), maxScale(4.0), minScale(0.25) {
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void ViewWidget::changeImage(const QImage& image) {
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "无法渲染页面");
        return;
    }
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->clear();
    scene->addItem(item);

    this->fitInView(item, Qt::KeepAspectRatio);
    emit scaleChanged(currentScale);
}

void ViewWidget::zoomIn() {
    currentScale *= 1.25; 
    if (currentScale > maxScale) {
        currentScale = maxScale; 
    }
    scale(1.25, 1.25);
    emit scaleChanged(currentScale);
}

void ViewWidget::zoomOut() {
    currentScale *= 0.8;
    if (currentScale < minScale) {
        currentScale = minScale;
    }
    scale(0.8, 0.8);
    emit scaleChanged(currentScale);
}
#include "ViewWidget.h"

ViewWidget::ViewWidget(QWidget* parent) : QGraphicsView(parent) {
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
}

void ViewWidget::zoomIn() {
    scale(1.25, 1.25);
}

void ViewWidget::zoomOut() {
    scale(0.8, 0.8);
}
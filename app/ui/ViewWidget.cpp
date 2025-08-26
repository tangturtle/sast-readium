#include "ViewWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

ViewWidget::ViewWidget(QWidget* parent) : QWidget(parent) {
    // 不再使用 QLabel，直接用 QPainter 绘制
    setMinimumSize(200, 200);
    setAutoFillBackground(true);
}

void ViewWidget::changeImage(const QImage& image) {
    if(image.isNull()){
        currentImage = QImage();
        update();
        return;
    }
    currentImage = image;
    update();
}

void ViewWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing, true);
    if(currentImage.isNull()) {
        painter.drawText(rect(), Qt::AlignCenter, "无法渲染页面");
        return;
    }
    // 计算缩放后大小，保持比例
    QSize widgetSize = size();
    QSize imgSize = currentImage.size();
    imgSize.scale(widgetSize, Qt::KeepAspectRatio);
    int x = (widgetSize.width() - imgSize.width()) / 2;
    int y = (widgetSize.height() - imgSize.height()) / 2;
    painter.drawImage(QRect(x, y, imgSize.width(), imgSize.height()), currentImage);
}
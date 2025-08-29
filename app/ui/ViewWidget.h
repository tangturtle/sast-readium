#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>

class ViewWidget : public QGraphicsView {
    Q_OBJECT

public:
    ViewWidget(QWidget* parent = nullptr);
    void changeImage(const QImage& image);

public slots:
    void zoomIn();
    void zoomOut();

private:
    QGraphicsScene* scene;
};
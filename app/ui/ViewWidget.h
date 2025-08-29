#pragma once


#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include "qtmetamacros.h"

class ViewWidget : public QWidget {
    Q_OBJECT
public:
    ViewWidget(QWidget* parent = nullptr);
public slots:
    void changeImage(const QImage& image);
private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmapItem;
    QVBoxLayout* layout;
};
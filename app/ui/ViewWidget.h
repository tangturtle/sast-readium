#pragma once

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QImage>
#include <QPixmap>
#include "qtmetamacros.h"

class ViewWidget : public QWidget {
    Q_OBJECT

public:
    ViewWidget(QWidget* parent = nullptr);
public slots:
    void changeImage(const QImage& image);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QImage currentImage;
};
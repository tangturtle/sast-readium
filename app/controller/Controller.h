#pragma once

#include <QObject>

class PageModel;

class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(PageModel* model, QObject* parent = nullptr);
    ~Controller() {};

public slots:
    void goTonextPage();
    void goToprevPage();

private:
    PageModel* _model;
};
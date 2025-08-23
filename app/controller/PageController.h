#pragma once

#include <QObject>

class PageModel;

class PageController : public QObject {
    Q_OBJECT

public:
    PageController(PageModel* model, QObject* parent = nullptr);
    ~PageController() {};

public slots:
    void goToNextPage();
    void goToPrevPage();

private:
    PageModel* _model;
};
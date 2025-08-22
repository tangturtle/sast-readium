#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include <QObject>

class PageModel;

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller(PageModel* model,QObject* parent = nullptr);
    ~Controller(){};
public slots:
    void goTonextPage();
    void goToprevPage();
    
private:
    PageModel* _model;
};
#endif // CONTROLLER_CONTROLLER_H
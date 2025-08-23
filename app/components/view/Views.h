#ifndef VIEW_VIEWS_H
#define VIEW_VIEWS_H

#include <QMainWindow>
#include <QPushButton>

#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QMap>
#include <QLabel>

class Controller;
class Command;
class PageModel;

#include "../delegate/PageNavigationDelegate.h"
#include "../factory/WidgetFactory.h"

class Views : public QWidget{
    Q_OBJECT
public:
    Views(WidgetFactory* factory,PageModel* model,PageNavigationDelegate* delegate,QWidget* parent = nullptr);

private:
    void initUI();

    WidgetFactory* _factory;
    PageModel* _model;
    PageNavigationDelegate* _delegate;
    QLabel* _pageLabel;
};
#endif // VIEW_VIEWS_H
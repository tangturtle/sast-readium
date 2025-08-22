#ifndef VIEW_VIEWS_H
#define VIEW_VIEWS_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QMap>

class Controller;
class Command;
class PageModel;

class WidgetFactory : public QObject {
    Q_OBJECT
public:
    explicit WidgetFactory(Controller* controller, QObject* parent = nullptr);
    QPushButton* createButton(const QString& actionID,const QString& text);

private:
    Controller* _controller;
    QMap<QString,Command*> _actionMap;
    
};

class PageNavigationDelegate : public QObject {
    Q_OBJECT
public:
    explicit PageNavigationDelegate(QLabel* pageLabel,QObject* parent = nullptr);
public slots:
    void viewUpdate(int pageNum);
    // void handleDocumentLoaded();
private:
    QLabel* _pageLabel;
    PageModel* _model;
};

class Viewers : public QWidget{
    Q_OBJECT
public:
    explicit Viewers(WidgetFactory* factory,PageModel* model,PageNavigationDelegate* delegate,QWidget* parent = nullptr);
private:
    void initUI();

    WidgetFactory* _factory;
    PageModel* _model;
    PageNavigationDelegate* _delegate;
    QLabel* _pageLabel;
    
};
#endif // VIEW_VIEWS_H
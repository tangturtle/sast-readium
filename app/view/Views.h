#pragma once

#include <QMainWindow>
#include <QPushButton>

#include <QMap>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

class PageController;
class Command;
class PageModel;
class PageNavigationDelegate;

class WidgetFactory : public QObject {
    Q_OBJECT
public:
    explicit WidgetFactory(PageController* controller, QObject* parent = nullptr);
    QPushButton* createButton(const QString& actionID, const QString& text);

private:
    PageController* _controller;
    QMap<QString, Command*> _actionMap;
};

class Viewers : public QWidget {
    Q_OBJECT
public:
    explicit Viewers(WidgetFactory* factory, PageModel* model,
                     PageNavigationDelegate* delegate,
                     QWidget* parent = nullptr);

private:
    // void initUI();

    WidgetFactory* _factory;
    PageModel* _model;
    PageNavigationDelegate* _delegate;
};
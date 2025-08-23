#ifndef FACTORY_WIDGETFACTORY_H
#define FACTORY_WIDGETFACTORY_H

#include <QObject>
#include <QPushButton>
#include <QMap>

class Controller;
class Command;

enum actionID{
    next,
    prev
};
class WidgetFactory : public QObject {
    Q_OBJECT
public:
    WidgetFactory(Controller* controller, QObject* parent = nullptr);

    QPushButton* createButton(actionID actionID, const QString& text);

    ~WidgetFactory() {}
        
private:
    Controller* _controller;
    QMap<actionID, Command*> _actionMap;
};

#endif // FACTORY_WIDGETFACTORY_H
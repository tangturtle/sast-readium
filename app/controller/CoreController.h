#pragma once

#include <QWidget>
#include "tool.hpp"

class CoreController : public QObject
{
    Q_OBJECT
private:
    void execute(ActionMap actionID, QWidget* context);
public:
    CoreController(){};
    ~CoreController(){};
};


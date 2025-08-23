#ifndef COMMAND_COMMANDS_H
#define COMMAND_COMMANDS_H

#include <QObject>

class Controller;

class Command : public QObject {
    Q_OBJECT
public:
    Command(QObject* parent = nullptr);
    ~Command(){};
public slots:
    virtual void execute() = 0;
};

class PrevPageCommand : public Command {
    Q_OBJECT
public:
    PrevPageCommand(Controller* controller, QObject* parent = nullptr);
public slots:
    void execute() override;
private:
    Controller* _controller;
};

class NextPageCommand : public Command {
    Q_OBJECT
public:
    NextPageCommand(Controller* controller, QObject* parent = nullptr);
public slots:
    void execute() override;
private:
    Controller* _controller;
};
#endif // COMMAND_COMMANDS_H
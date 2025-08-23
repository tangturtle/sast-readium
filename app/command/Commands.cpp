#include "Commands.h"
#include "../controller/Controller.h"
Command::Command(QObject* parent) : QObject(parent) {}

PrevPageCommand::PrevPageCommand(Controller* controller, QObject* parent)
    : Command(parent), _controller(controller) {}

void PrevPageCommand::execute() {
    if (_controller) {
        _controller->goToprevPage();
    }
}

NextPageCommand::NextPageCommand(Controller* controller, QObject* parent)
    : Command(parent), _controller(controller) {}

void NextPageCommand::execute() {
    if (_controller) {
        _controller->goTonextPage();
    }
}

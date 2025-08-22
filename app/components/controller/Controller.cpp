#include "Controller.h"
#include "../model/PageModel.h"

Controller::Controller(PageModel* model, QObject* parent)
    : QObject(parent), _model(model)
{
}

void Controller::goTonextPage()
{
    if (_model) {
        _model->nextPage();
    }
}

void Controller::goToprevPage()
{
    if (_model) {
        _model->prevPage();
    }
}


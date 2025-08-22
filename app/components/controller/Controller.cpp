#include "Controller.h"
#include "../model/PageModel.h"

Controller::Controller(PageModel* model, QObject* parent)
    : QObject(parent), _model(model)
{
}

void Controller::goTonextPage()
{
    if (_model) {
        _model->PageModel::nextPage();
    }
}

void Controller::goToprevPage()
{
    if (_model) {
        _model->prevPage();
    }
}

// void Controller::openFile(const QString& filePath){
//     if (_model) {
//         _model->loadDocument(filePath);
//     }
// }
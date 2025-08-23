#include "PageController.h"
#include "../model/PageModel.h"

PageController::PageController(PageModel* model, QObject* parent)
    : QObject(parent), _model(model) {}

void PageController::goToNextPage() {
    if (_model) {
        _model->nextPage();
    }
}

void PageController::goToPrevPage() {
    if (_model) {
        _model->prevPage();
    }
}

#include "CoreController.h"

CoreController::CoreController(PDFModel* pdf)
    :pdfDocument(pdf) {}

void CoreController::execute(ActionMap actionID, QWidget* context) {
    qDebug() << "EventID:" << actionID << "context" << context;
    switch (actionID)
    {
        case ActionMap::openFile :
            if(!pdfDocument->isNULL()){
                pdfDocument->openFromFile();
            }
            break;
        
        default:
            break;
    }
}
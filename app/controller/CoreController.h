#pragma once

#include <QWidget>
#include "tool.hpp"
#include "../model/DocumentModel.h"

class CoreController : public QObject
{
    Q_OBJECT
private:
    DocumentModel* pdfDocument;
public:
    CoreController(DocumentModel* pdf);
    ~CoreController(){};
    void execute(ActionMap actionID, QWidget* context);
};


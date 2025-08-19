#pragma once

#include <QWidget>
#include "tool.hpp"
#include "../model/PDFModel.h"

class CoreController : public QObject
{
    Q_OBJECT
private:
    PDFModel* pdfDocument;
public:
    CoreController(PDFModel* pdf);
    ~CoreController(){};
    void execute(ActionMap actionID, QWidget* context);
};


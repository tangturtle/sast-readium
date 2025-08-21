#pragma once

#include <QWidget>
#include <QStandardPaths>
#include "tool.hpp"
#include "../model/DocumentModel.h"

class CoreController : public QObject
{
    Q_OBJECT
private:
    DocumentModel* pdfDocument;
    QHash<ActionMap, std::function<void(QWidget*)>> commandMap;
    void initializeCommandMap();
public:
    CoreController(DocumentModel* pdf);
    ~CoreController(){};
    void execute(ActionMap actionID, QWidget* context);
};


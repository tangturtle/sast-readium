#pragma once

#include <QStandardPaths>
#include <QWidget>
#include "../model/DocumentModel.h"
#include "tool.hpp"

class CoreController : public QObject {
    Q_OBJECT

private:
    DocumentModel* pdfDocument;
    QHash<ActionMap, std::function<void(QWidget*)>> commandMap;
    void initializeCommandMap();

public:
    CoreController(DocumentModel* pdf);
    ~CoreController() {};
    void execute(ActionMap actionID, QWidget* context);
};

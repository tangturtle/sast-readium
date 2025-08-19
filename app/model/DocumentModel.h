#pragma once

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <poppler/qt6/poppler-qt6.h>

class DocumentModel : public QObject
{
    Q_OBJECT
private:
    QString filePath;
    std::unique_ptr<Poppler::Document> document;
public:
    DocumentModel(){};
    ~DocumentModel(){};
    bool isNULL();
    bool openFromFile();
};


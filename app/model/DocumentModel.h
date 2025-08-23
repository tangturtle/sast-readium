#pragma once

#include <poppler/qt6/poppler-qt6.h>
#include <QFileDialog>
#include <QObject>
#include <QString>

class DocumentModel : public QObject {
    Q_OBJECT

private:
    QString currentFilePath;
    std::unique_ptr<Poppler::Document> document;

public:
    DocumentModel() {};
    ~DocumentModel() {};
    bool isNULL();
    bool openFromFile(const QString& filePath);
};

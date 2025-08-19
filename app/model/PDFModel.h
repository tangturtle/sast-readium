#pragma once

#include <QObject>
#include <QString>
#include <QFileDialog>
// #include <poppler/qt6/poppler-qt6.h>

class PDFModel : public QObject
{
    Q_OBJECT
private:
    QString filePath;
    // std::unique_ptr<Poppler::Document> document;
public:
    PDFModel(){};
    ~PDFModel(){};
    bool isNULL();
    bool openFromFile();
};


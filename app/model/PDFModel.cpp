#include "PDFModel.h"

bool PDFModel::isNULL() { 
    return false; 
}

bool PDFModel::openFromFile() { 
    QWidget a;
    QFileDialog file(&a);
    file.setFileMode(QFileDialog::AnyFile);
    file.setNameFilter(tr("PDFDocument (*.pdf)"));
    file.setViewMode(QFileDialog::Detail);
    QString path = file.getOpenFileName();
    auto _document = Poppler::Document::load(path);
    if (_document)
    {
        document = std::move(_document);
        qDebug() << tr("打开成功") << path;
        return true;
    }
    qDebug() << tr("打开失败") << path;
    return false;
}

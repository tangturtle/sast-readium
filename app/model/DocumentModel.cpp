#include "DocumentModel.h"

bool DocumentModel::isNULL() { 
    return false; 
}

bool DocumentModel::openFromFile(const QString& filePath) { 
    if (filePath.isEmpty() || !QFile::exists(filePath)){
        qWarning() << "Invalid file path:" << filePath;
        return false;
    }

    auto _document = Poppler::Document::load(filePath);
    if (!_document) {
        qDebug() << "Failed to load document:" << filePath;
        return false;
    }

    document = std::move(_document);
    currentFilePath = filePath;
    qDebug() << "Opened successfully:" << filePath;
    
    return true;
}

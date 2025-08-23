#include "PageModel.h"

PageModel::PageModel(int totalPages, QObject* parent)
    : QObject(parent), _totalPages(totalPages), _currentPage(1) {}

int PageModel::currentPage() const { return _currentPage; }

int PageModel::totalPages() const { return _totalPages; }

void PageModel::setCurrentPage(int pageNum) {
    if (pageNum >= 1 && pageNum <= _totalPages && pageNum != _currentPage) {
        _currentPage = pageNum;
        emit pageUpdate(_currentPage);
    }
}

void PageModel::nextPage() {
    if (_currentPage < _totalPages) {
        setCurrentPage(++_currentPage);
    }
}

void PageModel::prevPage() {
    if (_currentPage > 1) {
        setCurrentPage(--_currentPage);
    }
}

// void PageModel::loadDocument(const QString& filePath) {
//     _document = Poppler::Document::load(filePath);
//     if (_document) {
//         _totalPages = _document->numPages();
//         _currentPage = 1;
//         emit documentLoaded();
//         emit pageUpdate(_currentPage);
//     } else {
//         qWarning() << "Failed to load document from" << filePath;
//     }
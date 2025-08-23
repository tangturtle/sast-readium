#pragma once

#include <QObject>
// #include <poppler/qt5/poppler-qt5.h>
#include <QSharedPointer>

class PageModel : public QObject {
    Q_OBJECT

public:
    explicit PageModel(int totalPages = 1, QObject* parent = nullptr);

    int currentPage() const;
    int totalPages() const;

    // void loadDocument(const QString& filePath);
    // QSharedPointer<Poppler::Document> getDocument() const;

    void setCurrentPage(int pageNum);
    void nextPage();
    void prevPage();

    ~PageModel() = default;

signals:
    void pageUpdate(int currentPage);
    // void documentLoaded();

private:
    int _totalPages;
    int _currentPage;
    // QSharedPointer<Poppler::Document> _document;
};
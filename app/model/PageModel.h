#pragma once

#include <QObject>
#include <QSharedPointer>

class PageModel : public QObject {
    Q_OBJECT

public:
    PageModel(int totalPages = 1, QObject* parent = nullptr);

    int currentPage() const;
    int totalPages() const;

    void setCurrentPage(int pageNum);
    void nextPage();
    void prevPage();

    ~PageModel(){};

signals:
    void pageUpdate(int currentPage);

private:
    int _totalPages;
    int _currentPage;
};
#pragma once

#include <QMessageBox>
#include <QObject>
#include <QSharedPointer>
#include "RenderModel.h"

class PageModel : public QObject {
    Q_OBJECT

public:
    PageModel(int totalPages = 1, QObject* parent = nullptr);
    PageModel(RenderModel* renderModel, QObject* parent = nullptr);

    int currentPage() const;
    int totalPages() const;

    void setCurrentPage(int pageNum);
    void nextPage();
    void prevPage();

    ~PageModel(){};

public slots:
    void updateInfo(Poppler::Document* document);

signals:
    void pageUpdate(int currentPage, int totalPages);

private:
    int _totalPages;
    int _currentPage;
    RenderModel* _renderModel;
};

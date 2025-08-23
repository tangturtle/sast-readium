#pragma once

#include <QLabel>
#include <QObject>

class PageNavigationDelegate : public QObject {
    Q_OBJECT

public:
    explicit PageNavigationDelegate(QLabel* pageLabel,
                                    QObject* parent = nullptr);

public slots:
    void viewUpdate(int pageNum);
    // void handleDocumentLoaded();

private:
    QLabel* _pageLabel;
};
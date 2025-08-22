#ifndef DELEGATE_PAGENAVIGATIONDELEGATE_H
#define DELEGATE_PAGENAVIGATIONDELEGATE_H
#include <QObject>
#include <QLabel>
class PageNavigationDelegate : public QObject {
    Q_OBJECT
public:
    explicit PageNavigationDelegate(QLabel* pageLabel,QObject* parent = nullptr);
public slots:
    void viewUpdate(int pageNum);
    // void handleDocumentLoaded();
private:
    QLabel* _pageLabel;
};
#endif
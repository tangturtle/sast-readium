#ifndef DELEGATE_PAGENAVIGATIONDELEGATE_H
#define DELEGATE_PAGENAVIGATIONDELEGATE_H
#include <QObject>
#include <QLabel>
class PageNavigationDelegate : public QObject {
    Q_OBJECT
public:
    PageNavigationDelegate(QLabel* pageLabel,QObject* parent = nullptr);
    ~PageNavigationDelegate(){};
public slots:
    void viewUpdate(int pageNum);
private:
    QLabel* _pageLabel;
};
#endif
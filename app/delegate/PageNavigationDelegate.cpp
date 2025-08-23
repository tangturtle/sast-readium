#include "PageNavigationDelegate.h"

PageNavigationDelegate::PageNavigationDelegate(QLabel* pageLabel,
                                               QObject* parent)
    : QObject(parent), _pageLabel(pageLabel) {}

void PageNavigationDelegate::viewUpdate(int pageNum) {
    _pageLabel->setText("Page: " + QString::number(pageNum));
}

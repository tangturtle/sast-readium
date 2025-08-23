#include "SideBar.h"
#include <QLabel>
#include <QListView>
#include <QTreeView>
#include <QVBoxLayout>

SideBar::SideBar(QWidget* parent) : QWidget(parent) {
    initWindow();
    initContent();
}

void SideBar::initWindow() {
    setMinimumWidth(200);
    setMaximumWidth(400);
}

void SideBar::initContent() {
    tabWidget = new QTabWidget(this);

    QWidget* thumbnailsTab = createThumbnailsTab();
    QWidget* bookmarksTab = createBookmarksTab();

    tabWidget->addTab(thumbnailsTab, "缩略图");
    tabWidget->addTab(bookmarksTab, "书签");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
}

QWidget* SideBar::createThumbnailsTab() {
    QWidget* thumbnailsTab = new QWidget();
    QVBoxLayout* thumbLayout = new QVBoxLayout(thumbnailsTab);

    QListView* thumbnailView = new QListView();
    thumbLayout->addWidget(thumbnailView);

    return thumbnailsTab;
}

QWidget* SideBar::createBookmarksTab() {
    QWidget* bookmarksTab = new QWidget();
    QVBoxLayout* bookmarkLayout = new QVBoxLayout(bookmarksTab);

    QTreeView* bookmarksView = new QTreeView();
    bookmarkLayout->addWidget(bookmarksView);

    return bookmarksTab;
}
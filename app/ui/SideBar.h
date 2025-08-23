#pragma once

#include <QTabWidget>
#include <QWidget>

class SideBar : public QWidget {
    Q_OBJECT
public:
    SideBar(QWidget* parent = nullptr);

private:
    QTabWidget* tabWidget;

    void initWindow();
    void initContent();

    QWidget* createThumbnailsTab();
    QWidget* createBookmarksTab();
};
#pragma once

#include <QWidget>
#include <QTabWidget>

class SideBar : public QWidget
{
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
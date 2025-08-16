#pragma once

#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT

public:
    MenuBar(QWidget *parent = nullptr);

private:
    void createFileMenu();
    void createHelpMenu();
};
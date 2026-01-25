#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::SearchWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);
}

SearchWindow::~SearchWindow()
{
    delete this->ui;
}

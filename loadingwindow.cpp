#include "loadingwindow.h"
#include "ui_loadingwindow.h"

LoadingWindow::LoadingWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::LoadingWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);
}

LoadingWindow::~LoadingWindow()
{
    delete this->ui;
}

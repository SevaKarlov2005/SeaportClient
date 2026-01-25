#include "storagewindow.h"
#include "ui_storagewindow.h"

StorageWindow::StorageWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::StorageWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);
}

StorageWindow::~StorageWindow()
{
    delete this->ui;
}

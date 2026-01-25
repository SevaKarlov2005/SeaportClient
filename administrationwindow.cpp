#include "administrationwindow.h"
#include "ui_administrationwindow.h"

AdministrationWindow::AdministrationWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::AdministrationWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);
}

AdministrationWindow::~AdministrationWindow()
{
    delete this->ui;
}

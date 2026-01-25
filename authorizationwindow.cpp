#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::AuthorizationWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(965, 260);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete this->ui;
}

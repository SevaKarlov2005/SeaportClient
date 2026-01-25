#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include <QRegularExpressionValidator>

AuthorizationWindow::AuthorizationWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::AuthorizationWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(965, 260);

    // Регулярное выражение
    QRegularExpression pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-z\-]{12,16})");

    // Установка валидаторов на поля ввода
    this->ui->username_edit->setValidator(new QRegularExpressionValidator(pattern));
    this->ui->password_edit->setValidator(new QRegularExpressionValidator(pattern));
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete this->ui;
}

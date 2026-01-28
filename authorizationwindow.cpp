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

    // Установка связей между сигналами и методами
    connect(this->ui->username_edit, &QLineEdit::textChanged, this, &AuthorizationWindow::CheckAuthorizationForm);
    connect(this->ui->password_edit, &QLineEdit::textChanged, this, &AuthorizationWindow::CheckAuthorizationForm);
    connect(this->ui->enter_button, &QPushButton::clicked, this, &AuthorizationWindow::Enter);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete this->ui;
}

void AuthorizationWindow::CheckAuthorizationForm()
{
    // Длины имени пользователя и пароля
    int username_length = this->ui->username_edit->text().length();
    int password_length = this->ui->password_edit->text().length();

    // Проверка имени пользователя
    if (username_length >= 12 && username_length <= 16)
    {
        this->ui->username_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->username_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_note_label->setText("* Обязательно для заполнения");
    }
    else
    {
        this->ui->username_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->username_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_note_label->setText("* Длина меньше 12 символов");
    }

    // Проверка пароля
    if (password_length >= 12 && password_length <= 16)
    {
        this->ui->password_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->password_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_note_label->setText("* Обязательно для заполнения");
    }
    else
    {
        this->ui->password_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->password_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_note_label->setText("* Длина меньше 12 символов");
    }

    // Управление кнопкой
    if (username_length >= 12 && username_length <= 16 &&
        password_length >= 12 && password_length <= 16)
        this->ui->enter_button->setEnabled(true);
    else
        this->ui->enter_button->setEnabled(false);
}

void AuthorizationWindow::Enter()
{
    // TODO проверить существование пользователя

    // Заглушка входа
    bool is_work = true;
    bool is_user = true;

    if (!is_work)
    {
        this->ui->enter_label->setStyleSheet("color: #F5F116;");
        this->ui->enter_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_user)
        {
            this->ui->enter_label->setStyleSheet("color: #F5F116;");
            this->ui->enter_label->setText("* Пользователь не найден");
        }
        else
        {
            this->ui->username_edit->clear();
            this->ui->password_edit->clear();

            this->ui->username_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->username_note_label->setStyleSheet("color: #FFFFFF;");
            this->ui->username_note_label->setText("* Обязательно для заполнения");

            this->ui->password_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->password_note_label->setStyleSheet("color: #FFFFFF;");
            this->ui->password_note_label->setText("* Обязательно для заполнения");
        }
    }
}

#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "administrationwindow.h"
#include "searchwindow.h"
#include "storagewindow.h"
#include "planningwindow.h"
#include "loadingwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::AuthorizationWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(965, 260);

    // Установка хоста
    this->host = "10.240.138.246";

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
    this->connection.Disconnect();
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
    // Флаги проверок
    bool is_work = true;
    bool is_user = true;

    // Результат работы сервера
    QString result;

    // Устанавливаем соединение с сервером
    is_work = this->connection.Connect(this->host, 8081);

    if (is_work)
    {
        // Шифруем пароль
        QString en_password = this->connection.Encryption(this->ui->password_edit->text());

        // Отправляем сообщение
        is_work = this->connection.Send("I00" + this->ui->username_edit->text() + '\v' + en_password);

        if (is_work)
        {
            // Принимаем сообщение
            result = this->connection.Receive();

            is_work = result != "\x18";

            if (is_work)
                is_user = result != "\x00";
        }

        // Удаляем соединение
        if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            this->connection.Disconnect();
    }

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

            this->ui->enter_label->clear();

            this->ui->username_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->username_note_label->setStyleSheet("color: #FFFFFF;");
            this->ui->username_note_label->setText("* Обязательно для заполнения");

            this->ui->password_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->password_note_label->setStyleSheet("color: #FFFFFF;");
            this->ui->password_note_label->setText("* Обязательно для заполнения");
        }
    }

    if (is_work)
    {
        // Активируем окно
        if (is_user)
        {
            QStringList list = result.split('\v');

            hide();

            if (list[4] == "Администратор")
            {
                AdministrationWindow* w = new AdministrationWindow(list[1], list[2], list[3], list[5]);

                connect(w, &QMainWindow::destroyed, this, &AuthorizationWindow::show);
                w->show();
            }
            else if (list[4] == "Таможенник")
            {
                SearchWindow* w = new SearchWindow(list[1], list[2], list[3], list[5]);

                connect(w, &QMainWindow::destroyed, this, &AuthorizationWindow::show);
                w->show();
            }
            else if (list[4] == "Тальман")
            {
                StorageWindow* w = new StorageWindow(list[1], list[2], list[3], list[5]);

                connect(w, &QMainWindow::destroyed, this, &AuthorizationWindow::show);
                w->show();
            }
            else if (list[4] == "Диспетчер")
            {
                PlanningWindow* w = new PlanningWindow(list[1], list[2], list[3], list[5]);

                connect(w, &QMainWindow::destroyed, this, &AuthorizationWindow::show);
                w->show();
            }
            else if (list[4] == "Стивидор")
            {
                LoadingWindow* w = new LoadingWindow(list[1], list[2], list[3], list[5]);

                connect(w, &QMainWindow::destroyed, this, &AuthorizationWindow::show);
                w->show();
            }
        }
    }
    else
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

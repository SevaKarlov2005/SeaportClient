#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>

SearchWindow::SearchWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::SearchWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

    // Удаление окна при закрытии
    setAttribute(Qt::WA_DeleteOnClose);

    // Отображение ФИО
    this->ui->surname_label->setText("Фамилия: " + surname);
    this->ui->name_label->setText("Имя: " + name);
    this->ui->patronym_label->setText("Отчество: " + patronym);

    // Установка хоста и имени пользователя
    this->host = "10.240.138.246";
    this->username = username;

    // Инициализация таблицы заявок
    this->bid_page = 1;

    this->bid_model = new QStandardItemModel(0, 4);
    this->bid_model->setHeaderData(0, Qt::Horizontal, "Идентификатор\nзаявки");
    this->bid_model->setHeaderData(1, Qt::Horizontal, "Дата подачи\nзаявки");
    this->bid_model->setHeaderData(2, Qt::Horizontal, "Дата последнего\nизменения");
    this->bid_model->setHeaderData(3, Qt::Horizontal, "Статус");
    this->ui->bid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->bid_table->setModel(this->bid_model);

    // Установка страниц форм
    this->bid_read_page = 1;

    // Регулярные выражения для валидаторов
    QRegularExpression bid_id_pattern(R"([0-9]{5}-[0-9]{2}/ОМиДР)");
    QRegularExpression date_pattern(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.[0-9]{2})");

    // Установка валидатора для работы с заявкой
    this->ui->bid_id_work_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка валидаторов для фильтра заявок
    this->ui->bid_id_filter_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));
    this->ui->bid_date_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));
    this->ui->bid_change_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));

    // Установка валидатора для просмотра заявки
    this->ui->bid_id_read_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка связей между сигналами и методами для работы с заявкой
    connect(this->ui->bid_id_work_edit, &QLineEdit::textChanged, this, &SearchWindow::CheckBidIdWork);
    connect(this->ui->bid_choose_work_button, &QPushButton::clicked, this, &SearchWindow::FindBidWork);
    connect(this->ui->condition_1_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_2_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_3_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_4_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_5_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_6_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->condition_7_check, &QCheckBox::checkStateChanged, this, &SearchWindow::CheckBidConditionsWork);
    connect(this->ui->bid_check_work_button, &QPushButton::clicked, this, &SearchWindow::CheckBidFulfillmentWork);
    connect(this->ui->comment_work_edit, &QTextEdit::textChanged, this->ui->result_work_label, &QLabel::clear);
    connect(this->ui->refusal_work_button, &QPushButton::clicked, this, &SearchWindow::Refusal);
    connect(this->ui->reception_work_button, &QPushButton::clicked, this, &SearchWindow::Reception);

    // Установка связей между сигналами и методами для пагинации заявок
    connect(this->ui->bid_id_filter_edit, &QLineEdit::textChanged, this, &SearchWindow::BidList);
    connect(this->ui->bid_date_filter_edit, &QLineEdit::textChanged, this, &SearchWindow::BidList);
    connect(this->ui->bid_change_filter_edit, &QLineEdit::textChanged, this, &SearchWindow::BidList);
    connect(this->ui->bid_status_filter_box, &QComboBox::currentIndexChanged, this, &SearchWindow::BidList);
    connect(this->ui->bid_left_button, &QPushButton::clicked, this, [this](){ this->bid_page--; BidList(); });
    connect(this->ui->bid_right_button, &QPushButton::clicked, this, [this](){ this->bid_page++; BidList(); });
    connect(this->ui->bid_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &SearchWindow::BidList);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &SearchWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &SearchWindow::FindBidRead);

    // Пагинация формы просмотра заявки
    connect(this->ui->bid_read_left_button, &QPushButton::clicked, this, [this](){ this->bid_read_page--; ChooseBidReadPage(); });
    connect(this->ui->bid_read_right_button, &QPushButton::clicked, this, [this](){ this->bid_read_page++; ChooseBidReadPage(); });

    // Заполнение таблиц
    BidList();

    ChooseBidReadPage();
}

SearchWindow::~SearchWindow()
{
    this->connection.Disconnect();
    delete this->ui;
}

void SearchWindow::CheckBidIdWork()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;

    if (this->bid_number.length() == 14)
    {

        // Устанавливаем соединение с сервером
        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            // Отправляем сообщение
            is_work = connection.Send("C00" + this->bid_status + '\v' + this->bid_number);

            if (is_work)
            {
                // Принимаем сообщение
                result = connection.Receive();

                is_work = result != "\x18";

                if (is_work)
                {
                    this->bid_number = "";
                    this->bid_status = "";
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    ClearBidWorkForm(0x7);
    ActivateBidWorkForm(false, 0x7);

    this->ui->bid_choose_work_label->clear();
}

void SearchWindow::FindBidWork()
{
    // Флаги проверок
    bool is_correct = this->ui->bid_id_work_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send("C01" + this->username + '\v' + this->ui->bid_id_work_edit->text());

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";
                is_find = result != "\x00";
                is_busy = result == "\x1A";
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }
    // Проверка идентификатора заявки
    if (!is_correct)
    {
        this->ui->bid_id_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_work_note_label->setText("* Длина меньше 14 символов");
        this->ui->bid_id_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->bid_id_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_work_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->bid_id_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_work_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска заявки
    if (!is_correct)
    {
        this->ui->bid_choose_work_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_work_label->setText("* Ошибка в идентификаторе заявки");
    }
    else if (!is_work)
    {
        this->ui->bid_choose_work_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->bid_choose_work_label->setStyleSheet("color: #F5F116;");
            this->ui->bid_choose_work_label->setText("* Заявки нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->bid_choose_work_label->setStyleSheet("color: #F5F116;");
                this->ui->bid_choose_work_label->setText("* Заявка занята сотрудником");
            }
            else
            {
                ActivateBidWorkForm(true, 0x1);

                this->ui->bid_choose_work_label->setStyleSheet("color: #00FF00;");
                this->ui->bid_choose_work_label->setText("* Заявка найдена");
            }
        }
    }

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find && !is_busy)
            {
                this->bid_number = this->ui->bid_id_work_edit->text();
                this->bid_status = result;
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
}

void SearchWindow::CheckBidConditionsWork()
{
    ClearBidWorkForm(0x6);
    ActivateBidWorkForm(false, 0x6);

    this->ui->bid_check_work_label->clear();
}

void SearchWindow::CheckBidFulfillmentWork()
{
    // Получение отметок о выполнении требований
    bool is_condition_1 = this->ui->condition_1_check->isChecked();
    bool is_condition_2 = this->ui->condition_2_check->isChecked();
    bool is_condition_3 = this->ui->condition_3_check->isChecked();
    bool is_condition_4 = this->ui->condition_4_check->isChecked();
    bool is_condition_5 = this->ui->condition_5_check->isChecked();
    bool is_condition_6 = this->ui->condition_6_check->isChecked();
    bool is_condition_7 = this->ui->condition_7_check->isChecked();
    bool is_correct = is_condition_1 && is_condition_2 && is_condition_3 && is_condition_4 &&
                      is_condition_5 && is_condition_6 && is_condition_7;

    // Проверка условия 1
    if (!is_condition_1)
    {
        this->ui->condition_1_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_1_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 2
    if (!is_condition_2)
    {
        this->ui->condition_2_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_2_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 3
    if (!is_condition_3)
    {
        this->ui->condition_3_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_3_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 4
    if (!is_condition_4)
    {
        this->ui->condition_4_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_4_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 5
    if (!is_condition_5)
    {
        this->ui->condition_5_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_5_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 6
    if (!is_condition_6)
    {
        this->ui->condition_6_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_6_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка условия 7
    if (!is_condition_7)
    {
        this->ui->condition_7_check->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->condition_7_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверок
    if (!is_correct)
    {
        this->ui->bid_check_work_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_check_work_label->setText("* Требования не выполнены");

        ActivateBidWorkForm(true, 0x2);
        this->ui->refusal_work_button->setEnabled(true);
    }
    else
    {
        this->ui->bid_check_work_label->setStyleSheet("color: #00FF00;");
        this->ui->bid_check_work_label->setText("* Требования выполнены");

        this->ui->reception_work_button->setEnabled(true);
    }
}

void SearchWindow::Refusal()
{
    // Установка разрешённых символов в комментарии
    QString grant_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789"
                            "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    QString comment = this->ui->comment_work_edit->toPlainText();

    // Флаги проверок
    bool is_correct = true;
    bool is_work = true;

    // Результат работы сервера
    QString result;

    // Проверка комментария
    for (int i = 0; i < comment.length(); i++)
    {
        if (!grant_symbols.contains(comment[i]))
        {
            is_correct = false;
            break;
        }
    }

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send("C02" + comment + "\vОтказ\v" + this->bid_number);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";

                if (result == "1")
                {
                    this->bid_number = "";
                    this->bid_status = "";
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    // Установка результата отказа
    if (!is_correct)
    {
        this->ui->result_work_label->setStyleSheet("color: #F5F116;");
        this->ui->result_work_label->setText("* Ошибка в комментарии");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_work)
    {
        this->ui->result_work_label->setStyleSheet("color: #F5F116;");
        this->ui->result_work_label->setText("* Возникли неполадки на стороне сервера");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->bid_id_work_edit->clear();
        this->ui->result_work_label->setStyleSheet("color: #00FF00;");
        this->ui->result_work_label->setText("* Отказ отправлен");
    }

    if (is_correct)
    {
        if (!is_work)
        {
            QMessageBox box;

            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Ошибка");
            box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

            box.exec();
        }
    }
}

void SearchWindow::Reception()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        is_work = connection.Send("C00Направлена на склад\v" + this->bid_number);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result != "\x18";

            if (result == "1")
            {
                this->bid_number = "";
                this->bid_status = "";
            }
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

    // Установка результата отправки на склад
    if (!is_work)
    {
        this->ui->result_work_label->setStyleSheet("color: #F5F116;");
        this->ui->result_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->bid_id_work_edit->clear();
        this->ui->result_work_label->setStyleSheet("color: #00FF00;");
        this->ui->result_work_label->setText("* Заявка отправлена на склад");
    }

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void SearchWindow::ClearBidWorkForm(unsigned short mod)
{
    // Очистка проверок
    if ((mod & 0x1) == 0x1)
    {
        this->ui->condition_1_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_2_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_3_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_4_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_5_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_6_check->setCheckState(Qt::CheckState::Unchecked);
        this->ui->condition_7_check->setCheckState(Qt::CheckState::Unchecked);

        this->ui->condition_1_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_2_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_3_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_4_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_5_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_6_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->condition_7_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");

        this->ui->bid_check_work_label->clear();
    }

    // Очистка комментария
    if ((mod & 0x2) == 0x2)
    {
        this->ui->comment_work_edit->clear();
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Очистка результата
    if ((mod & 0x4) == 0x4)
    {
        this->ui->result_work_label->clear();
    }
}

void SearchWindow::ActivateBidWorkForm(bool flag, unsigned short mod)
{
    if (flag)
    {
        // Активация проверок
        if ((mod & 0x1) == 0x1)
        {
            this->ui->condition_1_check->setEnabled(true);
            this->ui->condition_2_check->setEnabled(true);
            this->ui->condition_3_check->setEnabled(true);
            this->ui->condition_4_check->setEnabled(true);
            this->ui->condition_5_check->setEnabled(true);
            this->ui->condition_6_check->setEnabled(true);
            this->ui->condition_7_check->setEnabled(true);

            this->ui->condition_1_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_2_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_3_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_4_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_5_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_6_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->condition_7_check->setStyleSheet("background-color: #C5CAE9; color: #000000;");

            this->ui->bid_check_work_button->setEnabled(true);
        }

        // Активация комментария
        if ((mod & 0x2) == 0x2)
        {
            this->ui->comment_work_edit->setEnabled(true);
            this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        }

        // Активация кнопок
        if ((mod & 0x4) == 0x4)
        {
            this->ui->refusal_work_button->setEnabled(true);
            this->ui->reception_work_button->setEnabled(true);
        }
    }
    else
    {
        // Блокировка проверок
        if ((mod & 0x1) == 0x1)
        {
            this->ui->condition_1_check->setEnabled(false);
            this->ui->condition_2_check->setEnabled(false);
            this->ui->condition_3_check->setEnabled(false);
            this->ui->condition_4_check->setEnabled(false);
            this->ui->condition_5_check->setEnabled(false);
            this->ui->condition_6_check->setEnabled(false);
            this->ui->condition_7_check->setEnabled(false);

            this->ui->condition_1_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_2_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_3_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_4_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_5_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_6_check->setStyleSheet("background-color: #BBBBBB; color: black;");
            this->ui->condition_7_check->setStyleSheet("background-color: #BBBBBB; color: black;");

            this->ui->bid_check_work_button->setEnabled(false);
        }

        // Блокировка комментария
        if ((mod & 0x2) == 0x2)
        {
            this->ui->comment_work_edit->setEnabled(false);
            this->ui->comment_work_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        }

        // Блокировка кнопок
        if ((mod & 0x4) == 0x4)
        {
            this->ui->refusal_work_button->setEnabled(false);
            this->ui->reception_work_button->setEnabled(false);
        }
    }
}

void SearchWindow::BidList()
{
    if ((this->ui->bid_id_filter_edit->text().length() == 14 || this->ui->bid_id_filter_edit->text() == "") &&
        (this->ui->bid_date_filter_edit->text().length() == 8 || this->ui->bid_date_filter_edit->text() == "") &&
        (this->ui->bid_change_filter_edit->text().length() == 8 || this->ui->bid_change_filter_edit->text() == ""))
    {
        QString message = "C03";

        int section =  this->ui->bid_table->horizontalHeader()->sortIndicatorSection();
        Qt::SortOrder order = this->ui->bid_table->horizontalHeader()->sortIndicatorOrder();

        if (section == 0)
            message += "b.bid_number";
        else if (section == 1)
            message += "b.date_add";
        else if (section == 2)
            message += "b.date_change";
        else if (section == 3)
            message += "b.bid_status";

        if (order == Qt::AscendingOrder)
            message += "\vASC";
        else
            message += "\vDESC";

        message += ('\v' +QString::number(this->bid_page));

        message += ("\v11");

        if (this->ui->bid_id_filter_edit->text().length() == 14)
            message += ('\v' + this->ui->bid_id_filter_edit->text());
        else
            message += '\v';

        if (this->ui->bid_date_filter_edit->text().length() == 8)
        {
            QStringList list = this->ui->bid_date_filter_edit->text().split('.');

            message += ('\v' + QString("20%1-%2-%3").arg(list[2]).arg(list[1]).arg(list[0]));
        }
        else
            message += '\v';

        if (this->ui->bid_change_filter_edit->text().length() == 8)
        {
            QStringList list = this->ui->bid_change_filter_edit->text().split('.');

            message += ('\v' + QString("20%1-%2-%3").arg(list[2]).arg(list[1]).arg(list[0]));
        }
        else
            message += '\v';

        message += ('\v' + this->ui->bid_status_filter_box->currentText());

        bool is_work = true;
        bool is_find = true;
        QString result;


        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();

                is_find = result != "\x00";
                is_work = result != "\x18";

                if (is_work && is_find)
                {
                    QStringList fields = result.split('\v');

                    this->bid_page = fields[fields.length() - 2].toInt();

                    if (this->bid_page == 1)
                        this->ui->bid_left_button->setEnabled(false);
                    else
                        this->ui->bid_left_button->setEnabled(true);

                    if (fields[fields.length() - 1] == "1")
                        this->ui->bid_right_button->setEnabled(true);
                    else
                        this->ui->bid_right_button->setEnabled(false);

                    this->bid_model->removeRows(0, this->bid_model->rowCount());

                    for (int i = 0; i < (fields.length() - 2); i += 4)
                    {
                        this->bid_model->insertRow(this->bid_model->rowCount());

                        this->bid_model->setData(this->bid_model->index(i / 4, 0), fields[i]);
                        this->bid_model->setData(this->bid_model->index(i / 4, 1), QDate::fromString(fields[i + 1], "yyyy-MM-dd").toString("dd.MM.yy"));
                        this->bid_model->setData(this->bid_model->index(i / 4, 2), QDate::fromString(fields[i + 2], "yyyy-MM-dd").toString("dd.MM.yy"));
                        this->bid_model->setData(this->bid_model->index(i / 4, 3), fields[i + 3]);
                    }

                    this->ui->bid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();

            if (!is_work || !is_find)
            {
                this->ui->bid_left_button->setEnabled(false);
                this->ui->bid_right_button->setEnabled(false);

                this->bid_model->removeRows(0, this->bid_model->rowCount());
                this->ui->bid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                this->bid_page = 1;
            }
        }
    }
    else
    {
        this->ui->bid_left_button->setEnabled(false);
        this->ui->bid_right_button->setEnabled(false);

        this->bid_model->removeRows(0, this->bid_model->rowCount());
        this->ui->bid_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->bid_page = 1;
    }
}

void SearchWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void SearchWindow::FindBidRead()
{
    // Флаги проверок
    bool is_correct = this->ui->bid_id_read_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send("C04" + this->ui->bid_id_read_edit->text());

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";
                is_find = result != "\x00";
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }
    // Проверка идентификатора заявки
    if (!is_correct)
    {
        this->ui->bid_id_read_note_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_read_note_label->setText("* Длина меньше 14 символов");
        this->ui->bid_id_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->bid_id_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_read_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->bid_id_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_read_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результатов поиска заявки
    if (!is_correct)
    {
        this->ui->bid_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_read_label->setText("* Ошибка в идентификаторе заявки");
    }
    else if (!is_work)
    {
        this->ui->bid_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_read_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->bid_id_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_read_note_label->setText("* Обязательно для заполнения");

        if (!is_find)
        {
            this->ui->bid_choose_read_label->setStyleSheet("color: #F5F116;");
            this->ui->bid_choose_read_label->setText("* Заявки нет в системе");
        }
        else
        {
            this->ui->bid_choose_read_label->setStyleSheet("color: #00FF00;");
            this->ui->bid_choose_read_label->setText("* Заявка найдена");
        }
    }

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find)
            {
                QStringList list = result.split('\v');

                this->ui->organization_read_edit->setText(list[2]);
                this->ui->INN_read_edit->setText(list[3]);
                this->ui->phone_read_edit->setText(list[4]);
                this->ui->mail_read_edit->setText(list[5]);
                this->ui->cargo_read_edit->setText(list[6]);
                this->ui->TNVED_read_edit->setText(list[7]);
                this->ui->direction_read_edit->setText(list[8]);
                this->ui->length_read_spin->setValue(list[9].toDouble());
                this->ui->width_read_spin->setValue(list[10].toDouble());
                this->ui->height_read_spin->setValue(list[11].toDouble());
                this->ui->weight_read_spin->setValue(list[12].toDouble());
                this->ui->package_read_edit->setText(list[13]);
                this->ui->feature_read_edit->setText(list[14]);
                this->ui->quantity_read_spin->setValue(list[15].toInt());
                this->ui->traffic_in_read_edit->setText(list[16]);
                this->ui->traffic_out_read_edit->setText(list[17]);
                this->ui->date_in_read_date->setDate(QDate::fromString(list[18], "yyyy-MM-dd").addYears(-100));
                this->ui->date_out_read_date->setDate(QDate::fromString(list[19], "yyyy-MM-dd").addYears(-100));
                this->ui->storage_read_edit->setText(list[20]);
                this->ui->term_read_spin->setValue(list[21].toInt());
                this->ui->demand_read_edit->setText(list[22]);
                this->ui->producer_read_edit->setText(list[23]);
                this->ui->sender_read_edit->setText(list[24]);
                this->ui->port_from_read_edit->setText(list[25]);
                this->ui->country_from_read_edit->setText(list[26]);
                this->ui->port_to_read_edit->setText(list[27]);
                this->ui->country_to_read_edit->setText(list[28]);
                this->ui->receiver_read_edit->setText(list[29]);
                this->ui->other_read_edit->setText(list[30]);
                this->ui->comment_read_edit->setText(list[31]);
                this->ui->bid_status_read_edit->setText(list[32]);
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
}

void SearchWindow::ChooseBidReadPage()
{
    this->ui->organization_read_edit->setVisible(false);
    this->ui->INN_read_edit->setVisible(false);
    this->ui->phone_read_edit->setVisible(false);
    this->ui->mail_read_edit->setVisible(false);
    this->ui->cargo_read_edit->setVisible(false);
    this->ui->TNVED_read_edit->setVisible(false);
    this->ui->direction_read_edit->setVisible(false);
    this->ui->length_read_spin->setVisible(false);
    this->ui->width_read_spin->setVisible(false);
    this->ui->height_read_spin->setVisible(false);
    this->ui->weight_read_spin->setVisible(false);
    this->ui->package_read_edit->setVisible(false);
    this->ui->feature_read_edit->setVisible(false);
    this->ui->quantity_read_spin->setVisible(false);
    this->ui->traffic_in_read_edit->setVisible(false);
    this->ui->traffic_out_read_edit->setVisible(false);
    this->ui->date_in_read_date->setVisible(false);
    this->ui->date_out_read_date->setVisible(false);
    this->ui->storage_read_edit->setVisible(false);
    this->ui->term_read_spin->setVisible(false);
    this->ui->demand_read_edit->setVisible(false);
    this->ui->producer_read_edit->setVisible(false);
    this->ui->sender_read_edit->setVisible(false);
    this->ui->port_from_read_edit->setVisible(false);
    this->ui->country_from_read_edit->setVisible(false);
    this->ui->port_to_read_edit->setVisible(false);
    this->ui->country_to_read_edit->setVisible(false);
    this->ui->receiver_read_edit->setVisible(false);
    this->ui->other_read_edit->setVisible(false);
    this->ui->comment_read_edit->setVisible(false);
    this->ui->bid_status_read_edit->setVisible(false);

    this->ui->organization_read_label->setVisible(false);
    this->ui->INN_read_label->setVisible(false);
    this->ui->phone_read_label->setVisible(false);
    this->ui->mail_read_label->setVisible(false);
    this->ui->cargo_read_label->setVisible(false);
    this->ui->TNVED_read_label->setVisible(false);
    this->ui->direction_read_label->setVisible(false);
    this->ui->length_read_label->setVisible(false);
    this->ui->width_read_label->setVisible(false);
    this->ui->height_read_label->setVisible(false);
    this->ui->weight_read_label->setVisible(false);
    this->ui->package_read_label->setVisible(false);
    this->ui->feature_read_label->setVisible(false);
    this->ui->quantity_read_label->setVisible(false);
    this->ui->traffic_in_read_label->setVisible(false);
    this->ui->traffic_out_read_label->setVisible(false);
    this->ui->date_in_read_label->setVisible(false);
    this->ui->date_out_read_label->setVisible(false);
    this->ui->storage_read_label->setVisible(false);
    this->ui->term_read_label->setVisible(false);
    this->ui->demand_read_label->setVisible(false);
    this->ui->producer_read_label->setVisible(false);
    this->ui->sender_read_label->setVisible(false);
    this->ui->port_from_read_label->setVisible(false);
    this->ui->country_from_read_label->setVisible(false);
    this->ui->port_to_read_label->setVisible(false);
    this->ui->country_to_read_label->setVisible(false);
    this->ui->receiver_read_label->setVisible(false);
    this->ui->other_read_label->setVisible(false);
    this->ui->comment_read_label->setVisible(false);
    this->ui->bid_status_read_label->setVisible(false);

    if (this->bid_read_page == 1)
    {
        this->ui->organization_read_edit->setVisible(true);
        this->ui->INN_read_edit->setVisible(true);
        this->ui->phone_read_edit->setVisible(true);
        this->ui->mail_read_edit->setVisible(true);
        this->ui->cargo_read_edit->setVisible(true);
        this->ui->TNVED_read_edit->setVisible(true);

        this->ui->organization_read_label->setVisible(true);
        this->ui->INN_read_label->setVisible(true);
        this->ui->phone_read_label->setVisible(true);
        this->ui->mail_read_label->setVisible(true);
        this->ui->cargo_read_label->setVisible(true);
        this->ui->TNVED_read_label->setVisible(true);
    }
    else if (this->bid_read_page == 2)
    {
        this->ui->direction_read_edit->setVisible(true);
        this->ui->length_read_spin->setVisible(true);
        this->ui->width_read_spin->setVisible(true);
        this->ui->height_read_spin->setVisible(true);
        this->ui->weight_read_spin->setVisible(true);

        this->ui->direction_read_label->setVisible(true);
        this->ui->length_read_label->setVisible(true);
        this->ui->width_read_label->setVisible(true);
        this->ui->height_read_label->setVisible(true);
        this->ui->weight_read_label->setVisible(true);
    }
    else if (this->bid_read_page == 3)
    {
        this->ui->package_read_edit->setVisible(true);
        this->ui->feature_read_edit->setVisible(true);
        this->ui->quantity_read_spin->setVisible(true);
        this->ui->traffic_in_read_edit->setVisible(true);
        this->ui->traffic_out_read_edit->setVisible(true);

        this->ui->package_read_label->setVisible(true);
        this->ui->feature_read_label->setVisible(true);
        this->ui->quantity_read_label->setVisible(true);
        this->ui->traffic_in_read_label->setVisible(true);
        this->ui->traffic_out_read_label->setVisible(true);
    }
    else if (this->bid_read_page == 4)
    {
        this->ui->date_in_read_date->setVisible(true);
        this->ui->date_out_read_date->setVisible(true);
        this->ui->storage_read_edit->setVisible(true);
        this->ui->term_read_spin->setVisible(true);
        this->ui->demand_read_edit->setVisible(true);

        this->ui->date_in_read_label->setVisible(true);
        this->ui->date_out_read_label->setVisible(true);
        this->ui->storage_read_label->setVisible(true);
        this->ui->term_read_label->setVisible(true);
        this->ui->demand_read_label->setVisible(true);
    }
    else if (this->bid_read_page == 5)
    {
        this->ui->producer_read_edit->setVisible(true);
        this->ui->sender_read_edit->setVisible(true);
        this->ui->port_from_read_edit->setVisible(true);
        this->ui->country_from_read_edit->setVisible(true);
        this->ui->port_to_read_edit->setVisible(true);

        this->ui->producer_read_label->setVisible(true);
        this->ui->sender_read_label->setVisible(true);
        this->ui->port_from_read_label->setVisible(true);
        this->ui->country_from_read_label->setVisible(true);
        this->ui->port_to_read_label->setVisible(true);
    }
    else if (this->bid_read_page == 6)
    {
        this->ui->country_to_read_edit->setVisible(true);
        this->ui->receiver_read_edit->setVisible(true);
        this->ui->other_read_edit->setVisible(true);
        this->ui->comment_read_edit->setVisible(true);
        this->ui->bid_status_read_edit->setVisible(true);

        this->ui->country_to_read_label->setVisible(true);
        this->ui->receiver_read_label->setVisible(true);
        this->ui->other_read_label->setVisible(true);
        this->ui->comment_read_label->setVisible(true);
        this->ui->bid_status_read_label->setVisible(true);
    }

    if (this->bid_read_page == 1)
        this->ui->bid_read_left_button->setEnabled(false);
    else
        this->ui->bid_read_left_button->setEnabled(true);

    if (this->bid_read_page == 6)
        this->ui->bid_read_right_button->setEnabled(false);
    else
        this->ui->bid_read_right_button->setEnabled(true);

    this->ui->bid_read_page_label->setText("Страница " + QString::number(this->bid_read_page) + " из 6");

    this->ui->scrollArea_6->widget()->adjustSize();
    this->ui->scrollArea_6->widget()->updateGeometry();
}

void SearchWindow::ClearBidReadForm()
{
    // Возвращение исходного состояния формы
    this->ui->organization_read_edit->clear();
    this->ui->INN_read_edit->clear();
    this->ui->phone_read_edit->clear();
    this->ui->mail_read_edit->clear();
    this->ui->cargo_read_edit->clear();
    this->ui->feature_read_edit->clear();
    this->ui->TNVED_read_edit->clear();
    this->ui->direction_read_edit->clear();
    this->ui->length_read_spin->setValue(0);
    this->ui->width_read_spin->setValue(0);
    this->ui->height_read_spin->setValue(0);
    this->ui->weight_read_spin->setValue(0);
    this->ui->package_read_edit->clear();
    this->ui->quantity_read_spin->setValue(0);
    this->ui->traffic_in_read_edit->clear();
    this->ui->traffic_out_read_edit->clear();
    this->ui->date_in_read_date->setDate(QDate(1900, 1, 1));
    this->ui->date_out_read_date->setDate(QDate(1900, 1, 1));
    this->ui->storage_read_edit->clear();
    this->ui->term_read_spin->setValue(0);
    this->ui->demand_read_edit->clear();
    this->ui->producer_read_edit->clear();
    this->ui->sender_read_edit->clear();
    this->ui->port_from_read_edit->clear();
    this->ui->country_from_read_edit->clear();
    this->ui->port_to_read_edit->clear();
    this->ui->country_to_read_edit->clear();
    this->ui->receiver_read_edit->clear();
    this->ui->other_read_edit->clear();
    this->ui->comment_read_edit->clear();
    this->ui->bid_status_read_edit->clear();

    this->bid_read_page = 1;

    ChooseBidReadPage();
}

void SearchWindow::closeEvent(QCloseEvent *event)
{
    this->ui->bid_id_work_edit->clear();

    QCoreApplication::processEvents();

    event->accept();
}

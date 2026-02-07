#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QRegularExpressionValidator>

SearchWindow::SearchWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::SearchWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

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
    connect(this->ui->comment_work_edit, &QTextEdit::textChanged, this->ui->comment_work_label, &QLabel::clear);
    connect(this->ui->refusal_work_button, &QPushButton::clicked, this, &SearchWindow::Refusal);
    connect(this->ui->reception_work_button, &QPushButton::clicked, this, &SearchWindow::Reception);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &SearchWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &SearchWindow::FindBidRead);
}

SearchWindow::~SearchWindow()
{
    delete this->ui;
}

void SearchWindow::CheckBidIdWork()
{
    // TODO организовать снятие заявки с выбора

    ClearBidWorkForm(0x7);
    ActivateBidWorkForm(false, 0x7);

    this->ui->bid_choose_work_label->clear();
}

void SearchWindow::FindBidWork()
{
    // TODO организовать выбор заявки на сервере

    // Заглушка отправки
    bool is_correct = this->ui->bid_id_work_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

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
    // TODO изменение статуса заявки на отказ на сервере

    // Установка разрешённых символов в комментарии
    QString grant_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789"
                            "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    QString comment = this->ui->comment_work_edit->toPlainText();

    // Заглушка отказа
    bool is_correct = true;
    bool is_work = true;

    // Проверка комментария
    for (int i = 0; i < comment.length(); i++)
    {
        if (!grant_symbols.contains(comment[i]))
        {
            is_correct = false;
            break;
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
}

void SearchWindow::Reception()
{
    // TODO отправка заявки тальману на сервере

    // Заглушка отправки на склад
    bool is_work = true;

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

void SearchWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void SearchWindow::FindBidRead()
{
    // TODO организовать ввод заявки в поля с сервера

    // Заглушка просмотра
    bool is_correct = this->ui->bid_id_read_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;

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
}

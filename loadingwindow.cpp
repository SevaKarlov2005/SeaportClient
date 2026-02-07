#include "loadingwindow.h"
#include "ui_loadingwindow.h"

#include <QRegularExpressionValidator>

LoadingWindow::LoadingWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::LoadingWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

    // Регулярные выражения для валидаторов
    QRegularExpression code_pattern(R"([A-Z]{3})");
    QRegularExpression item_pattern(R"([0-9]{6})");
    QRegularExpression number_pattern(R"([0-9])");
    QRegularExpression bid_id_pattern(R"([0-9]{5}-[0-9]{2}/ОМиДР)");

    // Установка валидаторов для работы с контейнером
    this->ui->code_work_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_work_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_work_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для фильтра контейнеров
    this->ui->code_filter_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_filter_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_filter_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для просмотра контейнера
    this->ui->code_read_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_read_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_read_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидатора для просмотра заявки
    this->ui->bid_id_read_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Блокировка вкладки "Схема погрузки"
    this->ui->stevedore_tab->setTabEnabled(4, false);

    // Установка связей между сигналами и методами для работы с контейнером
    connect(this->ui->code_work_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsWork);
    connect(this->ui->rig_work_box, &QComboBox::currentIndexChanged, this, &LoadingWindow::CheckCaseOptionsWork);
    connect(this->ui->item_work_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsWork);
    connect(this->ui->number_work_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsWork);
    connect(this->ui->case_choose_work_button, &QPushButton::clicked, this, &LoadingWindow::FindCaseWork);
    connect(this->ui->check_true_radio, &QRadioButton::clicked, this, &LoadingWindow::CheckResult);
    connect(this->ui->check_false_radio, &QRadioButton::clicked, this, &LoadingWindow::CheckResult);
    connect(this->ui->reception_work_button, &QPushButton::clicked, this, &LoadingWindow::Reception);

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &LoadingWindow::FindCaseRead);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &LoadingWindow::FindBidRead);
}

LoadingWindow::~LoadingWindow()
{
    delete this->ui;
}

void LoadingWindow::CheckCaseOptionsWork()
{
    // TODO организовать освобождение контейнера на сервере

    ClearCaseWorkForm(0x7);
    ActivateCaseWorkForm(false, 0x7);

    this->ui->case_choose_work_label->clear();
}

void LoadingWindow::FindCaseWork()
{
    // TODO организовать поиск контейнера на сервере и вывод информации в "Схема погрузки"

    // Заглушка поиска
    bool is_code = this->ui->code_work_edit->text().length() == 3;
    bool is_item = this->ui->item_work_edit->text().length() == 6;
    bool is_number = this->ui->number_work_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->code_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_work_note_label->setText("* Длина меньше 3 символов");
        this->ui->code_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->code_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_work_note_label->setText("* Обязательно для заполнения");
        this->ui->code_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->code_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_work_note_label->setText("* Обязательно для заполнения");
        this->ui->code_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (!is_find)
    {
        this->ui->rig_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_work_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_work_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->rig_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_work_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_work_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->item_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_work_note_label->setText("* Длина меньше 6 символов");
        this->ui->item_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->item_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_work_note_label->setText("* Обязательно для заполнения");
        this->ui->item_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->item_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_work_note_label->setText("* Обязательно для заполнения");
        this->ui->item_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number)
    {
        this->ui->number_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_work_note_label->setText("* Длина меньше 1 символа");
        this->ui->number_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->number_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_work_note_label->setText("* Обязательно для заполнения");
        this->ui->number_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->number_work_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_work_note_label->setText("* Обязательно для заполнения");
        this->ui->number_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска контейнера
    if (!is_correct)
    {
        this->ui->case_choose_work_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_work_label->setText("* Ошибка в параметрах контейнера");
    }
    else if (!is_work)
    {
        this->ui->case_choose_work_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->case_choose_work_label->setStyleSheet("color: #F5F116;");
            this->ui->case_choose_work_label->setText("* Контейнера нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->case_choose_work_label->setStyleSheet("color: #F5F116;");
                this->ui->case_choose_work_label->setText("* Контейнер занят сотрудником");
            }
            else
            {
                ActivateCaseWorkForm(true, 0x5);

                this->ui->case_choose_work_label->setStyleSheet("color: #00FF00;");
                this->ui->case_choose_work_label->setText("* Контейнер найден");
            }
        }
    }
}

void LoadingWindow::CheckResult()
{
    if (this->ui->check_true_radio->isChecked())
    {
        ClearCaseWorkForm(0x6);
        ActivateCaseWorkForm(false, 0x2);
        ActivateCaseWorkForm(true, 0x4);
    }
    else
    {
        ClearCaseWorkForm(0x6);
        ActivateCaseWorkForm(true, 0x6);
    }
}

void LoadingWindow::Reception()
{
    // TODO изменение статуса контейнера на сервере

    // Установка разрешённых символов в комментарии
    QString grant_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789"
                            "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    QString comment = this->ui->comment_work_edit->toPlainText();

    // Заглушка
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

    // Установка результата
    if (!is_correct)
    {
        this->ui->reception_work_label->setStyleSheet("color: #F5F116;");
        this->ui->reception_work_label->setText("* Ошибка в комментарии");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_work)
    {
        this->ui->reception_work_label->setStyleSheet("color: #F5F116;");
        this->ui->reception_work_label->setText("* Возникли неполадки на стороне сервера");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->code_work_edit->clear();
        this->ui->rig_work_box->setCurrentIndex(0);
        this->ui->item_work_edit->clear();
        this->ui->number_work_edit->clear();
        this->ui->reception_work_label->setStyleSheet("color: #00FF00;");
        this->ui->reception_work_label->setText("* Результат отправлен");
    }
}

void LoadingWindow::ClearCaseWorkForm(unsigned short mod)
{
    //
    if ((mod & 0x1) == 0x1)
    {
        this->ui->check_false_radio->setChecked(false);
        this->ui->check_true_radio->setChecked(true);

        this->ui->designated_ship_edit->clear();
        this->ui->designated_position_edit->clear();
        this->ui->schema_label->clear();
    }

    //
    if ((mod & 0x2) == 0x2)
    {
        this->ui->comment_work_edit->clear();
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    //
    if ((mod & 0x4) == 0x4)
        this->ui->reception_work_label->clear();
}

void LoadingWindow::ActivateCaseWorkForm(bool flag, unsigned short mod)
{
    //
    if (flag)
    {
        //
        if ((mod & 0x1) == 0x1)
        {
            this->ui->check_true_radio->setEnabled(true);
            this->ui->check_false_radio->setEnabled(true);

            this->ui->stevedore_tab->setTabEnabled(4, true);
        }

        //
        if ((mod & 0x2) == 0x2)
        {
            this->ui->comment_work_edit->setEnabled(true);
            this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        }

        //
        if ((mod & 0x4) == 0x4)
            this->ui->reception_work_button->setEnabled(true);
    }
    else
    {
        //
        if ((mod & 0x1) == 0x1)
        {
            this->ui->check_true_radio->setEnabled(false);
            this->ui->check_false_radio->setEnabled(false);

            this->ui->stevedore_tab->setTabEnabled(4, false);
        }

        //
        if ((mod & 0x2) == 0x2)
        {
            this->ui->comment_work_edit->setEnabled(false);
            this->ui->comment_work_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        }

        //
        if ((mod & 0x4) == 0x4)
            this->ui->reception_work_button->setEnabled(false);
    }
}

void LoadingWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void LoadingWindow::FindCaseRead()
{
    // TODO организовать ввод контейнера в поля с сервера

    // Заглушка просмотра
    bool is_code = this->ui->code_read_edit->text().length() == 3;
    bool is_item = this->ui->item_read_edit->text().length() == 6;
    bool is_number = this->ui->number_read_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->code_read_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_read_note_label->setText("* Длина меньше 3 символов");
        this->ui->code_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->code_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_read_note_label->setText("* Обязательно для заполнения");
        this->ui->code_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->code_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_read_note_label->setText("* Обязательно для заполнения");
        this->ui->code_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (!is_find)
    {
        this->ui->rig_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_read_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_read_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->rig_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_read_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_read_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->item_read_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_read_note_label->setText("* Длина меньше 6 символов");
        this->ui->item_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->item_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_read_note_label->setText("* Обязательно для заполнения");
        this->ui->item_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->item_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_read_note_label->setText("* Обязательно для заполнения");
        this->ui->item_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number)
    {
        this->ui->number_read_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_read_note_label->setText("* Длина меньше 1 символа");
        this->ui->number_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->number_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_read_note_label->setText("* Обязательно для заполнения");
        this->ui->number_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->number_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_read_note_label->setText("* Обязательно для заполнения");
        this->ui->number_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска контейнера
    if (!is_correct)
    {
        this->ui->case_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_read_label->setText("* Ошибка в параметрах контейнера");
    }
    else if (!is_work)
    {
        this->ui->case_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_read_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {

        if (!is_find)
        {
            this->ui->case_choose_read_label->setStyleSheet("color: #F5F116;");
            this->ui->case_choose_read_label->setText("* Контейнера нет в системе");
        }
        else
        {
            this->ui->case_choose_read_label->setStyleSheet("color: #00FF00;");
            this->ui->case_choose_read_label->setText("* Контейнер найден");
        }
    }
}

void LoadingWindow::ClearCaseReadForm()
{
    // Возвращение исходного состояния формы
    this->ui->country_read_edit->clear();
    this->ui->size_read_edit->clear();
    this->ui->case_type_read_edit->clear();
    this->ui->gross_read_spin->setValue(0);
    this->ui->tare_weight_read_spin->setValue(0);
    this->ui->carrying_read_spin->setValue(0);
    this->ui->capacity_read_spin->setValue(0);
    this->ui->IMO_read_edit->clear();
    this->ui->position_read_edit->clear();
    this->ui->claim_read_edit->clear();
    this->ui->case_status_read_edit->clear();
}

void LoadingWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void LoadingWindow::FindBidRead()
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

void LoadingWindow::ClearBidReadForm()
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

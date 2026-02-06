#include "planningwindow.h"
#include "ui_planningwindow.h"

#include <QRegularExpressionValidator>

PlanningWindow::PlanningWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::PlanningWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

    // Регулярные выражения для валидаторов
    QRegularExpression code_pattern(R"([A-Z]{3})");
    QRegularExpression item_pattern(R"([0-9]{6})");
    QRegularExpression number_pattern(R"([0-9])");
    QRegularExpression IMO_pattern(R"([0-9]{7})");
    QRegularExpression position_pattern(R"([A-Z][0-9]{2})");
    QRegularExpression ship_name_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-zА-Яа-я\-]+)");
    QRegularExpression country_pattern(R"([A-Za-zА-Яа-я \-]+)");

    // Установка валидаторов для работы с контейнером
    this->ui->code_work_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_work_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_work_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для назначения морского судна
    this->ui->new_ship_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->new_position_edit->setValidator(new QRegularExpressionValidator(position_pattern));

    // Установка валидаторов для фильтра контейнеров
    this->ui->code_filter_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_filter_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_filter_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для фильтра морских судов
    this->ui->IMO_filter_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->ship_name_filter_edit->setValidator(new QRegularExpressionValidator(ship_name_pattern));

    // Установка валидаторов для просмотра контейнера
    this->ui->code_read_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_read_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_read_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидатора для просмотра морского судна
    this->ui->ship_IMO_read_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));

    // Установка валидаторов для добавления морского судна
    this->ui->ship_IMO_add_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->ship_name_add_edit->setValidator(new QRegularExpressionValidator(ship_name_pattern));
    this->ui->ship_country_add_edit->setValidator(new QRegularExpressionValidator(country_pattern));

    // Установка валидаторов для изменения морского судна
    this->ui->ship_IMO_update_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->new_IMO_update_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->ship_name_update_edit->setValidator(new QRegularExpressionValidator(ship_name_pattern));
    this->ui->ship_country_update_edit->setValidator(new QRegularExpressionValidator(country_pattern));

    // Установка валидатора для удаления морского судна
    this->ui->IMO_delete_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));

    // Блокировка второй вкладки
    this->ui->dispatcher_tab->setTabEnabled(1, false);

    // Установка связей между сигналами и методами для работы с контейнером
    connect(this->ui->code_work_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsWork);
    connect(this->ui->rig_work_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CheckCaseOptionsWork);
    connect(this->ui->item_work_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsWork);
    connect(this->ui->number_work_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsWork);
    connect(this->ui->case_choose_work_button, &QPushButton::clicked, this, &PlanningWindow::FindCaseWork);
    connect(this->ui->plan_suggest_work_button, &QPushButton::clicked, this, &PlanningWindow::SuggestPlan);
    connect(this->ui->plan_check_work_button, &QPushButton::clicked, this, &PlanningWindow::CheckPlan);
    connect(this->ui->reception_work_button, &QPushButton::clicked, this, &PlanningWindow::Reception);
    connect(this->ui->new_ship_choose_button, &QPushButton::clicked, this, &PlanningWindow::AssignShip);
    connect(this->ui->new_position_choose_button, &QPushButton::clicked, this, &PlanningWindow::AssignPosition);

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &PlanningWindow::FindCaseRead);

    // Установка связей между сигналами и методами для просмотра морского судна
    connect(this->ui->ship_IMO_read_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckIMORead);
    connect(this->ui->ship_choose_read_button, &QPushButton::clicked, this, &PlanningWindow::FindShipRead);

    // Установка связей между сигналами и методами для добавления морского судна
    connect(this->ui->ship_IMO_add_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->ship_type_add_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->ship_name_add_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->ship_country_add_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->ship_carrying_add_spin, &QDoubleSpinBox::valueChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->workload_add_spin, &QDoubleSpinBox::valueChanged, this, &PlanningWindow::CheckShipAddForm);
    connect(this->ui->ship_check_add_button, &QPushButton::clicked, this, &PlanningWindow::CheckShipAddContents);
    connect(this->ui->ship_add_button, &QPushButton::clicked, this, &PlanningWindow::AddShip);

    // Установка связей между сигналами и методами для изменения морского судна
    connect(this->ui->ship_IMO_update_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckIMOUpdate);
    connect(this->ui->ship_choose_update_button, &QPushButton::clicked, this, &PlanningWindow::FindShipUpdate);
    connect(this->ui->new_IMO_update_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_type_update_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_name_update_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_country_update_edit, &QLineEdit::textChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_carrying_update_spin, &QDoubleSpinBox::valueChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->workload_update_spin, &QDoubleSpinBox::valueChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_status_update_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CheckShipUpdateForm);
    connect(this->ui->ship_check_update_button, &QPushButton::clicked, this, &PlanningWindow::CheckShipUpdateContents);
    connect(this->ui->ship_update_button, &QPushButton::clicked, this, &PlanningWindow::UpdateShip);

    // Установка связей между сигналами и методами для удаления морского судна
    connect(this->ui->IMO_delete_edit, &QLineEdit::textChanged, this->ui->ship_delete_label, &QLabel::clear);
    connect(this->ui->ship_delete_button, &QPushButton::clicked, this, &PlanningWindow::DeleteShip);
}

PlanningWindow::~PlanningWindow()
{
    delete this->ui;
}

void PlanningWindow::CheckCaseOptionsWork()
{
    // TODO организовать освобождение контейнера на сервере

    ClearCaseWorkForm(0x7);
    ActivateCaseWorkForm(false, 0x7);

    this->ui->case_choose_work_label->clear();
}

void PlanningWindow::FindCaseWork()
{
    // TODO организовать поиск контейнера на сервере

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
                ActivateCaseWorkForm(true, 0x1);

                this->ui->case_choose_work_label->setStyleSheet("color: #00FF00;");
                this->ui->case_choose_work_label->setText("* Контейнер найден");
            }
        }
    }
}

void PlanningWindow::SuggestPlan()
{
    // TODO организовать предложение плана погрузки на сервере и отрисовку изображения

    bool is_work = true;
    bool is_find = true;

    // Установка результата предложения распределения
    if (!is_work)
    {
        this->ui->plan_suggest_work_label->setStyleSheet("color: #F5F116;");
        this->ui->plan_suggest_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->plan_suggest_work_label->setStyleSheet("color: #F5F116;");
            this->ui->plan_suggest_work_label->setText("* Не удалось составить план");
        }
        else
        {
            ActivateCaseWorkForm(true, 0x2);

            this->ui->plan_suggest_work_label->setStyleSheet("color: #00FF00;");
            this->ui->plan_suggest_work_label->setText("* План составлен");
        }
    }
}

void PlanningWindow::CheckPlan()
{
    // TODO организовать проверку плана на сервере

    bool is_work = true;
    bool is_right = true; // Проверка незанятости позиции

    // Проверка позиции
    if (!is_right)
    {
        this->ui->designated_position_note_label->setStyleSheet("color: #F5F116;");
        this->ui->designated_position_note_label->setText("* Место занято");
        this->ui->designated_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }

    // Установка результата проверки распределения
    if (!is_work)
    {
        this->ui->plan_check_work_label->setStyleSheet("color: #F5F116;");
        this->ui->plan_check_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_right)
        {
            this->ui->plan_check_work_label->setStyleSheet("color: #F5F116;");
            this->ui->plan_check_work_label->setText("* В плане обнаружены ошибки");
        }
        else
        {
            this->ui->reception_work_button->setEnabled(true);

            this->ui->plan_check_work_label->setStyleSheet("color: #00FF00;");
            this->ui->plan_check_work_label->setText("* План прошёл проверку");
        }
    }
}

void PlanningWindow::Reception()
{
    // TODO отправка контейнера стивидору на сервере

    // Заглушка отправки на склад
    bool is_work = true;

    // Установка результата отправки на склад
    if (!is_work)
    {
        this->ui->reception_work_label->setStyleSheet("color: #F5F116;");
        this->ui->reception_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->code_work_edit->clear();
        this->ui->rig_work_box->setCurrentIndex(0);
        this->ui->item_work_edit->clear();
        this->ui->number_work_edit->clear();
        this->ui->reception_work_label->setStyleSheet("color: #00FF00;");
        this->ui->reception_work_label->setText("* Контейнер отправлен стивидору");
    }
}

void PlanningWindow::ClearCaseWorkForm(unsigned short mod)
{
    // Очистка предоставления плана
    if ((mod & 0x1) == 0x1)
        this->ui->plan_suggest_work_label->clear();

    // TODO организовать освобождение морского судна на сервере
    // Очистка проверки плана
    if ((mod & 0x2) == 0x2)
    {
        this->ui->plan_check_work_label->clear();

        this->ui->ship_country_edit->clear();
        this->ui->designated_ship_edit->clear();
        this->ui->designated_position_edit->clear();
        this->ui->schema_label->clear();
        this->ui->new_ship_edit->clear();
        this->ui->new_position_edit->clear();

        this->ui->ship_country_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->designated_ship_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->designated_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->schema_label->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_ship_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

        this->ui->ship_country_note_label->clear();
        this->ui->designated_ship_note_label->clear();
        this->ui->designated_position_note_label->clear();
        this->ui->new_ship_note_label->clear();
        this->ui->new_position_note_label->clear();
        this->ui->new_ship_choose_label->clear();
        this->ui->new_position_choose_label->clear();

        this->ui->ship_country_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->designated_ship_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->designated_position_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_ship_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_position_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_ship_choose_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_position_choose_label->setStyleSheet("color: #FFFFFF;");
    }

    // Очистка результата
    if ((mod & 0x4) == 0x4)
        this->ui->reception_work_label->clear();
}

void PlanningWindow::ActivateCaseWorkForm(bool flag, unsigned short mod)
{
    // Активация и блокировка полей
    if (flag)
    {
        // Активация предоставления плана
        if ((mod & 0x1) == 0x1)
            this->ui->plan_suggest_work_button->setEnabled(true);

        // Активация проверки плана
        if ((mod & 0x2) == 0x2)
        {
            this->ui->plan_check_work_button->setEnabled(true);
            this->ui->dispatcher_tab->setTabEnabled(1, true);
        }

        // Активация результата
        if ((mod & 0x4) == 0x4)
            this->ui->reception_work_button->setEnabled(true);
    }
    else
    {
        // Блокировка предоставления плана
        if ((mod & 0x1) == 0x1)
            this->ui->plan_suggest_work_button->setEnabled(false);

        // Блокировка проверки плана
        if ((mod & 0x2) == 0x2)
        {
            this->ui->plan_check_work_button->setEnabled(false);
            this->ui->dispatcher_tab->setTabEnabled(1, false);
        }

        // Блокировка результата
        if ((mod & 0x4) == 0x4)
            this->ui->reception_work_button->setEnabled(false);
    }
}

void PlanningWindow::AssignShip()
{
    // TODO организовать назначение судна на сервере с изменением картинки

    bool is_correct = this->ui->new_ship_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка IMO номера
    if (!is_correct)
    {
        this->ui->new_ship_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_ship_note_label->setText("* Длина меньше 7 символов");
        this->ui->new_ship_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->new_ship_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_ship_note_label->clear();
        this->ui->new_ship_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_ship_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_ship_note_label->clear();
        this->ui->new_ship_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска морского судна
    if (!is_correct)
    {
        this->ui->new_ship_choose_label->setStyleSheet("color: #F5F116;");
        this->ui->new_ship_choose_label->setText("* Ошибка в номере IMO");
    }
    else if (!is_work)
    {
        this->ui->new_ship_choose_label->setStyleSheet("color: #F5F116;");
        this->ui->new_ship_choose_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->new_ship_choose_label->setStyleSheet("color: #F5F116;");
            this->ui->new_ship_choose_label->setText("* Морского судна нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->new_ship_choose_label->setStyleSheet("color: #F5F116;");
                this->ui->new_ship_choose_label->setText("* Морское судно занято сотрудником");
            }
            else
            {
                this->ui->plan_check_work_label->clear();

                ClearCaseWorkForm(0x4);
                ActivateCaseWorkForm(false, 0x4);

                this->ui->new_ship_choose_label->setStyleSheet("color: #00FF00;");
                this->ui->new_ship_choose_label->setText("* Морское судно назначено");
            }
        }
    }
}

void PlanningWindow::AssignPosition()
{
    // TODO организовать назначение позиции на сервере

    bool is_position_full = this->ui->new_position_edit->text().length() == 3;
    bool is_position = is_position_full && this->ui->new_position_edit->text().slice(1, 2).toInt(NULL) >= 0 &&
                       this->ui->new_position_edit->text().slice(1, 2).toInt(NULL) <= 9;
    bool is_correct = is_position;

    // Проверка позиции
    if (!is_position_full)
    {
        this->ui->new_position_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_position_note_label->setText("* Длина меньше 3 символов");
        this->ui->new_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_position)
    {
        this->ui->new_position_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_position_note_label->setText("* Позиция отсутствует");
        this->ui->new_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_position_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_position_note_label->clear();
        this->ui->new_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска позиции
    if (!is_correct)
    {
        this->ui->new_position_choose_label->setStyleSheet("color: #F5F116;");
        this->ui->new_position_choose_label->setText("* Ошибка в номере позиции");
    }
    else
    {
        this->ui->plan_check_work_label->clear();

        ClearCaseWorkForm(0x4);
        ActivateCaseWorkForm(false, 0x4);

        this->ui->new_position_choose_label->setStyleSheet("color: #00FF00;");
        this->ui->new_position_choose_label->setText("* Позиция назначена");
    }
}

void PlanningWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void PlanningWindow::FindCaseRead()
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

void PlanningWindow::ClearCaseReadForm()
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

void PlanningWindow::CheckIMORead()
{
    ClearShipReadForm();

    this->ui->ship_choose_read_label->clear();
}

void PlanningWindow::FindShipRead()
{
    // TODO организовать ввод морского судна в поля с сервера

    // Заглушка просмотра
    bool is_correct = this->ui->ship_IMO_read_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;

    // Проверка IMO номера
    if (!is_correct)
    {
        this->ui->ship_IMO_read_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_IMO_read_note_label->setText("* Длина меньше 7 символов");
        this->ui->ship_IMO_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->ship_IMO_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_IMO_read_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_IMO_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_IMO_read_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_IMO_read_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_IMO_read_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска морского судна
    if (!is_correct)
    {
        this->ui->ship_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_choose_read_label->setText("* Ошибка в номере IMO");
    }
    else if (!is_work)
    {
        this->ui->ship_choose_read_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_choose_read_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->ship_choose_read_label->setStyleSheet("color: #F5F116;");
            this->ui->ship_choose_read_label->setText("* Морского судна нет в системе");
        }
        else
        {
            this->ui->ship_choose_read_label->setStyleSheet("color: #00FF00;");
            this->ui->ship_choose_read_label->setText("* Морское судно найдено");
        }
    }
}

void PlanningWindow::ClearShipReadForm()
{
    // Возвращение исходного состояния формы
    this->ui->ship_type_read_edit->clear();
    this->ui->ship_name_read_edit->clear();
    this->ui->ship_country_read_edit->clear();
    this->ui->ship_carrying_read_spin->setValue(0);
    this->ui->workload_read_spin->setValue(0);
    this->ui->ship_status_read_edit->clear();
}

void PlanningWindow::CheckShipAddForm()
{
    this->ui->space_4_label->clear();
    this->ui->ship_add_button->setEnabled(false);
}

void PlanningWindow::CheckShipAddContents()
{
    // TODO организовать проверку на наличие такого морского судна

    // Проверка полей формы
    bool is_IMO_full = this->ui->ship_IMO_add_edit->text().length() == 7;
    bool is_ship_name = this->ui->ship_name_add_edit->text().length() > 0;
    bool is_country = this->ui->ship_country_add_edit->text().length() > 0;
    bool is_carrying = this->ui->ship_carrying_add_spin->value() > 0;
    bool is_workload = this->ui->workload_add_spin->value() <= this->ui->ship_carrying_add_spin->value();
    bool is_IMO = true;

    // Подготовка к проверке IMO номера
    QString IMO = this->ui->ship_IMO_add_edit->text();
    int result = 0;

    // Проверка IMO номера
    if (is_IMO_full)
    {
        // Вычисление суммы
        for (int i = 0; i < 6; i++)
            result += ((7 - i) * IMO[i].digitValue());

        // Взятие остатка
        result = result % 10;

        // Сравнение с последней цифрой
        is_IMO = QString::number(result) == IMO[6];
    }

    // Ключевые параметры проверок
    bool is_find = false;
    bool is_correct = is_IMO_full && is_IMO && is_ship_name && is_country && is_carrying && is_workload && !is_find;
    bool is_work = true;

    // Проверка IMO номера
    if (!is_IMO_full)
    {
        this->ui->ship_IMO_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_IMO_add_note_label->setText("* Длина меньше 7 символов");
        this->ui->ship_IMO_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_IMO)
    {
        this->ui->ship_IMO_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_IMO_add_note_label->setText("* Неправильный IMO номер");
        this->ui->ship_IMO_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find)
    {
        this->ui->ship_IMO_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_IMO_add_note_label->setText("* IMO номер не уникален");
        this->ui->ship_IMO_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_IMO_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_IMO_add_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_IMO_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка названия судна
    if (!is_ship_name)
    {
        this->ui->ship_name_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_name_add_note_label->setText("* Длина равна нулю");
        this->ui->ship_name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_name_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_name_add_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка страны
    if (!is_country)
    {
        this->ui->ship_country_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_country_add_note_label->setText("* Длина равна нулю");
        this->ui->ship_country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_country_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_country_add_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка грузоподъёмности
    if (!is_carrying)
    {
        this->ui->ship_carrying_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_carrying_add_note_label->setText("* Грузоподъёмность равна нулю");
        this->ui->ship_carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->ship_carrying_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_carrying_add_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка загруженности
    if (!is_workload)
    {
        this->ui->workload_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->workload_add_note_label->setText("* Загруженность больше грузоподъёмности");
        this->ui->workload_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->workload_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->workload_add_note_label->setText("* Обязательно для заполнения");
        this->ui->workload_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверки морского судна
    if (!is_correct)
    {
        this->ui->space_4_label->setStyleSheet("color: #F5F116;");
        this->ui->space_4_label->setText("* В данных морского судна обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->space_4_label->setStyleSheet("color: #F5F116;");
        this->ui->space_4_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->ship_add_button->setEnabled(true);

        this->ui->space_4_label->setStyleSheet("color: #00FF00;");
        this->ui->space_4_label->setText("* Данные морского судна прошли проверку");
    }
}

void PlanningWindow::AddShip()
{
    // TODO организовать отправку морского судна на сервер

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_4_label->setStyleSheet("color: #F5F116;");
        this->ui->space_4_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        ClearShipAddForm();

        this->ui->space_4_label->setStyleSheet("color: #00FF00;");
        this->ui->space_4_label->setText("* Морское судно добавлено");
    }
}

void PlanningWindow::ClearShipAddForm()
{
    // Возвращение начального содержимого полей
    this->ui->ship_IMO_add_edit->clear();
    this->ui->ship_type_add_box->setCurrentIndex(0);
    this->ui->ship_name_add_edit->clear();
    this->ui->ship_country_add_edit->clear();
    this->ui->ship_carrying_add_spin->setValue(0);
    this->ui->workload_add_spin->setValue(0);

    // Возвращение начального внешнего вида полей
    this->ui->ship_IMO_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_type_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->workload_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных комментариев
    this->ui->ship_IMO_add_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_type_add_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_name_add_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_country_add_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_carrying_add_note_label->setText("* Обязательно для заполнения");
    this->ui->workload_add_note_label->setText("* Обязательно для заполнения");

    // Возвращение начального вида комментариев
    this->ui->ship_IMO_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_type_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_name_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_country_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_carrying_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->workload_add_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального состояния кнопок
    this->ui->space_4_label->clear();
    this->ui->ship_check_add_button->setEnabled(true);
    this->ui->ship_add_button->setEnabled(false);
}

void PlanningWindow::CheckIMOUpdate()
{
    // TODO организовать снятие морского судна с занятости

    ClearShipUpdateForm();
    ActivateShipUpdateForm(false);

    this->ui->ship_choose_update_label->clear();
    this->ui->ship_check_update_button->setEnabled(false);
}

void PlanningWindow::FindShipUpdate()
{
    // TODO организовать ввод морского судна в поля с сервера с учётом 'Свободно' и 'Погрузка-Уплыло'

    // Заглушка поиска
    bool is_correct = this->ui->ship_IMO_update_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка IMO номера
    if (!is_correct)
    {
        this->ui->ship_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_IMO_update_note_label->setText("* Длина меньше 7 символов");
        this->ui->ship_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->ship_IMO_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_IMO_update_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_IMO_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_IMO_update_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска морского судна
    if (!is_correct)
    {
        this->ui->ship_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_choose_update_label->setText("* Ошибка в номере IMO");
    }
    else if (!is_work)
    {
        this->ui->ship_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_choose_update_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->ship_choose_update_label->setStyleSheet("color: #F5F116;");
            this->ui->ship_choose_update_label->setText("* Морского судна нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->ship_choose_update_label->setStyleSheet("color: #F5F116;");
                this->ui->ship_choose_update_label->setText("* Морское судно занято сотрудником");
            }
            else
            {
                this->ui->ship_choose_update_label->setStyleSheet("color: #00FF00;");
                this->ui->ship_choose_update_label->setText("* Морское судно найдено");

                ActivateShipUpdateForm(true);
                this->ui->ship_check_update_button->setEnabled(true);
            }
        }
    }
}

void PlanningWindow::CheckShipUpdateForm()
{
    this->ui->space_5_label->clear();
    this->ui->ship_update_button->setEnabled(false);
}

void PlanningWindow::CheckShipUpdateContents()
{
    // TODO организовать проверку на наличие такого морского судна

    // Проверка полей формы
    bool is_IMO_full = this->ui->new_IMO_update_edit->text().length() == 7;
    bool is_ship_name = this->ui->ship_name_update_edit->text().length() > 0;
    bool is_country = this->ui->ship_country_update_edit->text().length() > 0;
    bool is_carrying = this->ui->ship_carrying_update_spin->value() > 0;
    bool is_workload = this->ui->workload_update_spin->value() <= this->ui->ship_carrying_update_spin->value();
    bool is_IMO = true;

    // Подготовка к проверке IMO номера
    QString IMO = this->ui->new_IMO_update_edit->text();
    int result = 0;

    // Проверка IMO номера
    if (is_IMO_full)
    {
        // Вычисление суммы
        for (int i = 0; i < 6; i++)
            result += ((7 - i) * IMO[i].digitValue());

        // Вычисление остатка
        result = result % 10;

        // Сравнение с последней цифрой
        is_IMO = QString::number(result) == IMO[6];
    }

    // Ключевые параметры проверок
    bool is_find = false;
    bool is_correct = is_IMO_full && is_IMO && is_ship_name && is_country && is_carrying && is_workload && !is_find;
    bool is_work = true;

    // Проверка IMO номера
    if (!is_IMO_full)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* Длина меньше 7 символов");
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_IMO)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* Неправильный IMO номер");
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* IMO номер не уникален");
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_IMO_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка названия судна
    if (!is_ship_name)
    {
        this->ui->ship_name_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_name_update_note_label->setText("* Длина равна нулю");
        this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_name_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_name_update_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка страны
    if (!is_country)
    {
        this->ui->ship_country_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_country_update_note_label->setText("* Длина равна нулю");
        this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_country_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_country_update_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка грузоподъёмности
    if (!is_carrying)
    {
        this->ui->ship_carrying_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_carrying_update_note_label->setText("* Грузоподъёмность равна нулю");
        this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->ship_carrying_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_carrying_update_note_label->setText("* Обязательно для заполнения");
        this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка загруженности
    if (!is_workload)
    {
        this->ui->workload_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->workload_update_note_label->setText("* Загруженность больше грузоподъёмности");
        this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->workload_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->workload_update_note_label->setText("* Обязательно для заполнения");
        this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверки морского судна
    if (!is_correct)
    {
        this->ui->space_5_label->setStyleSheet("color: #F5F116;");
        this->ui->space_5_label->setText("* В данных морского судна обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->space_5_label->setStyleSheet("color: #F5F116;");
        this->ui->space_5_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->ship_update_button->setEnabled(true);

        this->ui->space_5_label->setStyleSheet("color: #00FF00;");
        this->ui->space_5_label->setText("* Данные морского судна прошли проверку");
    }
}

void PlanningWindow::UpdateShip()
{
    // TODO организовать изменение морского судна на сервере

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_5_label->setStyleSheet("color: #F5F116;");
        this->ui->space_5_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->ship_IMO_update_edit->clear();
        this->ui->space_5_label->setStyleSheet("color: #00FF00;");
        this->ui->space_5_label->setText("* Морское судно изменено");
    }
}

void PlanningWindow::ClearShipUpdateForm()
{
    // Возвращение начального состояния поля IMO номера
    this->ui->new_IMO_update_edit->clear();

    // Возвращение начального состояния типа судна
    this->ui->ship_type_update_box->clear();
    this->ui->ship_type_update_box->addItem("GP");
    this->ui->ship_type_update_box->addItem("VH");
    this->ui->ship_type_update_box->addItem("RE");
    this->ui->ship_type_update_box->addItem("UT");
    this->ui->ship_type_update_box->addItem("TN");
    this->ui->ship_type_update_box->addItem("HR");
    this->ui->ship_type_update_box->addItem("BU");
    this->ui->ship_type_update_box->addItem("PL");
    this->ui->ship_type_update_box->addItem("SN");
    this->ui->ship_type_update_box->setCurrentText("GP");

    // Возвращение начального состояния оставшихся полей
    this->ui->ship_name_update_edit->clear();
    this->ui->ship_country_update_edit->clear();
    this->ui->ship_carrying_update_spin->setValue(0);
    this->ui->workload_update_spin->setValue(0);

    // Возвращение начального статуса
    this->ui->ship_status_update_box->clear();
    this->ui->ship_status_update_box->addItem("Свободно");
    this->ui->ship_status_update_box->addItem("Погрузка");
    this->ui->ship_status_update_box->addItem("Уплыло");
    this->ui->ship_status_update_box->setCurrentText("Свободно");

    // Возвращение начального вида полей формы
    this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_type_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->ship_status_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных комментариев
    this->ui->new_IMO_update_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_type_update_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_name_update_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_country_update_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_carrying_update_note_label->setText("* Обязательно для заполнения");
    this->ui->workload_update_note_label->setText("* Обязательно для заполнения");
    this->ui->ship_status_update_note_label->clear();

    // Возвращение начального вида комментариев
    this->ui->new_IMO_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_type_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_name_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_country_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_carrying_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->workload_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->ship_status_update_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального состояния кнопок
    this->ui->space_5_label->clear();
    this->ui->ship_check_update_button->setEnabled(true);
    this->ui->ship_update_button->setEnabled(false);
}

void PlanningWindow::ActivateShipUpdateForm(bool flag)
{
    // Активация или блокировка полей формы
    this->ui->new_IMO_update_edit->setEnabled(flag);
    this->ui->ship_type_update_box->setEnabled(flag);
    this->ui->ship_name_update_edit->setEnabled(flag);
    this->ui->ship_country_update_edit->setEnabled(flag);
    this->ui->ship_carrying_update_spin->setEnabled(flag);
    this->ui->workload_update_spin->setEnabled(flag);
    this->ui->ship_status_update_box->setEnabled(flag);

    // Установка стиля полей формы
    if (flag)
    {
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->ship_type_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->ship_status_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->new_IMO_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->ship_type_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->ship_name_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->ship_country_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->workload_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->ship_status_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
    }
}

void PlanningWindow::DeleteShip()
{
    // TODO организовать удаление морского судна на сервере

    // Заглушка отправки
    bool is_correct = this->ui->IMO_delete_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка IMO номера
    if (!is_correct)
    {
        this->ui->IMO_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->IMO_delete_note_label->setText("* Длина меньше 7 символов");
        this->ui->IMO_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->IMO_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->IMO_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->IMO_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->IMO_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->IMO_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->IMO_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата удаления морского судна
    if (!is_correct)
    {
        this->ui->ship_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_delete_label->setText("* Ошибка в номере IMO");
    }
    else if (!is_work)
    {
        this->ui->ship_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_delete_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->ship_delete_label->setStyleSheet("color: #F5F116;");
            this->ui->ship_delete_label->setText("* Морского судна нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->ship_delete_label->setStyleSheet("color: #F5F116;");
                this->ui->ship_delete_label->setText("* Морское судно нельзя удалить");
            }
            else
            {
                this->ui->IMO_delete_edit->clear();
                this->ui->ship_delete_label->setStyleSheet("color: #00FF00;");
                this->ui->ship_delete_label->setText("* Морское судно удалено");
            }
        }
    }
}

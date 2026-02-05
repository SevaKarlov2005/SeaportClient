#include "storagewindow.h"
#include "ui_storagewindow.h"

StorageWindow::StorageWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::StorageWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

    // Регулярные выражения для валидаторов
    QRegularExpression bid_id_pattern(R"([0-9]{5}-[0-9]{2}/ОМиДР)");
    QRegularExpression code_pattern(R"([A-Z]{3})");
    QRegularExpression item_pattern(R"([0-9]{6})");
    QRegularExpression number_pattern(R"([0-9])");
    QRegularExpression date_pattern(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.[0-9]{2})");
    QRegularExpression country_pattern(R"([A-Z]{2})");

    // Установка валидатора для работы с заявкой
    this->ui->bid_id_work_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка валидаторов для назначения контейнеров
    this->ui->code_assigned_filter_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_assigned_filter_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_assigned_filter_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для фильтра заявок
    this->ui->bid_id_filter_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));
    this->ui->bid_date_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));
    this->ui->bid_change_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));

    // Установка валидаторов для фильтра контейнеров
    this->ui->code_filter_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_filter_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_filter_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидатора для просмотра заявки
    this->ui->bid_id_read_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка валидаторов для просмотра контейнера
    this->ui->code_read_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_read_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_read_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для добавления контейнера
    this->ui->code_add_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_add_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_add_edit->setValidator(new QRegularExpressionValidator(number_pattern));
    this->ui->country_add_edit->setValidator(new QRegularExpressionValidator(country_pattern));

    // Установка валидаторов для изменения контейнера
    this->ui->code_update_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_update_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_update_edit->setValidator(new QRegularExpressionValidator(number_pattern));
    this->ui->new_code_update_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->new_item_update_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->new_number_update_edit->setValidator(new QRegularExpressionValidator(number_pattern));
    this->ui->country_update_edit->setValidator(new QRegularExpressionValidator(country_pattern));

    // Установка валидаторов для удаления контейнера
    this->ui->code_delete_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_delete_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_delete_edit->setValidator(new QRegularExpressionValidator(number_pattern));
    this->ui->bid_id_delete_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Блокировка второй и третьей вкладок
    this->ui->tallyman_tab->setTabEnabled(1, false);
    this->ui->tallyman_tab->setTabEnabled(2, false);

    // Настройка таблицы назначенных контейнеров
    this->case_assigned_model = new QStandardItemModel(0, 5);
    this->case_assigned_model->setHeaderData(0, Qt::Horizontal, "Код\nвладельца");
    this->case_assigned_model->setHeaderData(1, Qt::Horizontal, "Идентификатор\nкатегории\nоборудования");
    this->case_assigned_model->setHeaderData(2, Qt::Horizontal, "Серийный\nномер");
    this->case_assigned_model->setHeaderData(3, Qt::Horizontal, "Контрольное\nчисло");
    this->case_assigned_model->setHeaderData(4, Qt::Horizontal, "Статус");
    this->ui->case_assigned_table->setModel(this->case_assigned_model);

    // Установка связей между сигналами и методами для работы с заявкой
    connect(this->ui->bid_id_work_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckBidIdWork);
    connect(this->ui->bid_choose_work_button, &QPushButton::clicked, this, &StorageWindow::FindBidWork);
    connect(this->ui->real_length_weighting_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckWeightingForm);
    connect(this->ui->real_width_weighting_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckWeightingForm);
    connect(this->ui->real_height_weighting_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckWeightingForm);
    connect(this->ui->real_mass_weighting_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckWeightingForm);
    connect(this->ui->real_quantity_weighting_spin, &QSpinBox::valueChanged, this, &StorageWindow::CheckWeightingForm);
    connect(this->ui->weight_check_work_button, &QPushButton::clicked, this, &StorageWindow::CheckWeighting);
    connect(this->ui->propose_distribution_work_button, &QPushButton::clicked, this, &StorageWindow::SuggestDistribution);
    connect(this->ui->check_distribution_work_button, &QPushButton::clicked, this, &StorageWindow::CheckDistribution);
    connect(this->ui->refusal_work_button, &QPushButton::clicked, this, &StorageWindow::Refusal);
    connect(this->ui->reception_work_button, &QPushButton::clicked, this, &StorageWindow::Reception);
    connect(this->ui->appoint_button, &QPushButton::clicked, this, &StorageWindow::AssignCase);
    connect(this->ui->not_appoint_button, &QPushButton::clicked, this, &StorageWindow::ReturnCase);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &StorageWindow::FindBidRead);

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &StorageWindow::FindCaseRead);

    // Установка связей между сигналами и методами для добавления контейнера
    connect(this->ui->code_add_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->rig_add_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->item_add_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->number_add_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->country_add_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->size_add_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->case_type_add_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->gross_add_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->tare_weight_add_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->carrying_add_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->capacity_add_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseAddForm);
    connect(this->ui->case_check_add_button, &QPushButton::clicked, this, &StorageWindow::CheckCaseAddContents);
    connect(this->ui->case_add_button, &QPushButton::clicked, this, &StorageWindow::AddCase);

    // Установка связей между сигналами и методами для изменения контейнера
    connect(this->ui->code_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsUpdate);
    connect(this->ui->rig_update_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseOptionsUpdate);
    connect(this->ui->item_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsUpdate);
    connect(this->ui->number_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsUpdate);
    connect(this->ui->case_choose_update_button, &QPushButton::clicked, this, &StorageWindow::FindCaseUpdate);
    connect(this->ui->new_code_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->new_rig_update_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->new_item_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->new_number_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->country_update_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->size_update_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->case_type_update_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->gross_update_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->tare_weight_update_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->carrying_update_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->capacity_update_spin, &QDoubleSpinBox::valueChanged, this, &StorageWindow::CheckCaseUpdateForm);
    connect(this->ui->case_check_update_button, &QPushButton::clicked, this, &StorageWindow::CheckCaseUpdateContents);
    connect(this->ui->case_update_button, &QPushButton::clicked, this, &StorageWindow::UpdateCase);

    // Установка связей между сигналами и методами для удаления контейнера
    connect(this->ui->code_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->rig_delete_box, &QComboBox::currentIndexChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->item_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->number_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->case_delete_button, &QPushButton::clicked, this, &StorageWindow::DeleteCaseByOptions);
    connect(this->ui->bid_id_delete_edit, &QLineEdit::textChanged, this->ui->bid_id_delete_label_2, &QLabel::clear);
    connect(this->ui->bid_id_delete_button, &QPushButton::clicked, this, &StorageWindow::DeleteCaseByBid);
}

StorageWindow::~StorageWindow()
{
    delete this->ui;
}

void StorageWindow::CheckBidIdWork()
{
    // TODO организовать снятие заявки с выбора

    ClearBidWorkForm(0x1F);
    ActivateBidWorkForm(false, 0x1F);

    this->ui->bid_choose_work_label->clear();
}

void StorageWindow::FindBidWork()
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

void StorageWindow::CheckWeightingForm()
{
    ClearBidWorkForm(0x1E);
    ActivateBidWorkForm(false, 0x1E);

    this->ui->weight_check_work_label->clear();
}

void StorageWindow::CheckWeighting()
{
    //
    bool is_length = this->ui->real_length_weighting_spin->value() == this->ui->bid_length_weighting_spin->value();
    bool is_width = this->ui->real_width_weighting_spin->value() == this->ui->bid_width_weighting_spin->value();
    bool is_height = this->ui->real_height_weighting_spin->value() == this->ui->bid_height_weighting_spin->value();
    bool is_mass = this->ui->real_mass_weighting_spin->value() == this->ui->bid_mass_weighting_spin->value();
    bool is_quantity = this->ui->real_quantity_weighting_spin->value() == this->ui->bid_quantity_weighting_spin->value();
    bool is_correct = is_length && is_width && is_height && is_mass && is_quantity;

    // Проверка длины
    if (!is_length)
    {
        this->ui->real_length_weighting_note_label->setStyleSheet("color: #F5F116;");
        this->ui->real_length_weighting_note_label->setText("* Несоответствие длины");
        this->ui->real_length_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->real_length_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_length_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_length_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка ширины
    if (!is_width)
    {
        this->ui->real_width_weighting_note_label->setStyleSheet("color: #F5F116;");
        this->ui->real_width_weighting_note_label->setText("* Несоответствие ширины");
        this->ui->real_width_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->real_width_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_width_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_width_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка высоты
    if (!is_height)
    {
        this->ui->real_height_weighting_note_label->setStyleSheet("color: #F5F116;");
        this->ui->real_height_weighting_note_label->setText("* Несоответствие высоты");
        this->ui->real_height_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->real_height_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_height_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_height_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка массы
    if (!is_mass)
    {
        this->ui->real_mass_weighting_note_label->setStyleSheet("color: #F5F116;");
        this->ui->real_mass_weighting_note_label->setText("* Несоответствие массы");
        this->ui->real_mass_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->real_mass_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_mass_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_mass_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка количества
    if (!is_quantity)
    {
        this->ui->real_quantity_weighting_note_label->setStyleSheet("color: #F5F116;");
        this->ui->real_quantity_weighting_note_label->setText("* Несоответствие количества");
        this->ui->real_quantity_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->real_quantity_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_quantity_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_quantity_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверки взвешивания
    if (!is_correct)
    {
        ActivateBidWorkForm(true, 0x8);
        this->ui->refusal_work_button->setEnabled(true);

        this->ui->weight_check_work_label->setStyleSheet("color: #F5F116;");
        this->ui->weight_check_work_label->setText("* Несоответствие данных о грузе");
    }
    else
    {
        ActivateBidWorkForm(true, 0x2);

        this->ui->weight_check_work_label->setStyleSheet("color: #00FF00;");
        this->ui->weight_check_work_label->setText("* Данные соответствуют");
    }
}

void StorageWindow::SuggestDistribution()
{
    // TODO организовать составление распределения на сервере

    bool is_work = true;
    bool is_find = true;

    // Установка результата предложения распределения
    if (!is_work)
    {
        this->ui->propose_distribution_work_label->setStyleSheet("color: #F5F116;");
        this->ui->propose_distribution_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->propose_distribution_work_label->setStyleSheet("color: #F5F116;");
            this->ui->propose_distribution_work_label->setText("* Не удалось составить распределение");
        }
        else
        {
            ActivateBidWorkForm(true, 0x4);

            this->ui->propose_distribution_work_label->setStyleSheet("color: #00FF00;");
            this->ui->propose_distribution_work_label->setText("* Распределение составлено");
        }
    }
}

void StorageWindow::CheckDistribution()
{
    // TODO организовать проверку распределения на сервере

    bool is_work = true;
    bool is_right = true;

    // Установка результата проверки распределения
    if (!is_work)
    {
        this->ui->check_distribution_work_label->setStyleSheet("color: #F5F116;");
        this->ui->check_distribution_work_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_right)
        {
            this->ui->check_distribution_work_label->setStyleSheet("color: #F5F116;");
            this->ui->check_distribution_work_label->setText("* Распределение не оптимально или недостаточно");
        }
        else
        {
            this->ui->reception_work_button->setEnabled(true);

            this->ui->check_distribution_work_label->setStyleSheet("color: #00FF00;");
            this->ui->check_distribution_work_label->setText("* Распределение оптимально");
        }
    }
}

void StorageWindow::Refusal()
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
        this->ui->comment_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->comment_work_note_label->setText("* Ошибка в комментарии");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_work)
    {
        this->ui->comment_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->comment_work_note_label->setText("* Возникли неполадки на стороне сервера");
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->bid_id_work_edit->clear();
        this->ui->comment_work_note_label->setStyleSheet("color: #00FF00;");
        this->ui->comment_work_note_label->setText("* Отказ отправлен");
    }
}

void StorageWindow::Reception()
{
    // TODO отправка заявки тальману на сервере

    // Заглушка отправки на склад
    bool is_work = true;

    // Установка результата отправки на склад
    if (!is_work)
    {
        this->ui->comment_work_note_label->setStyleSheet("color: #F5F116;");
        this->ui->comment_work_note_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->bid_id_work_edit->clear();
        this->ui->comment_work_note_label->setStyleSheet("color: #00FF00;");
        this->ui->comment_work_note_label->setText("* Заявка отправлена диспетчеру");
    }
}

void StorageWindow::ClearBidWorkForm(unsigned short mod)
{
    // Очистка взвешивания
    if ((mod & 0x1) == 0x1)
    {
        this->ui->weight_check_work_label->clear();

        this->ui->real_length_weighting_spin->setValue(0);
        this->ui->bid_length_weighting_spin->setValue(0);
        this->ui->real_width_weighting_spin->setValue(0);
        this->ui->bid_width_weighting_spin->setValue(0);
        this->ui->real_height_weighting_spin->setValue(0);
        this->ui->bid_height_weighting_spin->setValue(0);
        this->ui->real_mass_weighting_spin->setValue(0);
        this->ui->bid_mass_weighting_spin->setValue(0);
        this->ui->real_quantity_weighting_spin->setValue(0);
        this->ui->bid_quantity_weighting_spin->setValue(0);

        this->ui->real_length_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->real_width_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->real_height_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->real_mass_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->real_quantity_weighting_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");

        this->ui->real_length_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_width_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_height_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_mass_weighting_note_label->setText("* Обязательно для заполнения");
        this->ui->real_quantity_weighting_note_label->setText("* Обязательно для заполнения");

        this->ui->real_length_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_width_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_height_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_mass_weighting_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->real_quantity_weighting_note_label->setStyleSheet("color: #FFFFFF;");
    }

    // Очистка предложения распределения
    if ((mod & 0x2) == 0x2)
        this->ui->propose_distribution_work_label->clear();

    // TODO освободить назначенные контейнеры на сервере
    // Очистка распределения
    if ((mod & 0x4) == 0x4)
    {
        this->ui->check_distribution_work_label->clear();

        this->case_assigned_model->removeRows(0, this->case_assigned_model->rowCount());

        this->ui->space_2_label->clear();

        this->ui->code_assigned_filter_edit->clear();
        this->ui->rig_assigned_filter_box->setCurrentIndex(0);
        this->ui->item_assigned_filter_edit->clear();
        this->ui->number_assigned_filter_edit->clear();
        this->ui->status_assigned_filter_box->setCurrentIndex(0);

        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Очистка комментария
    if ((mod & 0x8) == 0x8)
    {
        this->ui->comment_work_edit->clear();
        this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Очистка результата
    if ((mod & 0x10) == 0x10)
        this->ui->comment_work_note_label->clear();
}

void StorageWindow::ActivateBidWorkForm(bool flag, unsigned short mod)
{
    // Активация или блокировка формы
    if (flag)
    {
        // Активация взвешивания
        if ((mod & 0x1) == 0x1)
        {
            this->ui->weight_check_work_button->setEnabled(true);
            this->ui->tallyman_tab->setTabEnabled(1, true);
        }

        // Активация предложения распределения
        if ((mod & 0x2) == 0x2)
            this->ui->propose_distribution_work_button->setEnabled(true);

        // Активация проверки распределения
        if ((mod & 0x4) == 0x4)
        {
            this->ui->check_distribution_work_button->setEnabled(true);
            this->ui->tallyman_tab->setTabEnabled(2, true);
        }

        // Активация комментария
        if ((mod & 0x8) == 0x8)
        {
            this->ui->comment_work_edit->setEnabled(true);
            this->ui->comment_work_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        }

        // Активация кнопок
        if ((mod & 0x10) == 0x10)
        {
            this->ui->refusal_work_button->setEnabled(true);
            this->ui->reception_work_button->setEnabled(true);
        }
    }
    else
    {
        // Блокировка взвешивания
        if ((mod & 0x1) == 0x1)
        {
            this->ui->weight_check_work_button->setEnabled(false);
            this->ui->tallyman_tab->setTabEnabled(1, false);
        }

        // Блокировка предложения распределения
        if ((mod & 0x2) == 0x2)
            this->ui->propose_distribution_work_button->setEnabled(false);

        // Блокировка проверки распределения
        if ((mod & 0x4) == 0x4)
        {
            this->ui->check_distribution_work_button->setEnabled(false);
            this->ui->tallyman_tab->setTabEnabled(2, false);
        }

        // Блокировка комментария
        if ((mod & 0x8) == 0x8)
        {
            this->ui->comment_work_edit->setEnabled(false);
            this->ui->comment_work_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        }

        // Блокировка кнопок
        if ((mod & 0x10) == 0x10)
        {
            this->ui->refusal_work_button->setEnabled(false);
            this->ui->reception_work_button->setEnabled(false);
        }
    }
}

void StorageWindow::AssignCase()
{
    // TODO назначить контейнер на сервере

    bool is_code = this->ui->code_assigned_filter_edit->text().length() == 3;
    bool is_item = this->ui->item_assigned_filter_edit->text().length() == 6;
    bool is_number = this->ui->number_assigned_filter_edit->text().length() == 1;
    bool is_status = this->ui->status_assigned_filter_box->currentIndex() == 0;
    bool is_correct = is_code && is_item && is_number && is_status;
    bool is_work = true;
    bool is_find = true;

    // Проверка кода владельца
    if (!is_code || !is_find)
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка идентификатора оборудования
    if (!is_find)
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка серийного номера
    if (!is_item || !is_find)
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка контрольного числа
    if (!is_number || !is_find)
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка статуса
    if (!is_status || !is_find)
        this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Установка результата назначения контейнера
    if (!is_correct)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Ошибка в параметрах контейнера");
    }
    else if (!is_work)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->space_2_label->setStyleSheet("color: #F5F116;");
            this->ui->space_2_label->setText("* Контейнера нет в системе");
        }
        else
        {
            this->ui->check_distribution_work_label->clear();

            ClearBidWorkForm(0x18);
            ActivateBidWorkForm(false, 0x18);

            this->ui->code_assigned_filter_edit->clear();
            this->ui->rig_assigned_filter_box->setCurrentIndex(0);
            this->ui->item_assigned_filter_edit->clear();
            this->ui->number_assigned_filter_edit->clear();
            this->ui->status_assigned_filter_box->setCurrentIndex(0);

            this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

            this->ui->space_2_label->setStyleSheet("color: #00FF00;");
            this->ui->space_2_label->setText("* Контейнер добавлен в назначение");
        }
    }
}

void StorageWindow::ReturnCase()
{
    // TODO снять контейнер с назначения на сервере

    bool is_code = this->ui->code_assigned_filter_edit->text().length() == 3;
    bool is_item = this->ui->item_assigned_filter_edit->text().length() == 6;
    bool is_number = this->ui->number_assigned_filter_edit->text().length() == 1;
    bool is_status = this->ui->status_assigned_filter_box->currentIndex() == 1;
    bool is_correct = is_code && is_item && is_number && is_status;
    bool is_work = true;
    bool is_find = true;

    // Проверка кода владельца
    if (!is_code || !is_find)
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка идентификатора оборудования
    if (!is_find)
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка серийного номера
    if (!is_item || !is_find)
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка контрольного числа
    if (!is_number || !is_find)
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка статуса
    if (!is_status || !is_find)
        this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Установка результата снятия контейнера с назначения
    if (!is_correct)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Ошибка в параметрах контейнера");
    }
    else if (!is_work)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->space_2_label->setStyleSheet("color: #F5F116;");
            this->ui->space_2_label->setText("* Контейнера нет среди выбранных");
        }
        else
        {
            this->ui->check_distribution_work_label->clear();

            ClearBidWorkForm(0x18);
            ActivateBidWorkForm(false, 0x18);

            this->ui->code_assigned_filter_edit->clear();
            this->ui->rig_assigned_filter_box->setCurrentIndex(0);
            this->ui->item_assigned_filter_edit->clear();
            this->ui->number_assigned_filter_edit->clear();
            this->ui->status_assigned_filter_box->setCurrentIndex(0);

            this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
            this->ui->status_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

            this->ui->space_2_label->setStyleSheet("color: #00FF00;");
            this->ui->space_2_label->setText("* Контейнер снят с назначения");
        }
    }
}

void StorageWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void StorageWindow::FindBidRead()
{
    // TODO организовать ввод заявки в поля с сервера

    // Заглушка просмотра
    bool is_correct = this->ui->bid_id_read_edit->text().length() >= 12 && this->ui->bid_id_read_edit->text().length() <= 16;
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

void StorageWindow::ClearBidReadForm()
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

void StorageWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void StorageWindow::FindCaseRead()
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

void StorageWindow::ClearCaseReadForm()
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

void StorageWindow::CheckCaseAddForm()
{
    this->ui->space_1_label->clear();
    this->ui->case_add_button->setEnabled(false);
}

void StorageWindow::CheckCaseAddContents()
{
    // TODO организовать проверку на наличие такого контейнера

    // Получение значений для проверки контрольного числа и серийного номера
    int table[26] = {10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 35, 36, 37, 38};
    QString code = this->ui->code_add_edit->text();
    QString rig = this->ui->rig_add_box->currentText();
    QString item = this->ui->item_add_edit->text();
    QString number = this->ui->number_add_edit->text();
    int result = 0;

    // Получение габаритов контейнера
    QString size = this->ui->size_add_box->currentText();

    // Получение числовых значений полей
    double gross = this->ui->gross_add_spin->value();
    double tare_weight = this->ui->tare_weight_add_spin->value();
    double carrying = this->ui->carrying_add_spin->value();
    double capacity = this->ui->capacity_add_spin->value();

    // Проверки на заполненность
    bool is_code = code.length() == 3;
    bool is_item = item.length() == 6;
    bool is_number_full = number.length() == 1;
    bool is_number = true;
    bool is_country = this->ui->country_add_edit->text().length() == 2;
    bool is_gross_null = gross == 0;
    bool is_tare_weight_null = tare_weight == 0;
    bool is_carrying_null = carrying == 0;
    bool is_capacity_null = capacity == 0;

    // Проверка соответствия брутто и габаритов
    bool is_gross = (size[0] == '1' && gross <= 29200) || (size[0] == '2' && gross <= 30480) || (size[0] == '3' && gross <= 30900) ||
                    (size[0] == '4' && gross <= 34300) || (size[0] == 'L' && gross <= 34850);

    // Проверка соответствия массы тары и габаритов
    bool is_tare_weight = (size[0] == '1' && (size[1] == '8' || size[1] == '9') && tare_weight == 1200) ||
                          (size[0] == '1' && size[1] == '0' && tare_weight == 1300) ||
                          (size[0] == '2' && (size[1] == '8' || size[1] == '9') && tare_weight == 2270) ||
                          (size[0] == '2' && size[1] == '0' && tare_weight == 2340) ||
                          (size[0] == '2' && size[1] == '2' && tare_weight == 2350) ||
                          (size[0] == '3' && (size[1] == '8' || size[1] == '9') && tare_weight == 2640) ||
                          (size[0] == '3' && size[1] == '0' && tare_weight == 2740) ||
                          (size[0] == '3' && size[1] == '2' && tare_weight == 2840) ||
                          (size[0] == '3' && size[1] == '5' && tare_weight == 2900) ||
                          (size[0] == '4' && (size[1] == '8' || size[1] == '9') && tare_weight == 4100) ||
                          (size[0] == '4' && size[1] == '0' && tare_weight == 4150) ||
                          (size[0] == '4' && size[1] == '2' && tare_weight == 4200) ||
                          (size[0] == '4' && size[1] == '5' && tare_weight == 4300) ||
                          (size[0] == 'L' && size[1] == '2' && tare_weight == 4700) ||
                          (size[0] == 'L' && size[1] == '5' && tare_weight == 4850);

    // Проверка грузоподъёмности
    bool is_carrying = (tare_weight + carrying) == gross;

    // Проверка соответствия вместимости и габаритов
    bool is_capacity = (size[0] == '1' && (size[1] == '8' || size[1] == '9') && capacity == 16.5) ||
                       (size[0] == '1' && size[1] == '0' && capacity == 18.7) ||
                       (size[0] == '2' && (size[1] == '8' || size[1] == '9') && capacity == 33.2) ||
                       (size[0] == '2' && size[1] == '0' && capacity == 35.3) ||
                       (size[0] == '2' && size[1] == '2' && capacity == 37.4) ||
                       (size[0] == '3' && (size[1] == '8' || size[1] == '9') && capacity == 47.0) ||
                       (size[0] == '3' && size[1] == '0' && capacity == 50.1) ||
                       (size[0] == '3' && size[1] == '2' && capacity == 52.3) ||
                       (size[0] == '3' && size[1] == '5' && capacity == 55.2) ||
                       (size[0] == '4' && (size[1] == '8' || size[1] == '9') && capacity == 66.0) ||
                       (size[0] == '4' && size[1] == '0' && capacity == 67.1) ||
                       (size[0] == '4' && size[1] == '2' && capacity == 75.5) ||
                       (size[0] == '4' && size[1] == '5' && capacity == 84.2) ||
                       (size[0] == 'L' && size[1] == '2' && capacity == 85.3) ||
                       (size[0] == 'L' && size[1] == '5' && capacity == 94.9);

    // Проверка контрольного числа
    if ((code + rig + item).length() == 10)
    {
        // Суммирование символов с весами
        for (int i = 0; i < 10; i++)
        {
            if (i < 3)
                result += ((1 << i) * table[(int)code[i].toLatin1() - 65]);
            else if (i == 3)
                result += ((1 << i) * table[(int)rig[0].toLatin1() - 65]);
            else
                result += ((1 << i) * item[i - 4].digitValue());
        }

        // Остаток от деления на 11
        result = result % 11;

        // Если остаток 10, записываем 0
        if (result == 10)
            result = 0;

        // Сравниваем с записанным контрольным числом
        if (QString::number(result) != number)
            is_number = false;
    }

    // Ключевые параметры проверок
    bool is_find = false;
    bool is_correct = is_code && is_item && is_number_full && is_number && is_country && !is_gross_null && is_gross &&
        !is_tare_weight_null && is_tare_weight && !is_carrying_null && is_carrying && !is_capacity_null && is_capacity && !is_find;
    bool is_work = true;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->code_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_add_note_label->setText("* Длина меньше 3 символов");
        this->ui->code_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find && is_item && is_number_full && is_number)
    {
        this->ui->code_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_add_note_label->setText("* Маркировка не уникальна");
        this->ui->code_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->code_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_add_note_label->setText("* Обязательно для заполнения");
        this->ui->code_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (is_find && is_code && is_item && is_number_full && is_number)
    {
        this->ui->rig_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->rig_add_note_label->setText("* Маркировка не уникальна");
        this->ui->rig_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->item_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_add_note_label->setText("* Длина меньше 6 символов");
        this->ui->item_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find && is_code && is_number_full && is_number)
    {
        this->ui->item_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_add_note_label->setText("* Маркировка не уникальна");
        this->ui->item_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->item_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_add_note_label->setText("* Обязательно для заполнения");
        this->ui->item_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number_full)
    {
        this->ui->number_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_add_note_label->setText("* Длина меньше 1 символа");
        this->ui->number_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_number)
    {
        this->ui->number_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_add_note_label->setText("* Неправильное контрольное число");
        this->ui->number_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find  && is_code && is_item)
    {
        this->ui->number_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_add_note_label->setText("* Маркировка не уникальна");
        this->ui->number_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->number_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_add_note_label->setText("* Обязательно для заполнения");
        this->ui->number_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка кода страны
    if (!is_country)
    {
        this->ui->country_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_add_note_label->setText("* Длина меньше 2 символов");
        this->ui->country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->country_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_add_note_label->setText("* Обязательно для заполнения");
        this->ui->country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка массы брутто
    if (is_gross_null)
    {
        this->ui->gross_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->gross_add_note_label->setText("* Масса равна нулю");
        this->ui->gross_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_gross)
    {
        this->ui->gross_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->gross_add_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->gross_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->gross_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->gross_add_note_label->setText("* Обязательно для заполнения");
        this->ui->gross_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка массы тары
    if (is_tare_weight_null)
    {
        this->ui->tare_weight_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->tare_weight_add_note_label->setText("* Масса равна нулю");
        this->ui->tare_weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_tare_weight)
    {
        this->ui->tare_weight_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->tare_weight_add_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->tare_weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->tare_weight_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->tare_weight_add_note_label->setText("* Обязательно для заполнения");
        this->ui->tare_weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка грузоподъёмности
    if (is_carrying_null)
    {
        this->ui->carrying_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->carrying_add_note_label->setText("* Грузоподъёмность равна нулю");
        this->ui->carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_carrying)
    {
        this->ui->carrying_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->carrying_add_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->carrying_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->carrying_add_note_label->setText("* Обязательно для заполнения");
        this->ui->carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка вместимости
    if (is_capacity_null)
    {
        this->ui->capacity_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->capacity_add_note_label->setText("* Вместимость равна нулю");
        this->ui->capacity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_capacity)
    {
        this->ui->capacity_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->capacity_add_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->capacity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->capacity_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->capacity_add_note_label->setText("* Обязательно для заполнения");
        this->ui->capacity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверки контейнера
    if (!is_correct)
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* В данных контейнера обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->case_add_button->setEnabled(true);

        this->ui->space_1_label->setStyleSheet("color: #00FF00;");
        this->ui->space_1_label->setText("* Данные контейнера прошли проверку");
    }
}

void StorageWindow::AddCase()
{
    // TODO организовать отправку контейнера на сервер

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        ClearCaseAddForm();

        this->ui->space_1_label->setStyleSheet("color: #00FF00;");
        this->ui->space_1_label->setText("* Контейнер добавлен");
    }
}

void StorageWindow::ClearCaseAddForm()
{
    // Возвращение содержимого полей к начальному состоянию
    this->ui->code_add_edit->clear();
    this->ui->rig_add_box->setCurrentIndex(0);
    this->ui->item_add_edit->clear();
    this->ui->number_add_edit->clear();
    this->ui->country_add_edit->clear();
    this->ui->size_add_box->setCurrentIndex(0);
    this->ui->case_type_add_box->setCurrentIndex(0);
    this->ui->gross_add_spin->setValue(0);
    this->ui->tare_weight_add_spin->setValue(0);
    this->ui->carrying_add_spin->setValue(0);
    this->ui->capacity_add_spin->setValue(0);

    // Возвращение начального вида полей
    this->ui->code_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->rig_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->item_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->number_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->size_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->case_type_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->gross_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->tare_weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->carrying_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->capacity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение комментариев к начальному состоянию
    this->ui->code_add_note_label->setText("* Обязательно для заполнения");
    this->ui->rig_add_note_label->setText("* Обязательно для заполнения");
    this->ui->item_add_note_label->setText("* Обязательно для заполнения");
    this->ui->number_add_note_label->setText("* Обязательно для заполнения");
    this->ui->country_add_note_label->setText("* Обязательно для заполнения");
    this->ui->size_add_note_label->setText("* Обязательно для заполнения");
    this->ui->case_type_add_note_label->setText("* Обязательно для заполнения");
    this->ui->gross_add_note_label->setText("* Обязательно для заполнения");
    this->ui->tare_weight_add_note_label->setText("* Обязательно для заполнения");
    this->ui->carrying_add_note_label->setText("* Обязательно для заполнения");
    this->ui->capacity_add_note_label->setText("* Обязательно для заполнения");

    // Возвращение начального вида комментариев
    this->ui->code_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->rig_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->item_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->number_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->size_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->case_type_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->gross_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->tare_weight_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->carrying_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->capacity_add_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение кнопок к начальному состоянию
    this->ui->space_1_label->clear();
    this->ui->case_check_add_button->setEnabled(true);
    this->ui->case_add_button->setEnabled(false);
}

void StorageWindow::CheckCaseOptionsUpdate()
{
    // TODO снятие контейнера с занятости

    ClearCaseUpdateForm();
    ActivateCaseUpdateForm(false);

    this->ui->case_choose_update_label->clear();
    this->ui->case_check_update_button->setEnabled(false);
}

void StorageWindow::FindCaseUpdate()
{
    // TODO организовать ввод контейнера в поля с сервера

    // Заглушка просмотра
    bool is_code = this->ui->code_update_edit->text().length() == 3;
    bool is_item = this->ui->item_update_edit->text().length() == 6;
    bool is_number = this->ui->number_update_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->code_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_update_note_label->setText("* Длина меньше 3 символов");
        this->ui->code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->code_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_update_note_label->setText("* Обязательно для заполнения");
        this->ui->code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->code_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_update_note_label->setText("* Обязательно для заполнения");
        this->ui->code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (!is_find)
    {
        this->ui->rig_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_update_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->rig_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_update_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->item_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_update_note_label->setText("* Длина меньше 6 символов");
        this->ui->item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->item_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_update_note_label->setText("* Обязательно для заполнения");
        this->ui->item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->item_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_update_note_label->setText("* Обязательно для заполнения");
        this->ui->item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number)
    {
        this->ui->number_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_update_note_label->setText("* Длина меньше 1 символа");
        this->ui->number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->number_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_update_note_label->setText("* Обязательно для заполнения");
        this->ui->number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->number_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_update_note_label->setText("* Обязательно для заполнения");
        this->ui->number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска контейнера
    if (!is_correct)
    {
        this->ui->case_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_update_label->setText("* Ошибка в параметрах контейнера");
    }
    else if (!is_work)
    {
        this->ui->case_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->case_choose_update_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->case_choose_update_label->setStyleSheet("color: #F5F116;");
            this->ui->case_choose_update_label->setText("* Контейнера нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->case_choose_update_label->setStyleSheet("color: #F5F116;");
                this->ui->case_choose_update_label->setText("* Контейнер занят сотрудником");
            }
            else
            {
                this->ui->case_choose_update_label->setStyleSheet("color: #00FF00;");
                this->ui->case_choose_update_label->setText("* Контейнер найден");

                ActivateCaseUpdateForm(true);
                this->ui->case_check_update_button->setEnabled(true);
            }
        }
    }
}

void StorageWindow::CheckCaseUpdateForm()
{
    this->ui->space_3_label->clear();
    this->ui->case_update_button->setEnabled(false);
}

void StorageWindow::CheckCaseUpdateContents()
{
    // TODO организовать проверку на наличие такого контейнера

    // Получение значений для проверки контрольного числа и серийного номера
    int table[26] = {10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 35, 36, 37, 38};
    QString code = this->ui->new_code_update_edit->text();
    QString rig = this->ui->new_rig_update_box->currentText();
    QString item = this->ui->new_item_update_edit->text();
    QString number = this->ui->new_number_update_edit->text();
    int result = 0;

    // Получение габаритов контейнера
    QString size = this->ui->size_update_box->currentText();

    // Получение числовых значений полей
    double gross = this->ui->gross_update_spin->value();
    double tare_weight = this->ui->tare_weight_update_spin->value();
    double carrying = this->ui->carrying_update_spin->value();
    double capacity = this->ui->capacity_update_spin->value();

    // Проверки на заполненность
    bool is_code = code.length() == 3;
    bool is_item = item.length() == 6;
    bool is_number_full = number.length() == 1;
    bool is_number = true;
    bool is_country = this->ui->country_update_edit->text().length() == 2;
    bool is_gross_null = gross == 0;
    bool is_tare_weight_null = tare_weight == 0;
    bool is_carrying_null = carrying == 0;
    bool is_capacity_null = capacity == 0;

    // Проверка соответствия брутто и габаритов
    bool is_gross = (size[0] == '1' && gross <= 29200) || (size[0] == '2' && gross <= 30480) || (size[0] == '3' && gross <= 30900) ||
                    (size[0] == '4' && gross <= 34300) || (size[0] == 'L' && gross <= 34850);

    // Проверка соответствия массы тары и габаритов
    bool is_tare_weight = (size[0] == '1' && (size[1] == '8' || size[1] == '9') && tare_weight == 1200) ||
                          (size[0] == '1' && size[1] == '0' && tare_weight == 1300) ||
                          (size[0] == '2' && (size[1] == '8' || size[1] == '9') && tare_weight == 2270) ||
                          (size[0] == '2' && size[1] == '0' && tare_weight == 2340) ||
                          (size[0] == '2' && size[1] == '2' && tare_weight == 2350) ||
                          (size[0] == '3' && (size[1] == '8' || size[1] == '9') && tare_weight == 2640) ||
                          (size[0] == '3' && size[1] == '0' && tare_weight == 2740) ||
                          (size[0] == '3' && size[1] == '2' && tare_weight == 2840) ||
                          (size[0] == '3' && size[1] == '5' && tare_weight == 2900) ||
                          (size[0] == '4' && (size[1] == '8' || size[1] == '9') && tare_weight == 4100) ||
                          (size[0] == '4' && size[1] == '0' && tare_weight == 4150) ||
                          (size[0] == '4' && size[1] == '2' && tare_weight == 4200) ||
                          (size[0] == '4' && size[1] == '5' && tare_weight == 4300) ||
                          (size[0] == 'L' && size[1] == '2' && tare_weight == 4700) ||
                          (size[0] == 'L' && size[1] == '5' && tare_weight == 4850);

    // Проверка грузоподъёмности
    bool is_carrying = (tare_weight + carrying) == gross;

    // Проверка соответствия вместимости и габаритов
    bool is_capacity = (size[0] == '1' && (size[1] == '8' || size[1] == '9') && capacity == 16.5) ||
                       (size[0] == '1' && size[1] == '0' && capacity == 18.7) ||
                       (size[0] == '2' && (size[1] == '8' || size[1] == '9') && capacity == 33.2) ||
                       (size[0] == '2' && size[1] == '0' && capacity == 35.3) ||
                       (size[0] == '2' && size[1] == '2' && capacity == 37.4) ||
                       (size[0] == '3' && (size[1] == '8' || size[1] == '9') && capacity == 47.0) ||
                       (size[0] == '3' && size[1] == '0' && capacity == 50.1) ||
                       (size[0] == '3' && size[1] == '2' && capacity == 52.3) ||
                       (size[0] == '3' && size[1] == '5' && capacity == 55.2) ||
                       (size[0] == '4' && (size[1] == '8' || size[1] == '9') && capacity == 66.0) ||
                       (size[0] == '4' && size[1] == '0' && capacity == 67.1) ||
                       (size[0] == '4' && size[1] == '2' && capacity == 75.5) ||
                       (size[0] == '4' && size[1] == '5' && capacity == 84.2) ||
                       (size[0] == 'L' && size[1] == '2' && capacity == 85.3) ||
                       (size[0] == 'L' && size[1] == '5' && capacity == 94.9);

    // Проверка контрольного числа
    if ((code + rig + item).length() == 10)
    {
        // Суммирование символов с весами
        for (int i = 0; i < 10; i++)
        {
            if (i < 3)
                result += ((1 << i) * table[(int)code[i].toLatin1() - 65]);
            else if (i == 3)
                result += ((1 << i) * table[(int)rig[0].toLatin1() - 65]);
            else
                result += ((1 << i) * item[i - 4].digitValue());
        }

        // Остаток от деления на 11
        result = result % 11;

        // Если остаток 10, записываем 0
        if (result == 10)
            result = 0;

        // Сравниваем с записанным контрольным числом
        if (QString::number(result) != number)
            is_number = false;
    }

    // Ключевые параметры проверок
    bool is_find = false;
    bool is_correct = is_code && is_item && is_number_full && is_number && is_country && !is_gross_null && is_gross &&
                      !is_tare_weight_null && is_tare_weight && !is_carrying_null && is_carrying && !is_capacity_null && is_capacity && !is_find;
    bool is_work = true;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->new_code_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_code_update_note_label->setText("* Длина меньше 3 символов");
        this->ui->new_code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find && is_item && is_number_full && is_number)
    {
        this->ui->new_code_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_code_update_note_label->setText("* Маркировка не уникальна");
        this->ui->new_code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_code_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_code_update_note_label->setText("* Обязательно для заполнения");
        this->ui->code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (is_find && is_code && is_item && is_number_full && is_number)
    {
        this->ui->new_rig_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_rig_update_note_label->setText("* Маркировка не уникальна");
        this->ui->new_rig_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->new_item_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_item_update_note_label->setText("* Длина меньше 6 символов");
        this->ui->new_item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find && is_code && is_number_full && is_number)
    {
        this->ui->new_item_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_item_update_note_label->setText("* Маркировка не уникальна");
        this->ui->new_item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_item_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_item_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number_full)
    {
        this->ui->new_number_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_number_update_note_label->setText("* Длина меньше 1 символа");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_number)
    {
        this->ui->new_number_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_number_update_note_label->setText("* Неправильное контрольное число");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (is_find  && is_code && is_item)
    {
        this->ui->new_number_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_number_update_note_label->setText("* Маркировка не уникальна");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_number_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_number_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка кода страны
    if (!is_country)
    {
        this->ui->country_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_update_note_label->setText("* Длина меньше 2 символов");
        this->ui->country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->country_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_update_note_label->setText("* Обязательно для заполнения");
        this->ui->country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка массы брутто
    if (is_gross_null)
    {
        this->ui->gross_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->gross_update_note_label->setText("* Масса равна нулю");
        this->ui->gross_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_gross)
    {
        this->ui->gross_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->gross_update_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->gross_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->gross_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->gross_update_note_label->setText("* Обязательно для заполнения");
        this->ui->gross_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка массы тары
    if (is_tare_weight_null)
    {
        this->ui->tare_weight_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->tare_weight_update_note_label->setText("* Масса равна нулю");
        this->ui->tare_weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_tare_weight)
    {
        this->ui->tare_weight_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->tare_weight_update_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->tare_weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->tare_weight_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->tare_weight_update_note_label->setText("* Обязательно для заполнения");
        this->ui->tare_weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка грузоподъёмности
    if (is_carrying_null)
    {
        this->ui->carrying_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->carrying_update_note_label->setText("* Грузоподъёмность равна нулю");
        this->ui->carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_carrying)
    {
        this->ui->carrying_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->carrying_update_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->carrying_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->carrying_update_note_label->setText("* Обязательно для заполнения");
        this->ui->carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка вместимости
    if (is_capacity_null)
    {
        this->ui->capacity_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->capacity_update_note_label->setText("* Вместимость равна нулю");
        this->ui->capacity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else if (!is_capacity)
    {
        this->ui->capacity_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->capacity_update_note_label->setText("* Несоответствие габаритам контейнера");
        this->ui->capacity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->capacity_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->capacity_update_note_label->setText("* Обязательно для заполнения");
        this->ui->capacity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата проверки контейнера
    if (!is_correct)
    {
        this->ui->space_3_label->setStyleSheet("color: #F5F116;");
        this->ui->space_3_label->setText("* В данных контейнера обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->space_3_label->setStyleSheet("color: #F5F116;");
        this->ui->space_3_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->case_update_button->setEnabled(true);

        this->ui->space_3_label->setStyleSheet("color: #00FF00;");
        this->ui->space_3_label->setText("* Данные контейнера прошли проверку");
    }
}

void StorageWindow::UpdateCase()
{
    // TODO организовать изменение контейнера на сервере

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_3_label->setStyleSheet("color: #F5F116;");
        this->ui->space_3_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->code_update_edit->clear();
        this->ui->rig_update_box->setCurrentIndex(0);
        this->ui->item_update_edit->clear();
        this->ui->number_update_edit->clear();
        this->ui->space_3_label->setStyleSheet("color: #00FF00;");
        this->ui->space_3_label->setText("* Контейнер изменён");
    }
}

void StorageWindow::ClearCaseUpdateForm()
{
    // Возвращение содержимого полей к начальному состоянию
    this->ui->new_code_update_edit->clear();
    this->ui->new_rig_update_box->setCurrentIndex(0);
    this->ui->new_item_update_edit->clear();
    this->ui->new_number_update_edit->clear();
    this->ui->country_update_edit->clear();
    this->ui->size_update_box->setCurrentIndex(0);
    this->ui->case_type_update_box->setCurrentIndex(0);
    this->ui->gross_update_spin->setValue(0);
    this->ui->tare_weight_update_spin->setValue(0);
    this->ui->carrying_update_spin->setValue(0);
    this->ui->capacity_update_spin->setValue(0);

    // Возвращение вида полей к начальному состоянию
    this->ui->new_code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->new_rig_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->new_item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->size_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->case_type_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->gross_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->tare_weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->capacity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение комментариев к начальному состоянию
    this->ui->new_code_update_note_label->setText("* Обязательно для заполнения");
    this->ui->new_rig_update_note_label->setText("* Обязательно для заполнения");
    this->ui->new_item_update_note_label->setText("* Обязательно для заполнения");
    this->ui->new_number_update_note_label->setText("* Обязательно для заполнения");
    this->ui->country_update_note_label->setText("* Обязательно для заполнения");
    this->ui->size_update_note_label->setText("* Обязательно для заполнения");
    this->ui->case_type_update_note_label->setText("* Обязательно для заполнения");
    this->ui->gross_update_note_label->setText("* Обязательно для заполнения");
    this->ui->tare_weight_update_note_label->setText("* Обязательно для заполнения");
    this->ui->carrying_update_note_label->setText("* Обязательно для заполнения");
    this->ui->capacity_update_note_label->setText("* Обязательно для заполнения");

    // Возвращение вида комментариев к начальному состоянию
    this->ui->new_code_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->new_rig_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->new_item_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->new_number_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->size_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->case_type_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->gross_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->tare_weight_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->carrying_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->capacity_update_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение кнопок к начальному состоянию
    this->ui->space_3_label->clear();
    this->ui->case_check_update_button->setEnabled(true);
    this->ui->case_update_button->setEnabled(false);
}

void StorageWindow::ActivateCaseUpdateForm(bool flag)
{
    // Активация или блокировка полей формы
    this->ui->new_code_update_edit->setEnabled(flag);
    this->ui->new_rig_update_box->setEnabled(flag);
    this->ui->new_item_update_edit->setEnabled(flag);
    this->ui->new_number_update_edit->setEnabled(flag);
    this->ui->country_update_edit->setEnabled(flag);
    this->ui->size_update_box->setEnabled(flag);
    this->ui->case_type_update_box->setEnabled(flag);
    this->ui->gross_update_spin->setEnabled(flag);
    this->ui->tare_weight_update_spin->setEnabled(flag);
    this->ui->carrying_update_spin->setEnabled(flag);
    this->ui->capacity_update_spin->setEnabled(flag);

    // Установка внешнего вида полей
    if (flag)
    {
        this->ui->new_code_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_rig_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_item_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->size_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->case_type_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->gross_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->tare_weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->capacity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->new_code_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->new_rig_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->new_item_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->new_number_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->country_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->size_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->case_type_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->gross_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->tare_weight_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->carrying_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->capacity_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
    }
}

void StorageWindow::DeleteCaseByOptions()
{
    // TODO организовать удаление контейнера на сервере

    // Заглушка отправки
    bool is_code = this->ui->code_delete_edit->text().length() == 3;
    bool is_item = this->ui->item_delete_edit->text().length() == 6;
    bool is_number = this->ui->number_delete_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка кода владельца
    if (!is_code)
    {
        this->ui->code_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->code_delete_note_label->setText("* Длина меньше 3 символов");
        this->ui->code_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->code_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->code_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->code_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->code_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->code_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка идентификатора оборудования
    if (!is_find)
    {
        this->ui->rig_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_delete_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->rig_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->rig_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->rig_delete_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка серийного номера
    if (!is_item)
    {
        this->ui->item_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->item_delete_note_label->setText("* Длина меньше 6 символов");
        this->ui->item_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->item_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->item_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->item_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->item_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->item_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка контрольного числа
    if (!is_number)
    {
        this->ui->number_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->number_delete_note_label->setText("* Длина меньше 1 символа");
        this->ui->number_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->number_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->number_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->number_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->number_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->number_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата удаления пользователя
    if (!is_correct)
    {
        this->ui->case_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->case_delete_label->setText("* Ошибка в данных контейнера");
    }
    else if (!is_work)
    {
        this->ui->case_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->case_delete_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->case_delete_label->setStyleSheet("color: #F5F116;");
            this->ui->case_delete_label->setText("* Контейнера нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->case_delete_label->setStyleSheet("color: #F5F116;");
                this->ui->case_delete_label->setText("* Контейнер занят сотрудником");
            }
            else
            {
                this->ui->code_delete_edit->clear();
                this->ui->rig_delete_box->setCurrentIndex(0);
                this->ui->item_delete_edit->clear();
                this->ui->number_delete_edit->clear();

                this->ui->case_delete_label->setStyleSheet("color: #00FF00;");
                this->ui->case_delete_label->setText("* Контейнер удалён");
            }
        }
    }
}

void StorageWindow::DeleteCaseByBid()
{
    // TODO организовать удаление контейнера на сервере

    // Заглушка отправки
    bool is_correct = this->ui->bid_id_delete_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка идентификатора заявки
    if (!is_correct)
    {
        this->ui->bid_id_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_delete_note_label->setText("* Длина меньше 14 символов");
        this->ui->bid_id_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->bid_id_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->bid_id_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата удаления контейнера
    if (!is_correct)
    {
        this->ui->bid_id_delete_label_2->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_delete_label_2->setText("* Ошибка в идентификаторе заявки");
    }
    else if (!is_work)
    {
        this->ui->bid_id_delete_label_2->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_delete_label_2->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->bid_id_delete_label_2->setStyleSheet("color: #F5F116;");
            this->ui->bid_id_delete_label_2->setText("* Контейнеров нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->bid_id_delete_label_2->setStyleSheet("color: #F5F116;");
                this->ui->bid_id_delete_label_2->setText("* Контейнеры нельзя удалить");
            }
            else
            {
                this->ui->bid_id_delete_edit->clear();
                this->ui->bid_id_delete_label_2->setStyleSheet("color: #00FF00;");
                this->ui->bid_id_delete_label_2->setText("* Контейнеры удалены");
            }
        }
    }
}

#include "storagewindow.h"
#include "ui_storagewindow.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>

StorageWindow::StorageWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::StorageWindow;
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

    // Инициализация таблицы контейнеров
    this->case_page = 1;

    this->case_model = new QStandardItemModel(0, 5);
    this->case_model->setHeaderData(0, Qt::Horizontal, "Код\nвладельца");
    this->case_model->setHeaderData(1, Qt::Horizontal, "Идентификатор\nкатегории\nоборудования");
    this->case_model->setHeaderData(2, Qt::Horizontal, "Серийный\nномер");
    this->case_model->setHeaderData(3, Qt::Horizontal, "Контрольное\nчисло");
    this->case_model->setHeaderData(4, Qt::Horizontal, "Статус");
    this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->case_table->setModel(this->case_model);

    // Инициализация таблицы назначенных контейнеров
    this->case_assigned_page = 1;

    this->case_assigned_model = new QStandardItemModel(0, 5);
    this->case_assigned_model->setHeaderData(0, Qt::Horizontal, "Код\nвладельца");
    this->case_assigned_model->setHeaderData(1, Qt::Horizontal, "Идентификатор\nкатегории\nоборудования");
    this->case_assigned_model->setHeaderData(2, Qt::Horizontal, "Серийный\nномер");
    this->case_assigned_model->setHeaderData(3, Qt::Horizontal, "Контрольное\nчисло");
    this->case_assigned_model->setHeaderData(4, Qt::Horizontal, "Статус");
    this->ui->case_assigned_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->case_assigned_table->setModel(this->case_assigned_model);

    // Установка страниц форм
    this->bid_read_page = 1;
    this->case_add_page = 1;
    this->case_update_page = 1;
    this->case_read_page = 1;

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

    // Установка связей между сигналами и методами для пагинации заявок
    connect(this->ui->bid_id_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::BidList);
    connect(this->ui->bid_date_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::BidList);
    connect(this->ui->bid_change_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::BidList);
    connect(this->ui->bid_status_filter_box, &QComboBox::currentIndexChanged, this, &StorageWindow::BidList);
    connect(this->ui->bid_left_button, &QPushButton::clicked, this, [this](){ this->bid_page--; BidList(); });
    connect(this->ui->bid_right_button, &QPushButton::clicked, this, [this](){ this->bid_page++; BidList(); });
    connect(this->ui->bid_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &StorageWindow::BidList);

    // Установка связей между сигналами и методами для пагинации контейнеров
    connect(this->ui->code_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::CaseList);
    connect(this->ui->rig_filter_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CaseList);
    connect(this->ui->item_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::CaseList);
    connect(this->ui->number_filter_edit, &QLineEdit::textChanged, this, &StorageWindow::CaseList);
    connect(this->ui->case_status_filter_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CaseList);
    connect(this->ui->case_left_button, &QPushButton::clicked, this, [this](){ this->case_page--; CaseList(); });
    connect(this->ui->case_right_button, &QPushButton::clicked, this, [this](){ this->case_page++; CaseList(); });
    connect(this->ui->case_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &StorageWindow::CaseList);

    // Установка связей между сигналами и методами для пагинации назначенных контейнеров
    connect(this->ui->case_assigned_left_button, &QPushButton::clicked, this, [this](){ this->case_assigned_page--; NominatedCaseList(); });
    connect(this->ui->case_assigned_right_button, &QPushButton::clicked, this, [this](){ this->case_assigned_page++; NominatedCaseList(); });
    connect(this->ui->case_assigned_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &StorageWindow::NominatedCaseList);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &StorageWindow::FindBidRead);

    // Пагинация формы просмотра заявки
    connect(this->ui->bid_read_left_button, &QPushButton::clicked, this, [this](){ this->bid_read_page--; ChooseBidReadPage(); });
    connect(this->ui->bid_read_right_button, &QPushButton::clicked, this, [this](){ this->bid_read_page++; ChooseBidReadPage(); });

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &StorageWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &StorageWindow::FindCaseRead);

    // Пагинация формы просмотра контейнера
    connect(this->ui->case_read_left_button, &QPushButton::clicked, this, [this](){ this->case_read_page--; ChooseCaseReadPage(); });
    connect(this->ui->case_read_right_button, &QPushButton::clicked, this, [this](){ this->case_read_page++; ChooseCaseReadPage(); });

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

    // Пагинация формы добавления контейнера
    connect(this->ui->case_add_left_button, &QPushButton::clicked, this, [this](){ this->case_add_page--; ChooseCaseAddPage(); });
    connect(this->ui->case_add_right_button, &QPushButton::clicked, this, [this](){ this->case_add_page++; ChooseCaseAddPage(); });

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

    // Пагинация формы изменения контейнера
    connect(this->ui->case_update_left_button, &QPushButton::clicked, this, [this](){ this->case_update_page--; ChooseCaseUpdatePage(); });
    connect(this->ui->case_update_right_button, &QPushButton::clicked, this, [this](){ this->case_update_page++; ChooseCaseUpdatePage(); });

    // Установка связей между сигналами и методами для удаления контейнера
    connect(this->ui->code_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->rig_delete_box, &QComboBox::currentIndexChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->item_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->number_delete_edit, &QLineEdit::textChanged, this->ui->case_delete_label, &QLabel::clear);
    connect(this->ui->case_delete_button, &QPushButton::clicked, this, &StorageWindow::DeleteCaseByOptions);
    connect(this->ui->bid_id_delete_edit, &QLineEdit::textChanged, this->ui->bid_id_delete_label_2, &QLabel::clear);
    connect(this->ui->bid_id_delete_button, &QPushButton::clicked, this, &StorageWindow::DeleteCaseByBid);

    // Заполнение таблиц
    BidList();
    CaseList();

    ChooseBidReadPage();
    ChooseCaseAddPage();

    ChooseCaseUpdatePage();
    this->ui->case_update_right_button->setEnabled(false);

    ChooseCaseReadPage();
}

StorageWindow::~StorageWindow()
{
    this->connection.Disconnect();
    delete this->ui;
}

void StorageWindow::CheckBidIdWork()
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
            is_work = connection.Send("D00" + this->bid_status + '\v' + this->bid_number);

            if (is_work)
            {
                // Принимаем сообщение
                result = connection.Receive();

                is_work = result != "\x18";

                if (is_work)
                {
                    this->bid_number = "";
                    this->bid_status = "";
                    this->TN_VED = "";
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    ClearBidWorkForm(0x1F);
    ActivateBidWorkForm(false, 0x1F);

    this->ui->bid_choose_work_label->clear();
}

void StorageWindow::FindBidWork()
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
            is_work = connection.Send("D01" + this->username + '\v' + this->ui->bid_id_work_edit->text());

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
                QStringList list = result.split('\v');

                this->bid_number = list[1];
                this->bid_status = list[32];
                this->TN_VED = list[7];

                this->ui->bid_length_weighting_spin->setValue(list[9].toDouble());
                this->ui->bid_width_weighting_spin->setValue(list[10].toDouble());
                this->ui->bid_height_weighting_spin->setValue(list[11].toDouble());
                this->ui->bid_mass_weighting_spin->setValue(list[12].toDouble());
                this->ui->bid_quantity_weighting_spin->setValue(list[15].toInt());
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

void StorageWindow::CheckWeightingForm()
{
    ClearBidWorkForm(0x1E);
    ActivateBidWorkForm(false, 0x1E);

    this->ui->weight_check_work_label->clear();
}

void StorageWindow::CheckWeighting()
{
    // Флаги проверок
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
    ClearBidWorkForm(0x1C);
    ActivateBidWorkForm(false, 0x1C);

    // Флаги проверок
    bool is_work = true;
    bool is_find = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "D02" +
                          QString::number(this->ui->bid_length_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_width_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_height_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_mass_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_quantity_weighting_spin->value()) + '\v' +
                          this->TN_VED + '\v' +
                          this->username;

        is_work = connection.Send(message);

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

    if (is_work)
    {
        if (is_find)
            NominatedCaseList();
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

void StorageWindow::CheckDistribution()
{
    // Флаги проверок
    bool is_work = true;
    bool is_right = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "D03" +
                          QString::number(this->ui->bid_length_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_width_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_height_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_mass_weighting_spin->value()) + '\v' +
                          QString::number(this->ui->bid_quantity_weighting_spin->value()) + '\v' +
                          this->username;

        is_work = connection.Send(message);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result != "\x18";
            is_right = result == "1";
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void StorageWindow::Refusal()
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

    // Проверка комментария
    for (int i = 0; i < comment.length(); i++)
    {
        if (!grant_symbols.contains(comment[i]))
        {
            is_correct = false;
            break;
        }
    }

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
            is_work = connection.Send("D04" + comment + "\vОтказ\v" + this->bid_number);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";

                if (result == "1")
                {
                    this->bid_number = "";
                    this->bid_status = "";
                    this->TN_VED = "";
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

    if(is_correct)
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

void StorageWindow::Reception()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        is_work = connection.Send("D05Обрабатывается на складе\v" + this->bid_number + '\v' + this->username);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result == "1";

            if (is_work)
            {
                this->bid_number = "";
                this->bid_status = "";
                this->TN_VED = "";
            }
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
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

    // Очистка распределения
    if ((mod & 0x4) == 0x4)
    {
        if (this->case_assigned_model->rowCount() > 0)
        {

            QString result;
            bool is_work = connection.Connect(this->host, 8081);

            if (is_work)
            {
                is_work = connection.Send("D06" + this->username);

                if (is_work)
                {
                    result = connection.Receive();

                    is_work = result == "1";
                }

                // Удаляем соединение
                if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                    connection.Disconnect();
            }
        }

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
    bool is_code = this->ui->code_assigned_filter_edit->text().length() == 3;
    bool is_item = this->ui->item_assigned_filter_edit->text().length() == 6;
    bool is_number = this->ui->number_assigned_filter_edit->text().length() == 1;
    bool is_status = this->ui->status_assigned_filter_box->currentIndex() == 0;
    bool is_correct = is_code && is_item && is_number && is_status;
    bool is_work = true;
    bool is_find = true;
    bool is_wrong = false;

    // Результат работы сервера
    QString result;

    if(is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "D08" +
                              this->ui->code_assigned_filter_edit->text() + '\v' +
                              this->ui->rig_assigned_filter_box->currentText() + '\v' +
                              this->ui->item_assigned_filter_edit->text() + '\v' +
                              this->ui->number_assigned_filter_edit->text() + '\v' +
                              this->ui->status_assigned_filter_box->currentText() + '\v' +
                              this->username + '\v' +
                              this->TN_VED;

            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";
                is_find = result != "\x00";
                is_wrong = result == "2";
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    // Проверка кода владельца
    if (!is_code || !is_find || is_wrong)
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->code_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка идентификатора оборудования
    if (!is_find || is_wrong)
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->rig_assigned_filter_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка серийного номера
    if (!is_item || !is_find || is_wrong)
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->item_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка контрольного числа
    if (!is_number || !is_find || is_wrong)
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    else
        this->ui->number_assigned_filter_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Проверка статуса
    if (!is_status || !is_find || is_wrong)
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
            if (is_wrong)
            {
                this->ui->space_2_label->setStyleSheet("color: #F5F116;");
                this->ui->space_2_label->setText("* Несоответствие типа контейнера");
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

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find && !is_wrong)
            {
                this->case_assigned_page = 1;

                NominatedCaseList();
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

void StorageWindow::ReturnCase()
{
    bool is_code = this->ui->code_assigned_filter_edit->text().length() == 3;
    bool is_item = this->ui->item_assigned_filter_edit->text().length() == 6;
    bool is_number = this->ui->number_assigned_filter_edit->text().length() == 1;
    bool is_status = this->ui->status_assigned_filter_box->currentIndex() == 1;
    bool is_correct = is_code && is_item && is_number && is_status;
    bool is_work = true;
    bool is_find = true;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "D09" +
                              this->ui->code_assigned_filter_edit->text() + '\v' +
                              this->ui->rig_assigned_filter_box->currentText() + '\v' +
                              this->ui->item_assigned_filter_edit->text() + '\v' +
                              this->ui->number_assigned_filter_edit->text() + '\v' +
                              this->username;

            is_work = connection.Send(message);

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

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find)
            {
                this->case_assigned_page = 1;

                NominatedCaseList();
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

void StorageWindow::BidList()
{
    if ((this->ui->bid_id_filter_edit->text().length() == 14 || this->ui->bid_id_filter_edit->text() == "") &&
        (this->ui->bid_date_filter_edit->text().length() == 8 || this->ui->bid_date_filter_edit->text() == "") &&
        (this->ui->bid_change_filter_edit->text().length() == 8 || this->ui->bid_change_filter_edit->text() == ""))
    {
        QString message = "D10";

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

void StorageWindow::CaseList()
{
    if ((this->ui->code_filter_edit->text().length() == 3 || this->ui->code_filter_edit->text() == "") &&
        (this->ui->item_filter_edit->text().length() == 6 || this->ui->item_filter_edit->text() == "") &&
        (this->ui->number_filter_edit->text().length() == 1 || this->ui->number_filter_edit->text() == ""))
    {
        QString message = "D11";

        int section =  this->ui->case_table->horizontalHeader()->sortIndicatorSection();
        Qt::SortOrder order = this->ui->case_table->horizontalHeader()->sortIndicatorOrder();

        if (section == 0)
            message += "c.owner_code";
        else if (section == 1)
            message += "e.equipment_type";
        else if (section == 2)
            message += "c.serial_number";
        else if (section == 3)
            message += "c.check_number";
        else if (section == 4)
            message += "s.container_status";

        if (order == Qt::AscendingOrder)
            message += "\vASC";
        else
            message += "\vDESC";

        message += ('\v' +QString::number(this->case_page));

        message += ("\v11");

        if (this->ui->code_filter_edit->text().length() == 3)
            message += ('\v' + this->ui->code_filter_edit->text());
        else
            message += '\v';

        message += ('\v' + this->ui->rig_filter_box->currentText());

        if (this->ui->item_filter_edit->text().length() == 6)
            message += ('\v' + this->ui->item_filter_edit->text());
        else
            message += '\v';

        if (this->ui->number_filter_edit->text().length() == 1)
            message += ('\v' + this->ui->number_filter_edit->text());
        else
            message += '\v';

        message += ('\v' + this->ui->case_status_filter_box->currentText());

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

                    this->case_page = fields[fields.length() - 2].toInt();

                    if (this->case_page == 1)
                        this->ui->case_left_button->setEnabled(false);
                    else
                        this->ui->case_left_button->setEnabled(true);

                    if (fields[fields.length() - 1] == "1")
                        this->ui->case_right_button->setEnabled(true);
                    else
                        this->ui->case_right_button->setEnabled(false);

                    this->case_model->removeRows(0, this->case_model->rowCount());

                    for (int i = 0; i < (fields.length() - 2); i += 5)
                    {
                        this->case_model->insertRow(this->case_model->rowCount());

                        this->case_model->setData(this->case_model->index(i / 5, 0), fields[i]);
                        this->case_model->setData(this->case_model->index(i / 5, 1), fields[i + 1]);
                        this->case_model->setData(this->case_model->index(i / 5, 2), fields[i + 2]);
                        this->case_model->setData(this->case_model->index(i / 5, 3), fields[i + 3]);
                        this->case_model->setData(this->case_model->index(i / 5, 4), fields[i + 4]);
                    }

                    this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();

            if (!is_work || !is_find)
            {
                this->ui->case_left_button->setEnabled(false);
                this->ui->case_right_button->setEnabled(false);

                this->case_model->removeRows(0, this->case_model->rowCount());
                this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                this->case_page = 1;
            }
        }
    }
    else
    {
        this->ui->case_left_button->setEnabled(false);
        this->ui->case_right_button->setEnabled(false);

        this->case_model->removeRows(0, this->case_model->rowCount());
        this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->case_page = 1;
    }
}

void StorageWindow::NominatedCaseList()
{
    QString message = "D07";

    int section =  this->ui->case_assigned_table->horizontalHeader()->sortIndicatorSection();
    Qt::SortOrder order = this->ui->case_assigned_table->horizontalHeader()->sortIndicatorOrder();

    if (section == 0)
        message += "c.owner_code";
    else if (section == 1)
        message += "eq.equipment_type";
    else if (section == 2)
        message += "c.serial_number";
    else if (section == 3)
        message += "c.check_number";
    else if (section == 4)
        message += "st.container_status";

    if (order == Qt::AscendingOrder)
        message += "\vASC";
    else
        message += "\vDESC";

    message += ('\v' +QString::number(this->case_assigned_page));

    message += ("\v7\v");

    message += this->username;

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

                this->case_assigned_page = fields[fields.length() - 2].toInt();

                if (this->case_assigned_page == 1)
                    this->ui->case_assigned_left_button->setEnabled(false);
                else
                    this->ui->case_assigned_left_button->setEnabled(true);

                if (fields[fields.length() - 1] == "1")
                    this->ui->case_assigned_right_button->setEnabled(true);
                else
                    this->ui->case_assigned_right_button->setEnabled(false);

                this->case_assigned_model->removeRows(0, this->case_assigned_model->rowCount());

                for (int i = 0; i < (fields.length() - 2); i += 5)
                {
                    this->case_assigned_model->insertRow(this->case_assigned_model->rowCount());

                    this->case_assigned_model->setData(this->case_assigned_model->index(i / 5, 0), fields[i]);
                    this->case_assigned_model->setData(this->case_assigned_model->index(i / 5, 1), fields[i + 1]);
                    this->case_assigned_model->setData(this->case_assigned_model->index(i / 5, 2), fields[i + 2]);
                    this->case_assigned_model->setData(this->case_assigned_model->index(i / 5, 3), fields[i + 3]);
                    this->case_assigned_model->setData(this->case_assigned_model->index(i / 5, 4), fields[i + 4]);
                }

                this->ui->case_assigned_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            }
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

    if (!is_work || !is_find)
    {
        this->ui->case_assigned_left_button->setEnabled(false);
        this->ui->case_assigned_right_button->setEnabled(false);

        this->case_assigned_model->removeRows(0, this->case_assigned_model->rowCount());
        this->ui->case_assigned_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->case_assigned_page = 1;
    }
}

void StorageWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void StorageWindow::FindBidRead()
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
            is_work = connection.Send("D12" + this->ui->bid_id_read_edit->text());

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

void StorageWindow::ChooseBidReadPage()
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

    this->ui->scrollArea_3->widget()->adjustSize();
    this->ui->scrollArea_3->widget()->updateGeometry();
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

    this->bid_read_page = 1;

    ChooseBidReadPage();
}

void StorageWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void StorageWindow::FindCaseRead()
{
    // Флаги проверок
    bool is_code = this->ui->code_read_edit->text().length() == 3;
    bool is_item = this->ui->item_read_edit->text().length() == 6;
    bool is_number = this->ui->number_read_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send("D13" + this->ui->code_read_edit->text() + '\v' +
                                            this->ui->rig_read_box->currentText() + '\v' +
                                            this->ui->item_read_edit->text() + '\v' +
                                            this->ui->number_read_edit->text());

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

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find)
            {
                QStringList list = result.split('\v');

                this->ui->country_read_edit->setText(list[5]);
                this->ui->size_read_edit->setText(list[6]);
                this->ui->case_type_read_edit->setText(list[7]);
                this->ui->gross_read_spin->setValue(list[8].toDouble());
                this->ui->tare_weight_read_spin->setValue(list[9].toDouble());
                this->ui->carrying_read_spin->setValue(list[10].toDouble());
                this->ui->capacity_read_spin->setValue(list[11].toDouble());
                this->ui->IMO_read_edit->setText(list[14]);
                this->ui->position_read_edit->setText(list[12]);
                this->ui->claim_read_edit->setText(list[15]);
                this->ui->case_status_read_edit->setText(list[13]);
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

void StorageWindow::ChooseCaseReadPage()
{
    this->ui->country_read_edit->setVisible(false);
    this->ui->size_read_edit->setVisible(false);
    this->ui->case_type_read_edit->setVisible(false);
    this->ui->gross_read_spin->setVisible(false);
    this->ui->tare_weight_read_spin->setVisible(false);
    this->ui->carrying_read_spin->setVisible(false);
    this->ui->capacity_read_spin->setVisible(false);
    this->ui->IMO_read_edit->setVisible(false);
    this->ui->position_read_edit->setVisible(false);
    this->ui->claim_read_edit->setVisible(false);
    this->ui->case_status_read_edit->setVisible(false);

    this->ui->country_read_label->setVisible(false);
    this->ui->size_read_label->setVisible(false);
    this->ui->case_type_read_label->setVisible(false);
    this->ui->gross_read_label->setVisible(false);
    this->ui->tare_weight_read_label->setVisible(false);
    this->ui->carrying_read_label->setVisible(false);
    this->ui->capacity_read_label->setVisible(false);
    this->ui->IMO_read_label->setVisible(false);
    this->ui->position_read_label->setVisible(false);
    this->ui->claim_read_label->setVisible(false);
    this->ui->case_status_read_label->setVisible(false);

    if (this->case_read_page == 1)
    {
        this->ui->country_read_edit->setVisible(true);
        this->ui->size_read_edit->setVisible(true);
        this->ui->case_type_read_edit->setVisible(true);
        this->ui->gross_read_spin->setVisible(true);

        this->ui->country_read_label->setVisible(true);
        this->ui->size_read_label->setVisible(true);
        this->ui->case_type_read_label->setVisible(true);
        this->ui->gross_read_label->setVisible(true);
    }
    else if (this->case_read_page == 2)
    {
        this->ui->tare_weight_read_spin->setVisible(true);
        this->ui->carrying_read_spin->setVisible(true);
        this->ui->capacity_read_spin->setVisible(true);
        this->ui->IMO_read_edit->setVisible(true);

        this->ui->tare_weight_read_label->setVisible(true);
        this->ui->carrying_read_label->setVisible(true);
        this->ui->capacity_read_label->setVisible(true);
        this->ui->IMO_read_label->setVisible(true);
    }
    else if (this->case_read_page == 3)
    {
        this->ui->position_read_edit->setVisible(true);
        this->ui->claim_read_edit->setVisible(true);
        this->ui->case_status_read_edit->setVisible(true);

        this->ui->position_read_label->setVisible(true);
        this->ui->claim_read_label->setVisible(true);
        this->ui->case_status_read_label->setVisible(true);
    }

    if (this->case_read_page == 1)
        this->ui->case_read_left_button->setEnabled(false);
    else
        this->ui->case_read_left_button->setEnabled(true);

    if (this->case_read_page == 3)
        this->ui->case_read_right_button->setEnabled(false);
    else
        this->ui->case_read_right_button->setEnabled(true);

    this->ui->case_read_page_label->setText("Страница " + QString::number(this->case_read_page) + " из 3");

    this->ui->scrollArea_4->widget()->adjustSize();
    this->ui->scrollArea_4->widget()->updateGeometry();
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

    this->case_read_page = 1;

    ChooseCaseReadPage();
}

void StorageWindow::CheckCaseAddForm()
{
    this->ui->space_1_label->clear();
    this->ui->case_add_button->setEnabled(false);
}

void StorageWindow::CheckCaseAddContents()
{
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
                      !is_tare_weight_null && is_tare_weight && !is_carrying_null && is_carrying && !is_capacity_null && is_capacity;
    bool is_work = true;

    // Результат работы сервера
    QString result_work;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "D14" +
                              this->ui->code_add_edit->text() + '\v' +
                              this->ui->rig_add_box->currentText() + '\v' +
                              this->ui->item_add_edit->text() + '\v' +
                              this->ui->number_add_edit->text();

            is_work = connection.Send(message);

            if (is_work)
            {
                result_work = connection.Receive();

                is_work = result_work != "\x18";
                is_find = result_work == "2";
                is_correct = is_correct && !is_find;
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

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

void StorageWindow::AddCase()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "D15" +
                          this->ui->code_add_edit->text() + '\v' +
                          this->ui->rig_add_box->currentText() + '\v' +
                          this->ui->item_add_edit->text() + '\v' +
                          this->ui->number_add_edit->text() + '\v' +
                          this->ui->country_add_edit->text() + '\v' +
                          this->ui->size_add_box->currentText() + '\v' +
                          this->ui->case_type_add_box->currentText() + '\v' +
                          QString::number(this->ui->gross_add_spin->value()) + '\v' +
                          QString::number(this->ui->tare_weight_add_spin->value()) + '\v' +
                          QString::number(this->ui->carrying_add_spin->value()) + '\v' +
                          QString::number(this->ui->capacity_add_spin->value()) + '\v' +
                          "Свободен";

        is_work = connection.Send(message);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result != "\x18";
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void StorageWindow::ChooseCaseAddPage()
{
    this->ui->code_add_edit->setVisible(false);
    this->ui->rig_add_box->setVisible(false);
    this->ui->item_add_edit->setVisible(false);
    this->ui->number_add_edit->setVisible(false);
    this->ui->country_add_edit->setVisible(false);
    this->ui->size_add_box->setVisible(false);
    this->ui->case_type_add_box->setVisible(false);
    this->ui->gross_add_spin->setVisible(false);
    this->ui->tare_weight_add_spin->setVisible(false);
    this->ui->carrying_add_spin->setVisible(false);
    this->ui->capacity_add_spin->setVisible(false);

    this->ui->code_add_note_label->setVisible(false);
    this->ui->rig_add_note_label->setVisible(false);
    this->ui->item_add_note_label->setVisible(false);
    this->ui->number_add_note_label->setVisible(false);
    this->ui->country_add_note_label->setVisible(false);
    this->ui->size_add_note_label->setVisible(false);
    this->ui->case_type_add_note_label->setVisible(false);
    this->ui->gross_add_note_label->setVisible(false);
    this->ui->tare_weight_add_note_label->setVisible(false);
    this->ui->carrying_add_note_label->setVisible(false);
    this->ui->capacity_add_note_label->setVisible(false);

    this->ui->code_add_label->setVisible(false);
    this->ui->rig_add_label->setVisible(false);
    this->ui->item_add_label->setVisible(false);
    this->ui->number_add_label->setVisible(false);
    this->ui->country_add_label->setVisible(false);
    this->ui->size_add_label->setVisible(false);
    this->ui->case_type_add_label->setVisible(false);
    this->ui->gross_add_label->setVisible(false);
    this->ui->tare_weight_add_label->setVisible(false);
    this->ui->carrying_add_label->setVisible(false);
    this->ui->capacity_add_label->setVisible(false);

    if (this->case_add_page == 1)
    {
        this->ui->code_add_edit->setVisible(true);
        this->ui->rig_add_box->setVisible(true);
        this->ui->item_add_edit->setVisible(true);
        this->ui->number_add_edit->setVisible(true);
        this->ui->country_add_edit->setVisible(true);
        this->ui->size_add_box->setVisible(true);

        this->ui->code_add_note_label->setVisible(true);
        this->ui->rig_add_note_label->setVisible(true);
        this->ui->item_add_note_label->setVisible(true);
        this->ui->number_add_note_label->setVisible(true);
        this->ui->country_add_note_label->setVisible(true);
        this->ui->size_add_note_label->setVisible(true);

        this->ui->code_add_label->setVisible(true);
        this->ui->rig_add_label->setVisible(true);
        this->ui->item_add_label->setVisible(true);
        this->ui->number_add_label->setVisible(true);
        this->ui->country_add_label->setVisible(true);
        this->ui->size_add_label->setVisible(true);
    }
    else if (this->case_add_page == 2)
    {
        this->ui->case_type_add_box->setVisible(true);
        this->ui->gross_add_spin->setVisible(true);
        this->ui->tare_weight_add_spin->setVisible(true);
        this->ui->carrying_add_spin->setVisible(true);
        this->ui->capacity_add_spin->setVisible(true);

        this->ui->case_type_add_note_label->setVisible(true);
        this->ui->gross_add_note_label->setVisible(true);
        this->ui->tare_weight_add_note_label->setVisible(true);
        this->ui->carrying_add_note_label->setVisible(true);
        this->ui->capacity_add_note_label->setVisible(true);

        this->ui->case_type_add_label->setVisible(true);
        this->ui->gross_add_label->setVisible(true);
        this->ui->tare_weight_add_label->setVisible(true);
        this->ui->carrying_add_label->setVisible(true);
        this->ui->capacity_add_label->setVisible(true);
    }

    if (this->case_add_page == 1)
        this->ui->case_add_left_button->setEnabled(false);
    else
        this->ui->case_add_left_button->setEnabled(true);

    if (this->case_add_page == 2)
        this->ui->case_add_right_button->setEnabled(false);
    else
        this->ui->case_add_right_button->setEnabled(true);

    this->ui->case_add_page_label->setText("Страница " + QString::number(this->case_add_page) + " из 2");

    this->ui->scrollArea_5->widget()->adjustSize();
    this->ui->scrollArea_5->widget()->updateGeometry();
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

    this->case_add_page = 1;

    ChooseCaseAddPage();

    // Возвращение кнопок к начальному состоянию
    this->ui->space_1_label->clear();
    this->ui->case_check_add_button->setEnabled(true);
    this->ui->case_add_button->setEnabled(false);
}

void StorageWindow::CheckCaseOptionsUpdate()
{
    // Флаги проверок
        bool is_work = true;

    // Результат работы сервера
    QString result;

    if (this->case_code.length() == 3)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "D16" +
                              this->case_status + '\v' +
                              this->case_code + '\v' +
                              this->case_rig + '\v' +
                              this->case_item + '\v' +
                              this->case_number;

            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";

                if (is_work)
                {
                    this->case_status = "";
                    this->case_code = "";
                    this->case_rig = "";
                    this->case_item = "";
                    this->case_number = "";
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    ClearCaseUpdateForm();
    ActivateCaseUpdateForm(false);

    this->ui->case_choose_update_label->clear();
    this->ui->case_check_update_button->setEnabled(false);
}

void StorageWindow::FindCaseUpdate()
{
    // Флаги проверок
    bool is_code = this->ui->code_update_edit->text().length() == 3;
    bool is_item = this->ui->item_update_edit->text().length() == 6;
    bool is_number = this->ui->number_update_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
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
            QString message = "D17" +
                              this->username + '\v' +
                              this->ui->code_update_edit->text() + '\v' +
                              this->ui->rig_update_box->currentText() + '\v' +
                              this->ui->item_update_edit->text() + '\v' +
                              this->ui->number_update_edit->text();

            is_work = connection.Send(message);

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

    if (is_correct)
    {
        if(is_work)
        {
            if(is_find && !is_busy)
            {
                QStringList list = result.split('\v');

                this->case_code = this->ui->code_update_edit->text();
                this->case_rig = this->ui->rig_update_box->currentText();
                this->case_item = this->ui->item_update_edit->text();
                this->case_number = this->ui->number_update_edit->text();
                this->case_status = list[13];

                this->ui->new_code_update_edit->setText(this->case_code);
                this->ui->new_rig_update_box->setCurrentText(this->case_rig);
                this->ui->new_item_update_edit->setText(this->case_item);
                this->ui->new_number_update_edit->setText(this->case_number);
                this->ui->country_update_edit->setText(list[5]);
                this->ui->size_update_box->setCurrentText(list[6]);
                this->ui->case_type_update_box->setCurrentText(list[7]);
                this->ui->gross_update_spin->setValue(list[8].toDouble());
                this->ui->tare_weight_update_spin->setValue(list[9].toDouble());
                this->ui->carrying_update_spin->setValue(list[10].toDouble());
                this->ui->capacity_update_spin->setValue(list[11].toDouble());
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

void StorageWindow::CheckCaseUpdateForm()
{
    this->ui->space_3_label->clear();
    this->ui->case_update_button->setEnabled(false);
}

void StorageWindow::CheckCaseUpdateContents()
{
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
                      !is_tare_weight_null && is_tare_weight && !is_carrying_null && is_carrying && !is_capacity_null && is_capacity;
    bool is_work = true;

    // Результат работы сервера
    QString result_work;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "D18" +
                              this->ui->new_code_update_edit->text() + '\v' +
                              this->ui->new_rig_update_box->currentText() + '\v' +
                              this->ui->new_item_update_edit->text() + '\v' +
                              this->ui->new_number_update_edit->text() + '\v' +
                              this->ui->code_update_edit->text() + '\v' +
                              this->ui->rig_update_box->currentText() + '\v' +
                              this->ui->item_update_edit->text() + '\v' +
                              this->ui->number_update_edit->text();

            is_work = connection.Send(message);

            if (is_work)
            {
                result_work = connection.Receive();

                is_work = result_work != "\x18";
                is_find = result_work == "2";
                is_correct = is_correct && !is_find;
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

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

void StorageWindow::UpdateCase()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;


    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "D19" +
                          this->case_status + '\v' +
                          this->ui->new_code_update_edit->text() + '\v' +
                          this->ui->new_rig_update_box->currentText() + '\v' +
                          this->ui->new_item_update_edit->text() + '\v' +
                          this->ui->new_number_update_edit->text() + '\v' +
                          this->ui->country_update_edit->text() + '\v' +
                          this->ui->size_update_box->currentText() + '\v' +
                          this->ui->case_type_update_box->currentText() + '\v' +
                          QString::number(this->ui->gross_update_spin->value()) + '\v' +
                          QString::number(this->ui->tare_weight_update_spin->value()) + '\v' +
                          QString::number(this->ui->carrying_update_spin->value()) + '\v' +
                          QString::number(this->ui->capacity_update_spin->value()) + '\v' +
                          this->ui->code_update_edit->text() + '\v' +
                          this->ui->rig_update_box->currentText() + '\v' +
                          this->ui->item_update_edit->text() + '\v' +
                          this->ui->number_update_edit->text();

        is_work = connection.Send(message);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result != "\x18";

            if (is_work)
            {
                this->case_code = "";
                this->case_rig = "";
                this->case_item = "";
                this->case_number = "";
                this->case_status = "";
            }
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void StorageWindow::ChooseCaseUpdatePage()
{
    this->ui->new_code_update_edit->setVisible(false);
    this->ui->new_rig_update_box->setVisible(false);
    this->ui->new_item_update_edit->setVisible(false);
    this->ui->new_number_update_edit->setVisible(false);
    this->ui->country_update_edit->setVisible(false);
    this->ui->size_update_box->setVisible(false);
    this->ui->case_type_update_box->setVisible(false);
    this->ui->gross_update_spin->setVisible(false);
    this->ui->tare_weight_update_spin->setVisible(false);
    this->ui->carrying_update_spin->setVisible(false);
    this->ui->capacity_update_spin->setVisible(false);

    this->ui->new_code_update_note_label->setVisible(false);
    this->ui->new_rig_update_note_label->setVisible(false);
    this->ui->new_item_update_note_label->setVisible(false);
    this->ui->new_number_update_note_label->setVisible(false);
    this->ui->country_update_note_label->setVisible(false);
    this->ui->size_update_note_label->setVisible(false);
    this->ui->case_type_update_note_label->setVisible(false);
    this->ui->gross_update_note_label->setVisible(false);
    this->ui->tare_weight_update_note_label->setVisible(false);
    this->ui->carrying_update_note_label->setVisible(false);
    this->ui->capacity_update_note_label->setVisible(false);

    this->ui->new_code_update_label->setVisible(false);
    this->ui->new_rig_update_label->setVisible(false);
    this->ui->new_item_update_label->setVisible(false);
    this->ui->new_number_update_label->setVisible(false);
    this->ui->country_update_label->setVisible(false);
    this->ui->size_update_label->setVisible(false);
    this->ui->case_type_update_label->setVisible(false);
    this->ui->gross_update_label->setVisible(false);
    this->ui->tare_weight_update_label->setVisible(false);
    this->ui->carrying_update_label->setVisible(false);
    this->ui->capacity_update_label->setVisible(false);

    if (this->case_update_page == 1)
    {
        this->ui->new_code_update_edit->setVisible(true);
        this->ui->new_rig_update_box->setVisible(true);
        this->ui->new_item_update_edit->setVisible(true);
        this->ui->new_number_update_edit->setVisible(true);

        this->ui->new_code_update_note_label->setVisible(true);
        this->ui->new_rig_update_note_label->setVisible(true);
        this->ui->new_item_update_note_label->setVisible(true);
        this->ui->new_number_update_note_label->setVisible(true);

        this->ui->new_code_update_label->setVisible(true);
        this->ui->new_rig_update_label->setVisible(true);
        this->ui->new_item_update_label->setVisible(true);
        this->ui->new_number_update_label->setVisible(true);
    }
    else if (this->case_update_page == 2)
    {
        this->ui->country_update_edit->setVisible(true);
        this->ui->size_update_box->setVisible(true);
        this->ui->case_type_update_box->setVisible(true);
        this->ui->gross_update_spin->setVisible(true);

        this->ui->country_update_note_label->setVisible(true);
        this->ui->size_update_note_label->setVisible(true);
        this->ui->case_type_update_note_label->setVisible(true);
        this->ui->gross_update_note_label->setVisible(true);

        this->ui->country_update_label->setVisible(true);
        this->ui->size_update_label->setVisible(true);
        this->ui->case_type_update_label->setVisible(true);
        this->ui->gross_update_label->setVisible(true);
    }
    else if (this->case_update_page == 3)
    {
        this->ui->tare_weight_update_spin->setVisible(true);
        this->ui->carrying_update_spin->setVisible(true);
        this->ui->capacity_update_spin->setVisible(true);

        this->ui->tare_weight_update_note_label->setVisible(true);
        this->ui->carrying_update_note_label->setVisible(true);
        this->ui->capacity_update_note_label->setVisible(true);

        this->ui->tare_weight_update_label->setVisible(true);
        this->ui->carrying_update_label->setVisible(true);
        this->ui->capacity_update_label->setVisible(true);
    }

    if (this->case_update_page == 1)
        this->ui->case_update_left_button->setEnabled(false);
    else
        this->ui->case_update_left_button->setEnabled(true);

    if (this->case_update_page == 3)
        this->ui->case_update_right_button->setEnabled(false);
    else
        this->ui->case_update_right_button->setEnabled(true);

    this->ui->case_update_page_label->setText("Страница " + QString::number(this->case_update_page) + " из 3");

    this->ui->scrollArea_6->widget()->adjustSize();
    this->ui->scrollArea_6->widget()->updateGeometry();
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

    this->case_update_page = 1;

    ChooseCaseUpdatePage();

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

    this->ui->case_update_right_button->setEnabled(flag);

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
    // Флаги проверок
    bool is_code = this->ui->code_delete_edit->text().length() == 3;
    bool is_item = this->ui->item_delete_edit->text().length() == 6;
    bool is_number = this->ui->number_delete_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
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
            QString message = "D20" +
                              this->ui->code_delete_edit->text() + '\v' +
                              this->ui->rig_delete_box->currentText() + '\v' +
                              this->ui->item_delete_edit->text() + '\v' +
                              this->ui->number_delete_edit->text();

            is_work = connection.Send(message);

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

void StorageWindow::DeleteCaseByBid()
{
    // Флаги проверок
    bool is_correct = this->ui->bid_id_delete_edit->text().length() == 14;
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
            QString message = "D21" +
                              this->ui->bid_id_delete_edit->text();

            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();
                qDebug() << result;

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

void StorageWindow::closeEvent(QCloseEvent* event)
{
    this->ui->bid_id_work_edit->clear();

    this->ui->code_update_edit->clear();

    QCoreApplication::processEvents();

    event->accept();
}

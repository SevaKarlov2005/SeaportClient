#include "planningwindow.h"
#include "ui_planningwindow.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QPainter>

PlanningWindow::PlanningWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::PlanningWindow;
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

    // Инициализация таблицы морских судов
    this->ship_page = 1;

    this->ship_model = new QStandardItemModel(0, 3);
    this->ship_model->setHeaderData(0, Qt::Horizontal, "IMO номер судна");
    this->ship_model->setHeaderData(1, Qt::Horizontal, "Название судна");
    this->ship_model->setHeaderData(2, Qt::Horizontal, "Статус");
    this->ui->ship_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->ship_table->setModel(this->ship_model);

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

    // Установка связей между сигналами и методами для пагинации контейнеров
    connect(this->ui->code_filter_edit, &QLineEdit::textChanged, this, &PlanningWindow::CaseList);
    connect(this->ui->rig_filter_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CaseList);
    connect(this->ui->item_filter_edit, &QLineEdit::textChanged, this, &PlanningWindow::CaseList);
    connect(this->ui->number_filter_edit, &QLineEdit::textChanged, this, &PlanningWindow::CaseList);
    connect(this->ui->case_status_filter_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::CaseList);
    connect(this->ui->case_left_button, &QPushButton::clicked, this, [this](){ this->case_page--; CaseList(); });
    connect(this->ui->case_right_button, &QPushButton::clicked, this, [this](){ this->case_page++; CaseList(); });
    connect(this->ui->case_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &PlanningWindow::CaseList);

    // Установка связей между сигналами и методами для пагинации морских судов
    connect(this->ui->IMO_filter_edit, &QLineEdit::textChanged, this, &PlanningWindow::ShipList);
    connect(this->ui->ship_name_filter_edit, &QLineEdit::textChanged, this, &PlanningWindow::ShipList);
    connect(this->ui->ship_status_filter_box, &QComboBox::currentIndexChanged, this, &PlanningWindow::ShipList);
    connect(this->ui->ship_left_button, &QPushButton::clicked, this, [this](){ this->ship_page--; ShipList(); });
    connect(this->ui->ship_right_button, &QPushButton::clicked, this, [this](){ this->ship_page++; ShipList(); });
    connect(this->ui->ship_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &PlanningWindow::ShipList);

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

    // Заполнение таблиц
    CaseList();
    ShipList();
}

PlanningWindow::~PlanningWindow()
{
    this->connection.Disconnect();
    delete this->ui;
}

void PlanningWindow::CheckCaseOptionsWork()
{
    // Флаги проверок
    bool is_work = true;

    // Результат работы сервера
    QString result;

    if (this->case_code.length() == 3)
    {


        is_work = this->connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P00"+
                              this->case_status + '\v' +
                              this->case_code + '\v' +
                              this->case_rig + '\v' +
                              this->case_item + '\v' +
                              this->case_number;

            is_work = this->connection.Send(message);

            if (is_work)
            {
                result = this->connection.Receive();

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
            if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                this->connection.Disconnect();
        }
    }

    ClearCaseWorkForm(0x7);
    ActivateCaseWorkForm(false, 0x7);

    this->ui->case_choose_work_label->clear();
}

void PlanningWindow::FindCaseWork()
{
    // Флаги проверок
    bool is_code = this->ui->code_work_edit->text().length() == 3;
    bool is_item = this->ui->item_work_edit->text().length() == 6;
    bool is_number = this->ui->number_work_edit->text().length() == 1;
    bool is_correct = is_code && is_item && is_number;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {


        is_work = this->connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P01" +
                              this->username + '\v' +
                              this->ui->code_work_edit->text() + '\v' +
                              this->ui->rig_work_box->currentText() + '\v' +
                              this->ui->item_work_edit->text() + '\v' +
                              this->ui->number_work_edit->text();

            is_work = this->connection.Send(message);

            if (is_work)
            {
                result = this->connection.Receive();

                is_work = result != "\x18";
                is_find = result != "\x00";
                is_busy = result == "\x1A";
            }

            // Удаляем соединение
            if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                this->connection.Disconnect();
        }
    }

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

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find && !is_busy)
            {
                this->case_status = result;
                this->case_code = this->ui->code_work_edit->text();
                this->case_rig = this->ui->rig_work_box->currentText();
                this->case_item = this->ui->item_work_edit->text();
                this->case_number = this->ui->number_work_edit->text();
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

void PlanningWindow::SuggestPlan()
{
    ClearCaseWorkForm(0x6);
    ActivateCaseWorkForm(false, 0x6);

    bool is_work = true;
    bool is_find = true;

    QString result;

    is_work = this->connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "P02" +
                          this->case_code + '\v' +
                          this->case_rig + '\v' +
                          this->case_item + '\v' +
                          this->case_number + '\v' +
                          this->username;

        is_work = this->connection.Send(message);

        if (is_work)
        {
            result = this->connection.Receive();

            is_work = result != "\x18";
            is_find = result != "\x00";
        }

        // Удаляем соединение
        if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            this->connection.Disconnect();
    }

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

    if (is_work)
    {
        QStringList list = result.split('\v');

        this->ui->ship_country_edit->setText(list[0]);
        this->ui->designated_ship_edit->setText(list[1]);
        this->ui->designated_position_edit->setText(list[2]);

        QPixmap pixmap(980, 1400);
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);

        QStringList occupied = list.sliced(3);

        if (occupied.length() > 0)
            this->ship_status = "Погрузка";
        else
            this->ship_status = "Свободно";

        QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        int cell_size = 50;
        int x = 240;
        int y = 50;

        painter.setPen(QPen(Qt::gray, 1));

        for (int row = 0; row < 26; row++)
        {
            for (int col = 0; col < 10; col++)
            {
                QRect cell(x + col * cell_size,
                           y + row * cell_size,
                           cell_size - 2, cell_size - 2);

                QString pos = alphabet[row] + QString::number(col).rightJustified(2, '0');

                if (occupied.contains(pos))
                    painter.fillRect(cell, QColor(255, 100, 100));

                painter.setPen(QPen(Qt::gray, 1));
                painter.drawRect(cell);
                painter.setPen(Qt::black);
                painter.drawText(cell, Qt::AlignCenter, pos);
                painter.setPen(QPen(Qt::gray, 1));
            }
        }

        this->ui->schema_label->setPixmap(pixmap);
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

void PlanningWindow::CheckPlan()
{
    bool is_work = true;
    bool is_right = true;

    // Результат работы сервера
    QString result;



    is_work = this->connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "P03" +
                          this->case_code + '\v' +
                          this->case_rig + '\v' +
                          this->case_item + '\v' +
                          this->case_number + '\v' +
                          this->ui->designated_ship_edit->text() + '\v' +
                          this->ui->designated_position_edit->text();

        is_work = this->connection.Send(message);

        if (is_work)
        {
            result = this->connection.Receive();

            is_work = result != "\x18";
            is_right = result == "1";
        }

        // Удаляем соединение
        if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            this->connection.Disconnect();
    }

    // Проверка позиции
    if (!is_right && result == "2")
    {
        this->ui->designated_position_note_label->setStyleSheet("color: #F5F116;");
        this->ui->designated_position_note_label->setText("* Место занято");
        this->ui->designated_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->designated_position_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->designated_position_note_label->clear();
        this->ui->designated_position_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void PlanningWindow::Reception()
{
    // Флаги проверок
    bool is_work = true;

    //
    QString result;

    is_work = this->connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "P04" +
                          this->case_code + '\v' +
                          this->case_rig + '\v' +
                          this->case_item + '\v' +
                          this->case_number + '\v' +
                          this->ui->designated_ship_edit->text() + '\v' +
                          this->ui->designated_position_edit->text();

        is_work = this->connection.Send(message);

        if (is_work)
        {
            result = this->connection.Receive();

            is_work = result != "\x18";

            if (is_work)
            {
                this->case_code = "";
                this->case_rig = "";
                this->case_item = "";
                this->case_number = "";
                this->case_status = "";
                this->ship_status = "Погрузка";
            }
        }

        // Удаляем соединение
        if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            this->connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
    }
}

void PlanningWindow::ClearCaseWorkForm(unsigned short mod)
{
    // Очистка предоставления плана
    if ((mod & 0x1) == 0x1)
        this->ui->plan_suggest_work_label->clear();

    // Очистка проверки плана
    if ((mod & 0x2) == 0x2)
    {
        if (this->ui->designated_ship_edit->text().length() > 0)
        {
            bool is_work = true;
            QString result;


            is_work = this->connection.Connect(this->host, 8081);

            if (is_work)
            {
                QString message = "P05" +
                                  this->ship_status + '\v' +
                                  this->ui->designated_ship_edit->text();

                is_work = this->connection.Send(message);

                if (is_work)
                {
                    result = this->connection.Receive();

                    is_work = result != "\x18";
                }

                // Удаляем соединение
                if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                    this->connection.Disconnect();
            }
        }

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
    bool is_correct = this->ui->new_ship_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;
    bool is_wrong = false;

    QString result;

    if (is_correct)
    {


        is_work = this->connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P06" +
                              this->case_code + '\v' +
                              this->case_rig + '\v' +
                              this->case_item + '\v' +
                              this->case_number + '\v' +
                              this->ui->new_ship_edit->text() + '\v' +
                              this->ui->designated_ship_edit->text() + '\v' +
                              this->ship_status + '\v' +
                              this->username + '\v' +
                              this->ui->ship_country_edit->text();

            is_work = this->connection.Send(message);

            if (is_work)
            {
                result = this->connection.Receive();

                is_work = result != "\x18";
                is_find = result != "\x00";
                is_busy = result == "\x1A";
                is_wrong = result == "2";
            }

            // Удаляем соединение
            if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                this->connection.Disconnect();
        }
    }

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
                if (is_wrong)
                {
                    this->ui->new_ship_choose_label->setStyleSheet("color: #F5F116;");
                    this->ui->new_ship_choose_label->setText("* Несоответствие типа морского судна или страны");
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

    if (is_correct)
    {
        if (is_work)
        {
            if (is_find && !is_busy && !is_wrong)
            {
                this->ui->designated_ship_edit->setText(this->ui->new_ship_edit->text());

                QPixmap pixmap(980, 1400);
                pixmap.fill(Qt::white);

                QPainter painter(&pixmap);

                QStringList occupied = result.split('\v');

                if (occupied.length() > 0)
                    this->ship_status = "Погрузка";
                else
                    this->ship_status = "Свободно";

                QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

                int cell_size = 50;
                int x = 240;
                int y = 50;

                painter.setPen(QPen(Qt::gray, 1));

                for (int row = 0; row < 26; row++)
                {
                    for (int col = 0; col < 10; col++)
                    {
                        QRect cell(x + col * cell_size,
                                   y + row * cell_size,
                                   cell_size - 2, cell_size - 2);

                        QString pos = alphabet[row] + QString::number(col).rightJustified(2, '0');

                        if (occupied.contains(pos))
                            painter.fillRect(cell, QColor(255, 100, 100));

                        painter.setPen(QPen(Qt::gray, 1));
                        painter.drawRect(cell);
                        painter.setPen(Qt::black);
                        painter.drawText(cell, Qt::AlignCenter, pos);
                        painter.setPen(QPen(Qt::gray, 1));
                    }
                }

                this->ui->schema_label->setPixmap(pixmap);
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

void PlanningWindow::AssignPosition()
{
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

        this->ui->designated_position_edit->setText(this->ui->new_position_edit->text());

        this->ui->new_position_choose_label->setStyleSheet("color: #00FF00;");
        this->ui->new_position_choose_label->setText("* Позиция назначена");
    }
}

void PlanningWindow::CaseList()
{
    if ((this->ui->code_filter_edit->text().length() == 3 || this->ui->code_filter_edit->text() == "") &&
        (this->ui->item_filter_edit->text().length() == 6 || this->ui->item_filter_edit->text() == "") &&
        (this->ui->number_filter_edit->text().length() == 1 || this->ui->number_filter_edit->text() == ""))
    {
        QString message = "P07";

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


        is_work = this->connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = this->connection.Send(message);

            if (is_work)
            {
                result = this->connection.Receive();

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
            if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                this->connection.Disconnect();

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

void PlanningWindow::ShipList()
{
    if ((this->ui->IMO_filter_edit->text().length() == 7 || this->ui->IMO_filter_edit->text() == "") &&
        (this->ui->ship_name_filter_edit->text().length() > 0 || this->ui->ship_name_filter_edit->text() == ""))
    {
        QString message = "P08";

        int section =  this->ui->ship_table->horizontalHeader()->sortIndicatorSection();
        Qt::SortOrder order = this->ui->ship_table->horizontalHeader()->sortIndicatorOrder();

        if (section == 0)
            message += "s.IMO_number";
        else if (section == 1)
            message += "s.ship_name";
        else if (section == 2)
            message += "st.ship_status";

        if (order == Qt::AscendingOrder)
            message += "\vASC";
        else
            message += "\vDESC";

        message += ('\v' +QString::number(this->ship_page));

        message += ("\v11");

        if (this->ui->IMO_filter_edit->text().length() == 7)
            message += ('\v' + this->ui->IMO_filter_edit->text());
        else
            message += '\v';

        if (this->ui->ship_name_filter_edit->text().length() > 0)
            message += ('\v' + this->ui->ship_name_filter_edit->text());
        else
            message += '\v';

        message += ('\v' + this->ui->ship_status_filter_box->currentText());

        bool is_work = true;
        bool is_find = true;
        QString result;


        is_work = this->connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = this->connection.Send(message);

            if (is_work)
            {
                result = this->connection.Receive();

                is_find = result != "\x00";
                is_work = result != "\x18";

                if (is_work && is_find)
                {
                    QStringList fields = result.split('\v');

                    this->ship_page = fields[fields.length() - 2].toInt();

                    if (this->ship_page == 1)
                        this->ui->ship_left_button->setEnabled(false);
                    else
                        this->ui->ship_left_button->setEnabled(true);

                    if (fields[fields.length() - 1] == "1")
                        this->ui->ship_right_button->setEnabled(true);
                    else
                        this->ui->ship_right_button->setEnabled(false);

                    this->ship_model->removeRows(0, this->ship_model->rowCount());

                    for (int i = 0; i < (fields.length() - 2); i += 3)
                    {
                        this->ship_model->insertRow(this->ship_model->rowCount());

                        this->ship_model->setData(this->ship_model->index(i / 3, 0), fields[i]);
                        this->ship_model->setData(this->ship_model->index(i / 3, 1), fields[i + 1]);
                        this->ship_model->setData(this->ship_model->index(i / 3, 2), fields[i + 2]);
                    }

                    this->ui->ship_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                }
            }

            // Удаляем соединение
            if (this->connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                this->connection.Disconnect();

            if (!is_work || !is_find)
            {
                this->ui->ship_left_button->setEnabled(false);
                this->ui->ship_right_button->setEnabled(false);

                this->ship_model->removeRows(0, this->ship_model->rowCount());
                this->ui->ship_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                this->ship_page = 1;
            }
        }
    }
    else
    {
        this->ui->ship_left_button->setEnabled(false);
        this->ui->ship_right_button->setEnabled(false);

        this->ship_model->removeRows(0, this->ship_model->rowCount());
        this->ui->ship_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->ship_page = 1;
    }
}

void PlanningWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void PlanningWindow::FindCaseRead()
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
            is_work = connection.Send("P09" + this->ui->code_read_edit->text() + '\v' +
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
    // Флаги проверок
    bool is_correct = this->ui->ship_IMO_read_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;

    // Результат работы сервера
    QString result;

    if (is_correct)
    {

        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            is_work = connection.Send("P10" + this->ui->ship_IMO_read_edit->text());

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

    if(is_correct)
    {
        if (is_work)
        {
            if (is_find)
            {
                QStringList list = result.split('\v');

                this->ui->ship_type_read_edit->setText(list[2]);
                this->ui->ship_name_read_edit->setText(list[3]);
                this->ui->ship_country_read_edit->setText(list[4]);
                this->ui->ship_carrying_read_spin->setValue(list[6].toDouble());
                this->ui->workload_read_spin->setValue(list[7].toDouble());
                this->ui->ship_status_read_edit->setText(list[5]);
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
    bool is_correct = is_IMO_full && is_IMO && is_ship_name && is_country && is_carrying && is_workload;
    bool is_work = true;

    //
    QString result_work;

    if (is_correct)
    {
        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P11" +
                              this->ui->ship_IMO_add_edit->text();

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

void PlanningWindow::AddShip()
{
    // Флаги проверок
    bool is_work = true;

    //
    QString result;

    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "P12" +
                          this->ui->ship_IMO_add_edit->text() + '\v' +
                          this->ui->ship_type_add_box->currentText() + '\v' +
                          this->ui->ship_name_add_edit->text() + '\v' +
                          this->ui->ship_country_add_edit->text() + '\v' +
                          "Свободно\v" +
                          QString::number(this->ui->ship_carrying_add_spin->value()) + '\v' +
                          QString::number(this->ui->workload_add_spin->value());

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
        this->ui->space_4_label->setStyleSheet("color: #F5F116;");
        this->ui->space_4_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        ClearShipAddForm();

        this->ui->space_4_label->setStyleSheet("color: #00FF00;");
        this->ui->space_4_label->setText("* Морское судно добавлено");
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
    // Флаги проверок
    bool is_work = true;

    //
    QString result;

    if (this->ship_update_imo.length() == 7)
    {
        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P05" +
                              this->ship_update_status + '\v' +
                              this->ship_update_imo;

            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";

                if (is_work)
                {
                    this->ship_update_imo = "";
                    this->ship_update_status = "";
                }
            }

            // Удаляем соединение
            if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
                connection.Disconnect();
        }
    }

    ClearShipUpdateForm();
    ActivateShipUpdateForm(false);

    this->ui->ship_choose_update_label->clear();
    this->ui->ship_check_update_button->setEnabled(false);
}

void PlanningWindow::FindShipUpdate()
{
    // Флаги проверок
    bool is_correct = this->ui->ship_IMO_update_edit->text().length() == 7;
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
            QString message = "P13" +
                              this->username + '\v' +
                              this->ui->ship_IMO_update_edit->text();

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

    if (is_correct)
    {
        if(is_work)
        {
            if(is_find && !is_busy)
            {
                QStringList list = result.split('\v');

                this->ship_update_imo = this->ui->ship_IMO_update_edit->text();
                this->ship_update_status = list[5];

                this->ui->new_IMO_update_edit->setText(list[1]);
                this->ui->ship_type_update_box->setCurrentText(list[2]);
                this->ui->ship_name_update_edit->setText(list[3]);
                this->ui->ship_country_update_edit->setText(list[4]);
                this->ui->ship_carrying_update_spin->setValue(list[6].toDouble());
                this->ui->workload_update_spin->setValue(list[7].toDouble());

                this->ui->ship_status_update_box->clear();

                if (list[5] == "Свободно")
                {
                    this->ui->ship_status_update_box->addItem("Свободно");
                    this->ui->ship_status_update_box->addItem("Уплыло");
                }
                else if (list[5] == "Погрузка")
                {
                    this->ui->ship_status_update_box->addItem("Погрузка");
                    this->ui->ship_status_update_box->addItem("Уплыло");

                    ActivateShipUpdateForm(false);

                    this->ui->ship_status_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
                    this->ui->ship_status_update_box->setEnabled(true);
                }

                this->ui->ship_status_update_box->setCurrentText(list[5]);
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

void PlanningWindow::CheckShipUpdateForm()
{
    this->ui->space_5_label->clear();
    this->ui->ship_update_button->setEnabled(false);
}

void PlanningWindow::CheckShipUpdateContents()
{
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
    bool is_correct = is_IMO_full && is_IMO && is_ship_name && is_country && is_carrying && is_workload;
    bool is_work = true;

    QString result_work;

    if (is_correct)
    {
        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P14" +
                              this->ui->new_IMO_update_edit->text() + '\v' +
                              this->ui->ship_IMO_update_edit->text();

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

    // Проверка IMO номера
    if (!is_IMO_full)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* Длина меньше 7 символов");

        if (this->ui->new_IMO_update_edit->isEnabled())
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        else
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red;");
    }
    else if (!is_IMO)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* Неправильный IMO номер");

        if (this->ui->new_IMO_update_edit->isEnabled())
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        else
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red;");
    }
    else if (is_find)
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_IMO_update_note_label->setText("* IMO номер не уникален");

        if (this->ui->new_IMO_update_edit->isEnabled())
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        else
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red;");
    }
    else
    {
        this->ui->new_IMO_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_IMO_update_note_label->setText("* Обязательно для заполнения");

        if (this->ui->new_IMO_update_edit->isEnabled())
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        else
            this->ui->new_IMO_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; color: #000000;");
    }

    // Проверка названия судна
    if (!is_ship_name)
    {
        this->ui->ship_name_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_name_update_note_label->setText("* Длина равна нулю");

        if (this->ui->ship_name_update_edit->isEnabled())
            this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        else
            this->ui->ship_name_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_name_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_name_update_note_label->setText("* Обязательно для заполнения");

        if (this->ui->ship_name_update_edit->isEnabled())
            this->ui->ship_name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        else
            this->ui->ship_name_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
    }

    // Проверка страны
    if (!is_country)
    {
        this->ui->ship_country_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_country_update_note_label->setText("* Длина равна нулю");

        if (this->ui->ship_country_update_edit->isEnabled())
            this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        else
            this->ui->ship_country_update_edit->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red;");
    }
    else
    {
        this->ui->ship_country_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_country_update_note_label->setText("* Обязательно для заполнения");

        if (this->ui->ship_country_update_edit->isEnabled())
            this->ui->ship_country_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        else
            this->ui->ship_country_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
    }

    // Проверка грузоподъёмности
    if (!is_carrying)
    {
        this->ui->ship_carrying_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->ship_carrying_update_note_label->setText("* Грузоподъёмность равна нулю");

        if (this->ui->ship_carrying_update_spin->isEnabled())
            this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        else
            this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->ship_carrying_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->ship_carrying_update_note_label->setText("* Обязательно для заполнения");

        if (this->ui->ship_carrying_update_spin->isEnabled())
            this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        else
            this->ui->ship_carrying_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
    }

    // Проверка загруженности
    if (!is_workload)
    {
        this->ui->workload_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->workload_update_note_label->setText("* Загруженность больше грузоподъёмности");

        if (this->ui->workload_update_spin->isEnabled())
            this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        else
            this->ui->workload_update_spin->setStyleSheet("background-color: #BBBBBB; color: black; border: 5px solid red; padding: 1px 18px 1px 4px;");
    }
    else
    {
        this->ui->workload_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->workload_update_note_label->setText("* Обязательно для заполнения");

        if (this->ui->workload_update_spin->isEnabled())
            this->ui->workload_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        else
            this->ui->workload_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
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

void PlanningWindow::UpdateShip()
{
    // Флаги проверок
    bool is_work = true;

    //
    QString result;

    is_work = connection.Connect(this->host, 8081);

    if (is_work)
    {
        QString message = "P15" +
                          this->ui->ship_status_update_box->currentText() + '\v' +
                          this->ui->new_IMO_update_edit->text() + '\v' +
                          this->ui->ship_type_update_box->currentText() + '\v' +
                          this->ui->ship_name_update_edit->text() + '\v' +
                          this->ui->ship_country_update_edit->text() + '\v' +
                          this->ui->ship_status_update_box->currentText() + '\v' +
                          QString::number(this->ui->ship_carrying_update_spin->value()) + '\v' +
                          QString::number(this->ui->workload_update_spin->value()) + '\v' +
                          this->ui->ship_IMO_update_edit->text();

        is_work = connection.Send(message);

        if (is_work)
        {
            result = connection.Receive();

            is_work = result != "\x18";

            if (is_work)
            {
                this->ship_update_imo = "";
                this->ship_update_status = "";
            }
        }

        // Удаляем соединение
        if (connection.CheckConnectionState() == QAbstractSocket::ConnectedState)
            connection.Disconnect();
    }

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

    if (!is_work)
    {
        QMessageBox box;

        box.setIcon(QMessageBox::Critical);
        box.setWindowTitle("Ошибка");
        box.setText("Произошёл сбой на сервере. Свяжитесь с технической поддержкой для устранения неполадки.");

        box.exec();
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
    // Флаги проверок
    bool is_correct = this->ui->IMO_delete_edit->text().length() == 7;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    //
    QString result;

    if (is_correct)
    {
        is_work = connection.Connect(this->host, 8081);

        if (is_work)
        {
            QString message = "P16" +
                              this->ui->IMO_delete_edit->text();

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

void PlanningWindow::closeEvent(QCloseEvent* event)
{
    this->ui->code_work_edit->clear();

    this->ui->ship_IMO_update_edit->clear();

    QCoreApplication::processEvents();

    event->accept();
}

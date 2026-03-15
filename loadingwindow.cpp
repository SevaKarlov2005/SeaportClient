#include "loadingwindow.h"
#include "ui_loadingwindow.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QPainter>

LoadingWindow::LoadingWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::LoadingWindow;
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

    // Установка страниц форм
    this->bid_read_page = 1;
    this->case_read_page = 1;

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

    // Установка связей между сигналами и методами для пагинации контейнеров
    connect(this->ui->code_filter_edit, &QLineEdit::textChanged, this, &LoadingWindow::CaseList);
    connect(this->ui->rig_filter_box, &QComboBox::currentIndexChanged, this, &LoadingWindow::CaseList);
    connect(this->ui->item_filter_edit, &QLineEdit::textChanged, this, &LoadingWindow::CaseList);
    connect(this->ui->number_filter_edit, &QLineEdit::textChanged, this, &LoadingWindow::CaseList);
    connect(this->ui->status_filter_box, &QComboBox::currentIndexChanged, this, &LoadingWindow::CaseList);
    connect(this->ui->left_button, &QPushButton::clicked, this, [this](){ this->case_page--; CaseList(); });
    connect(this->ui->right_button, &QPushButton::clicked, this, [this](){ this->case_page++; CaseList(); });
    connect(this->ui->case_table->horizontalHeader(), &QHeaderView::sortIndicatorChanged, this, &LoadingWindow::CaseList);

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &LoadingWindow::FindCaseRead);

    // Пагинация формы просмотра контейнера
    connect(this->ui->case_read_left_button, &QPushButton::clicked, this, [this](){ this->case_read_page--; ChooseCaseReadPage(); });
    connect(this->ui->case_read_right_button, &QPushButton::clicked, this, [this](){ this->case_read_page++; ChooseCaseReadPage(); });

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &LoadingWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &LoadingWindow::FindBidRead);

    // Пагинация формы просмотра заявки
    connect(this->ui->bid_read_left_button, &QPushButton::clicked, this, [this](){ this->bid_read_page--; ChooseBidReadPage(); });
    connect(this->ui->bid_read_right_button, &QPushButton::clicked, this, [this](){ this->bid_read_page++; ChooseBidReadPage(); });

    // Заполнение таблиц
    CaseList();

    ChooseBidReadPage();
    ChooseCaseReadPage();
}

LoadingWindow::~LoadingWindow()
{
    this->connection.Disconnect();
    delete this->ui;
}

void LoadingWindow::CheckCaseOptionsWork()
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
            QString message = "L00"+
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

void LoadingWindow::FindCaseWork()
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
            QString message = "L01" +
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
                ActivateCaseWorkForm(true, 0x5);

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
                QStringList list = result.split('\v');

                this->case_status = list[13];
                this->case_code = this->ui->code_work_edit->text();
                this->case_rig = this->ui->rig_work_box->currentText();
                this->case_item = this->ui->item_work_edit->text();
                this->case_number = this->ui->number_work_edit->text();

                this->ui->designated_position_edit->setText(list[12]);
                this->ui->designated_ship_edit->setText(list[14]);

                QPixmap pixmap(980, 1400);
                pixmap.fill(Qt::white);

                QPainter painter(&pixmap);

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

                        if (pos == this->ui->designated_position_edit->text())
                            painter.fillRect(cell, QColor(144, 238, 144));

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

    //
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
            QString message = "L02" +
                              comment + '\v' +
                              (this->ui->check_true_radio->isChecked() ? "Погружен" : "Не погружен") + '\v' +
                              this->case_code + '\v' +
                              this->case_rig + '\v' +
                              this->case_item + '\v' +
                              this->case_number;

            is_work = connection.Send(message);

            if (is_work)
            {
                result = connection.Receive();

                is_work = result != "\x18";

                if (result == "1")
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

void LoadingWindow::CaseList()
{
    if ((this->ui->code_filter_edit->text().length() == 3 || this->ui->code_filter_edit->text() == "") &&
        (this->ui->item_filter_edit->text().length() == 6 || this->ui->item_filter_edit->text() == "") &&
        (this->ui->number_filter_edit->text().length() == 1 || this->ui->number_filter_edit->text() == ""))
    {
        QString message = "L03";

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

        message += ('\v' + this->ui->status_filter_box->currentText());

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
                        this->ui->left_button->setEnabled(false);
                    else
                        this->ui->left_button->setEnabled(true);

                    if (fields[fields.length() - 1] == "1")
                        this->ui->right_button->setEnabled(true);
                    else
                        this->ui->right_button->setEnabled(false);

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
                this->ui->left_button->setEnabled(false);
                this->ui->right_button->setEnabled(false);

                this->case_model->removeRows(0, this->case_model->rowCount());
                this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                this->case_page = 1;
            }
        }
    }
    else
    {
        this->ui->left_button->setEnabled(false);
        this->ui->right_button->setEnabled(false);

        this->case_model->removeRows(0, this->case_model->rowCount());
        this->ui->case_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        this->case_page = 1;
    }
}

void LoadingWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void LoadingWindow::FindCaseRead()
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
            is_work = connection.Send("L04" + this->ui->code_read_edit->text() + '\v' +
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

void LoadingWindow::ChooseCaseReadPage()
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

    this->case_read_page = 1;

    ChooseCaseReadPage();
}

void LoadingWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void LoadingWindow::FindBidRead()
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
            is_work = connection.Send("L05" + this->ui->bid_id_read_edit->text());

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

void LoadingWindow::ChooseBidReadPage()
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

    this->bid_read_page = 1;

    ChooseBidReadPage();
}

void LoadingWindow::closeEvent(QCloseEvent* event)
{
    this->ui->code_work_edit->clear();

    QCoreApplication::processEvents();

    event->accept();
}

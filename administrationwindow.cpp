#include "administrationwindow.h"
#include "ui_administrationwindow.h"

#include <QRegularExpressionValidator>

AdministrationWindow::AdministrationWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::AdministrationWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);

    // Регулярные выражения для валидаторов
    QRegularExpression bid_id_pattern(R"([0-9]{5}-[0-9]{2}/ОМиДР)");
    QRegularExpression organization_pattern(R"([@#\$%\^&\*\(\) _\+\=\{\}\[\]\|\\;:"'<>,\./\?~A-Za-zА-Яа-я\-]+)");
    QRegularExpression INN_pattern(R"([0-9]{10})");
    QRegularExpression phone_pattern(R"(\+[0-9]{11})");
    QRegularExpression mail_pattern(R"([a-z0-9]+@[a-z]+\.[a-z]+)");
    QRegularExpression cargo_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression TNVED_pattern(R"([0-9]{10})");
    QRegularExpression package_pattern(R"([A-Za-zА-Яа-я0-9\- ]+)");
    QRegularExpression producer_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression sender_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression port_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression country_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression receiver_pattern(R"([A-Za-zА-Яа-я0-9\- "]+)");
    QRegularExpression date_pattern(R"((0[1-9]|[12][0-9]|3[01])\.(0[1-9]|1[0-2])\.[0-9]{2})");
    QRegularExpression code_pattern(R"([A-Z]{3})");
    QRegularExpression item_pattern(R"([0-9]{6})");
    QRegularExpression number_pattern(R"([0-9])");
    QRegularExpression IMO_pattern(R"([0-9]{7})");
    QRegularExpression ship_name_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-zА-Яа-я\-]+)");
    QRegularExpression FIO_pattern(R"([А-Яа-яA-Za-z \-]+)");
    QRegularExpression username_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-z\-]{12,16})");
    QRegularExpression password_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-z\-]{12,16})");

    // Установка валидаторов для добавления заявки
    this->ui->organization_add_edit->setValidator(new QRegularExpressionValidator(organization_pattern));
    this->ui->INN_add_edit->setValidator(new QRegularExpressionValidator(INN_pattern));
    this->ui->phone_add_edit->setValidator(new QRegularExpressionValidator(phone_pattern));
    this->ui->mail_add_edit->setValidator(new QRegularExpressionValidator(mail_pattern));
    this->ui->cargo_add_edit->setValidator(new QRegularExpressionValidator(cargo_pattern));
    this->ui->TNVED_add_edit->setValidator(new QRegularExpressionValidator(TNVED_pattern));
    this->ui->package_add_edit->setValidator(new QRegularExpressionValidator(package_pattern));
    this->ui->producer_add_edit->setValidator(new QRegularExpressionValidator(producer_pattern));
    this->ui->sender_add_edit->setValidator(new QRegularExpressionValidator(sender_pattern));
    this->ui->port_from_add_edit->setValidator(new QRegularExpressionValidator(port_pattern));
    this->ui->country_from_add_edit->setValidator(new QRegularExpressionValidator(country_pattern));
    this->ui->port_to_add_edit->setValidator(new QRegularExpressionValidator(port_pattern));
    this->ui->country_to_add_edit->setValidator(new QRegularExpressionValidator(country_pattern));
    this->ui->receiver_add_edit->setValidator(new QRegularExpressionValidator(receiver_pattern));

    // Установка валидаторов для изменения заявки
    this->ui->bid_id_update_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));
    this->ui->organization_update_edit->setValidator(new QRegularExpressionValidator(organization_pattern));
    this->ui->INN_update_edit->setValidator(new QRegularExpressionValidator(INN_pattern));
    this->ui->phone_update_edit->setValidator(new QRegularExpressionValidator(phone_pattern));
    this->ui->mail_update_edit->setValidator(new QRegularExpressionValidator(mail_pattern));
    this->ui->cargo_update_edit->setValidator(new QRegularExpressionValidator(cargo_pattern));
    this->ui->TNVED_update_edit->setValidator(new QRegularExpressionValidator(TNVED_pattern));
    this->ui->package_update_edit->setValidator(new QRegularExpressionValidator(package_pattern));
    this->ui->producer_update_edit->setValidator(new QRegularExpressionValidator(producer_pattern));
    this->ui->sender_update_edit->setValidator(new QRegularExpressionValidator(sender_pattern));
    this->ui->port_from_update_edit->setValidator(new QRegularExpressionValidator(port_pattern));
    this->ui->country_from_update_edit->setValidator(new QRegularExpressionValidator(country_pattern));
    this->ui->port_to_update_edit->setValidator(new QRegularExpressionValidator(port_pattern));
    this->ui->country_to_update_edit->setValidator(new QRegularExpressionValidator(country_pattern));
    this->ui->receiver_update_edit->setValidator(new QRegularExpressionValidator(receiver_pattern));

    // Установка валидатора для удаления заявки
    this->ui->bid_id_delete_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка валидаторов для фильтра заявок
    this->ui->bid_id_filter_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));
    this->ui->bid_date_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));
    this->ui->bid_change_filter_edit->setValidator(new QRegularExpressionValidator(date_pattern));

    // Установка валидаторов для фильтра контейнеров
    this->ui->case_code_filter_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->case_item_filter_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->case_number_filter_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидаторов для фильтра морских судов
    this->ui->ship_IMO_filter_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));
    this->ui->ship_name_filter_edit->setValidator(new QRegularExpressionValidator(ship_name_pattern));

    // Установка валидатора для просмотра заявки
    this->ui->bid_id_read_edit->setValidator(new QRegularExpressionValidator(bid_id_pattern));

    // Установка валидаторов для просмотра контейнера
    this->ui->code_read_edit->setValidator(new QRegularExpressionValidator(code_pattern));
    this->ui->item_read_edit->setValidator(new QRegularExpressionValidator(item_pattern));
    this->ui->number_read_edit->setValidator(new QRegularExpressionValidator(number_pattern));

    // Установка валидатора для просмотра морского судна
    this->ui->ship_IMO_read_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));

    // Установка валидаторов для добавления пользователя
    this->ui->surname_add_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->name_add_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->patronym_add_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->username_add_edit->setValidator(new QRegularExpressionValidator(username_pattern));
    this->ui->password_add_edit->setValidator(new QRegularExpressionValidator(password_pattern));
    this->ui->repeat_add_edit->setValidator(new QRegularExpressionValidator(password_pattern));

    // Установка валидаторов для изменения пользователя
    this->ui->username_update_edit->setValidator(new QRegularExpressionValidator(username_pattern));
    this->ui->password_update_edit->setValidator(new QRegularExpressionValidator(password_pattern));
    this->ui->surname_update_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->name_update_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->patronym_update_edit->setValidator(new QRegularExpressionValidator(FIO_pattern));
    this->ui->new_username_update_edit->setValidator(new QRegularExpressionValidator(username_pattern));
    this->ui->new_password_update_edit->setValidator(new QRegularExpressionValidator(password_pattern));
    this->ui->repeat_update_edit->setValidator(new QRegularExpressionValidator(password_pattern));

    // Установка валидаторов для удаления пользователя
    this->ui->username_delete_edit->setValidator(new QRegularExpressionValidator(username_pattern));
    this->ui->password_delete_edit->setValidator(new QRegularExpressionValidator(password_pattern));

    // Установка связей между сигналами и методами для добавления заявки
    connect(this->ui->organization_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->INN_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->phone_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->mail_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->cargo_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->TNVED_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->direction_add_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->length_add_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->width_add_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->height_add_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->weight_add_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->package_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->feature_add_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->quantity_add_spin, &QSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->traffic_in_add_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->traffic_out_add_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->date_in_add_date, &QDateEdit::dateChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->date_out_add_date, &QDateEdit::dateChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->storage_add_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->term_add_spin, &QSpinBox::valueChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->demand_add_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->producer_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->sender_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->port_from_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->country_from_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->port_to_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->country_to_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->receiver_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->other_add_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidAddForm);
    connect(this->ui->bid_check_add_button, &QPushButton::clicked, this, &AdministrationWindow::CheckBidAddContents);
    connect(this->ui->bid_feasibility_add_button, &QPushButton::clicked, this, &AdministrationWindow::CheckBidAddFeasibility);
    connect(this->ui->bid_add_button, &QPushButton::clicked, this, &AdministrationWindow::AddBid);

    // Установка связей между сигналами и методами для изменения заявки
    connect(this->ui->bid_id_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidIdUpdate);
    connect(this->ui->bid_choose_update_button, &QPushButton::clicked, this, &AdministrationWindow::FindBidUpdate);
    connect(this->ui->organization_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->INN_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->phone_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->mail_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->cargo_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->TNVED_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->direction_update_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->length_update_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->width_update_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->height_update_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->weight_update_spin, &QDoubleSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->package_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->feature_update_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->quantity_update_spin, &QSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->traffic_in_update_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->traffic_out_update_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->date_in_update_date, &QDateEdit::dateChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->date_out_update_date, &QDateEdit::dateChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->storage_update_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->term_update_spin, &QSpinBox::valueChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->demand_update_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->producer_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->sender_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->port_from_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->country_from_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->port_to_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->country_to_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->receiver_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->other_update_edit, &QTextEdit::textChanged, this, &AdministrationWindow::CheckBidUpdateForm);
    connect(this->ui->bid_check_update_button, &QPushButton::clicked, this, &AdministrationWindow::CheckBidUpdateContents);
    connect(this->ui->bid_feasibility_update_button, &QPushButton::clicked, this, &AdministrationWindow::CheckBidUpdateFeasibility);
    connect(this->ui->bid_update_button, &QPushButton::clicked, this, &AdministrationWindow::UpdateBid);

    // Установка связей между сигналами и методами для удаления заявки
    connect(this->ui->bid_id_delete_edit, &QLineEdit::textChanged, this->ui->bid_choose_delete_label, &QLabel::clear);
    connect(this->ui->bid_choose_delete_button, &QPushButton::clicked, this, &AdministrationWindow::DeleteBid);

    // Установка связей между сигналами и методами для просмотра заявки
    connect(this->ui->bid_id_read_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckBidIdRead);
    connect(this->ui->bid_choose_read_button, &QPushButton::clicked, this, &AdministrationWindow::FindBidRead);

    // Установка связей между сигналами и методами для просмотра контейнера
    connect(this->ui->code_read_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckCaseOptionsRead);
    connect(this->ui->rig_read_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckCaseOptionsRead);
    connect(this->ui->item_read_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckCaseOptionsRead);
    connect(this->ui->number_read_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckCaseOptionsRead);
    connect(this->ui->case_choose_read_button, &QPushButton::clicked, this, &AdministrationWindow::FindCaseRead);

    // Установка связей между сигналами и методами для просмотра морского судна
    connect(this->ui->ship_IMO_read_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckIMORead);
    connect(this->ui->ship_choose_read_button, &QPushButton::clicked, this, &AdministrationWindow::FindShipRead);

    // Установка связей между сигналами и методами для добавления пользователя
    connect(this->ui->surname_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->name_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->patronym_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->job_add_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->username_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->password_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->repeat_add_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserAddForm);
    connect(this->ui->user_add_button, &QPushButton::clicked, this, &AdministrationWindow::AddUser);

    // Установка связей между сигналами и методами для изменения пользователя
    connect(this->ui->username_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserOptionsUpdate);
    connect(this->ui->password_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserOptionsUpdate);
    connect(this->ui->user_choose_update_button, &QPushButton::clicked, this, &AdministrationWindow::FindUserUpdate);
    connect(this->ui->surname_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->name_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->patronym_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->job_update_box, &QComboBox::currentIndexChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->new_username_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->new_password_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->repeat_update_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserUpdateForm);
    connect(this->ui->user_update_button, &QPushButton::clicked, this, &AdministrationWindow::UpdateUser);

    // Установка связей между сигналами и методами для удаления пользователя
    connect(this->ui->username_delete_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserOptionsDelete);
    connect(this->ui->password_delete_edit, &QLineEdit::textChanged, this, &AdministrationWindow::CheckUserOptionsDelete);
    connect(this->ui->user_delete_button, &QPushButton::clicked, this, &AdministrationWindow::DeleteUser);
}

AdministrationWindow::~AdministrationWindow()
{
    delete this->ui;
}

void AdministrationWindow::CheckBidAddForm()
{
    // Установка разрешённых символов для характеристик и требований к креплению груза
    QString feature_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789 -";
    QString demand_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                           "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                           "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                           "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    QChar wrong_feature = '-';
    QChar wrong_demand = '-';

    // Получение значений проверяемых полей
    double length = this->ui->length_add_spin->value();
    double width = this->ui->width_add_spin->value();
    double height = this->ui->height_add_spin->value();
    QString feature = this->ui->feature_add_edit->toPlainText();
    QString demand = this->ui->demand_add_edit->toPlainText();

    // Проверка характеристик груза
    for (int i = 0; i < feature.length(); i++)
    {
        if (!feature_grant.contains(feature[i]))
        {
            wrong_feature = feature[i];
            break;
        }
    }

    // Проверка требований груза
    for (int i = 0; i < demand.length(); i++)
    {
        if (!demand_grant.contains(demand[i]))
        {
            wrong_demand = demand[i];
            break;
        }
    }

    // Проверка длины единицы груза
    if (length == 0)
    {
        this->ui->length_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->length_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->length_add_note_label->setText("* Длина единицы груза равна нулю");
    }
    else
    {
        this->ui->length_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->length_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->length_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка ширины единицы груза
    if (width == 0)
    {
        this->ui->width_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->width_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->width_add_note_label->setText("* Ширина единицы груза равна нулю");
    }
    else
    {
        this->ui->width_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->width_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->width_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка высоты единицы груза
    if (height == 0)
    {
        this->ui->height_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->height_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->height_add_note_label->setText("* Высота единицы груза равна нулю");
    }
    else
    {
        this->ui->height_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->height_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->height_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка характеристик груза
    if (wrong_feature != '-')
    {
        this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_add_note_label->setText(QString("* Запрещённый символ ") + wrong_feature);
    }
    else
    {
        this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->feature_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->feature_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка требований груза
    if (wrong_demand != '-')
    {
        int index = demand.indexOf(wrong_demand);
        QTextCursor cursor = this->ui->demand_add_edit->textCursor();

        cursor.setPosition(index);
        cursor.deleteChar();
    }

    // Установка блокировок на кнопки формы
    this->ui->space_1_label->clear();
    this->ui->bid_feasibility_add_button->setEnabled(false);
    this->ui->bid_add_button->setEnabled(false);
}

void AdministrationWindow::CheckBidAddContents()
{
    // Установка разрешённых символов для характеристик и прочей информации к грузу
    QString feature_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789 -";
    QString other_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                           "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                           "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                           "0123456789"
                           "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    bool is_feature_correct = true;
    bool is_other_correct = true;
    bool is_bid_correct = true;

    // Значения строковых полей формы
    QString mail = this->ui->mail_add_edit->text();
    QString feature = this->ui->feature_add_edit->toPlainText();
    QString demand = this->ui->demand_add_edit->toPlainText();
    QString other = this->ui->other_add_edit->toPlainText();

    // Длины значений полей формы
    int organization_length = this->ui->organization_add_edit->text().length();
    int INN_length = this->ui->INN_add_edit->text().length();
    int phone_length = this->ui->phone_add_edit->text().length();
    int mail_length = this->ui->mail_add_edit->text().length();
    int cargo_length = this->ui->cargo_add_edit->text().length();
    int TNVED_length = this->ui->TNVED_add_edit->text().length();
    int package_length = this->ui->package_add_edit->text().length();
    int feature_length = feature.length();
    int demand_length = demand.length();
    int producer_length = this->ui->producer_add_edit->text().length();
    int sender_length = this->ui->sender_add_edit->text().length();
    int port_from_length = this->ui->port_from_add_edit->text().length();
    int country_from_length = this->ui->country_from_add_edit->text().length();
    int port_to_length = this->ui->port_to_add_edit->text().length();
    int country_to_length = this->ui->country_to_add_edit->text().length();
    int receiver_length = this->ui->receiver_add_edit->text().length();

    // Значения числовых и датированных полей формы
    double length = this->ui->length_add_spin->value();
    double width = this->ui->width_add_spin->value();
    double height = this->ui->height_add_spin->value();
    double weight = this->ui->weight_add_spin->value();
    int quantity = this->ui->quantity_add_spin->value();
    int term = this->ui->term_add_spin->value();
    QDate date_in = this->ui->date_in_add_date->date().addYears(100);
    QDate date_out = this->ui->date_out_add_date->date().addYears(100);

    // Проверка характеристик груза
    for (int i = 0; i < feature.length(); i++)
    {
        if (!feature_grant.contains(feature[i]))
        {
            is_feature_correct = false;
            break;
        }
    }

    // Проверка прочей информации о грузе
    for (int i = 0; i < other.length(); i++)
    {
        if (!other_grant.contains(other[i]))
        {
            is_other_correct = false;
            break;
        }
    }

    // Проверка длины наименования организации
    if (organization_length == 0)
    {
        is_bid_correct = false;
        this->ui->organization_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->organization_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->organization_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->organization_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->organization_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->organization_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины ИНН
    if (INN_length == 0)
    {
        is_bid_correct = false;
        this->ui->INN_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->INN_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->INN_add_note_label->setText("* Длина равна нулю");
    }
    else if (INN_length < 10)
    {
        is_bid_correct = false;
        this->ui->INN_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->INN_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->INN_add_note_label->setText("* Длина меньше 10 символов");
    }
    else
    {
        this->ui->INN_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->INN_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->INN_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины номера телефона
    if (phone_length == 0)
    {
        is_bid_correct = false;
        this->ui->phone_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->phone_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->phone_add_note_label->setText("* Длина равна нулю");
    }
    else if (phone_length < 12)
    {
        is_bid_correct = false;
        this->ui->phone_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->phone_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->phone_add_note_label->setText("* Длина меньше 12 символов");
    }
    else
    {
        this->ui->phone_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->phone_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->phone_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка электронной почты
    if (mail_length == 0)
    {
        is_bid_correct = false;
        this->ui->mail_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_add_note_label->setText("* Длина равна нулю");
    }
    else if (!mail.contains('@'))
    {
        is_bid_correct = false;
        this->ui->mail_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_add_note_label->setText("* Отсутствие символа @");
    }
    else if (!mail.contains('.') || (mail.indexOf('.') - mail.indexOf('@') - 1) < 2 || (mail_length - mail.indexOf('.') - 1) < 2)
    {
        is_bid_correct = false;
        this->ui->mail_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_add_note_label->setText("* Неправильный домен");
    }
    else
    {
        this->ui->mail_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->mail_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->mail_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины наименования груза
    if (cargo_length == 0)
    {
        is_bid_correct = false;
        this->ui->cargo_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->cargo_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->cargo_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->cargo_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->cargo_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->cargo_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины кода ТН ВЭД
    if (TNVED_length == 0)
    {
        is_bid_correct = false;
        this->ui->TNVED_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->TNVED_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->TNVED_add_note_label->setText("* Длина равна нулю");
    }
    else if (TNVED_length < 10)
    {
        is_bid_correct = false;
        this->ui->TNVED_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->TNVED_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->TNVED_add_note_label->setText("* Длина меньше 10 символов");
    }
    else
    {
        this->ui->TNVED_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->TNVED_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->TNVED_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины единицы груза
    if (length == 0)
    {
        is_bid_correct = false;
        this->ui->length_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->length_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->length_add_note_label->setText("* Длина единицы груза равна нулю");
    }
    else
    {
        this->ui->length_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->length_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->length_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка ширины единицы груза
    if (width == 0)
    {
        is_bid_correct = false;
        this->ui->width_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->width_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->width_add_note_label->setText("* Ширина единицы груза равна нулю");
    }
    else
    {
        this->ui->width_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->width_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->width_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка высоты единицы груза
    if (height == 0)
    {
        is_bid_correct = false;
        this->ui->height_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->height_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->height_add_note_label->setText("* Высота единицы груза равна нулю");
    }
    else
    {
        this->ui->height_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->height_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->height_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка массы единицы груза
    if (weight == 0)
    {
        is_bid_correct = false;
        this->ui->weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->weight_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->weight_add_note_label->setText("* Масса единицы груза равна нулю");
    }
    else
    {
        this->ui->weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->weight_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->weight_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины наименования упаковки
    if (package_length == 0)
    {
        is_bid_correct = false;
        this->ui->package_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->package_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->package_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->package_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->package_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->package_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка характеристик груза
    if (feature_length == 0)
    {
        is_bid_correct = false;
        this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_add_note_label->setText("* Длина равна нулю");
    }
    else if (!is_feature_correct)
    {
        is_bid_correct = false;
        this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_add_note_label->setText("* Наличие запрещённых символов");
    }
    else
    {
        this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->feature_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->feature_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка количества единиц груза
    if (quantity == 0)
    {
        is_bid_correct = false;
        this->ui->quantity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->quantity_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->quantity_add_note_label->setText("* Количество единиц груза равно нулю");
    }
    else
    {
        this->ui->quantity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->quantity_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->quantity_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка даты завоза груза
    if (date_in < QDate::currentDate())
    {
        is_bid_correct = false;
        this->ui->date_in_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_in_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_in_add_note_label->setText("* Дата уже прошла");
    }
    else
    {
        this->ui->date_in_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_in_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->date_in_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка даты вывоза груза
    if (date_out < QDate::currentDate())
    {
        is_bid_correct = false;
        this->ui->date_out_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_out_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_out_add_note_label->setText("* Дата уже прошла");
    }
    else if (date_out < date_in)
    {
        is_bid_correct = false;
        this->ui->date_out_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_out_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_out_add_note_label->setText("* Дата вывоза меньше даты завоза");
    }
    else
    {
        this->ui->date_out_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_out_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->date_out_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка сроков хранения груза
    if (term == 0)
    {
        is_bid_correct = false;
        this->ui->term_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->term_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->term_add_note_label->setText("* Срок хранения груза равен нулю");
    }
    else
    {
        this->ui->term_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->term_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->term_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка требований к грузу
    if (demand_length == 0)
    {
        is_bid_correct = false;
        this->ui->demand_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->demand_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->demand_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->demand_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->demand_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->demand_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины производителя груза
    if (producer_length == 0)
    {
        is_bid_correct = false;
        this->ui->producer_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->producer_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->producer_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->producer_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->producer_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->producer_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины отправителя груза
    if (sender_length == 0)
    {
        is_bid_correct = false;
        this->ui->sender_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->sender_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->sender_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->sender_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->sender_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->sender_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины порта отправления
    if (port_from_length == 0)
    {
        is_bid_correct = false;
        this->ui->port_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->port_from_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->port_from_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->port_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_from_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->port_from_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины страны отправления
    if (country_from_length == 0)
    {
        is_bid_correct = false;
        this->ui->country_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->country_from_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_from_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->country_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_from_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_from_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины порта прибытия
    if (port_to_length == 0)
    {
        is_bid_correct = false;
        this->ui->port_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->port_to_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->port_to_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->port_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_to_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->port_to_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины страны прибытия
    if (country_to_length == 0)
    {
        is_bid_correct = false;
        this->ui->country_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->country_to_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_to_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->country_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_to_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_to_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины получателя
    if (receiver_length == 0)
    {
        is_bid_correct = false;
        this->ui->receiver_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->receiver_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->receiver_add_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->receiver_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->receiver_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->receiver_add_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка прочей информации о грузе
    if (!is_other_correct)
    {
        is_bid_correct = false;
        this->ui->other_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->other_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->other_add_note_label->setText("* Наличие запрещённых символов");
    }
    else
    {
        this->ui->other_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->other_add_note_label->clear();
    }

    // Проверка корректности заявки
    if (is_bid_correct)
    {
        this->ui->space_1_label->setStyleSheet("color: #00FF00;");
        this->ui->space_1_label->setText("* Проверка содержимого заявки прошла успешно");
        this->ui->bid_feasibility_add_button->setEnabled(true);
    }
    else
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* В содержимом заявки обнаружены ошибки");
    }
}

void AdministrationWindow::CheckBidAddFeasibility()
{
    // TODO проверить наличие контейнеров и морских судов по код ТН ВЭД

    // Заглушка проверки осуществимости
    bool is_work = true;
    bool is_feasibility = true;

    if (!is_work)
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_feasibility)
        {
            this->ui->space_1_label->setStyleSheet("color: #F5F116;");
            this->ui->space_1_label->setText("* Невозможно выполнить заявку. Отсутствуют морские суда или контейнеры");
        }
        else
        {
            this->ui->space_1_label->setStyleSheet("color: #00FF00;");
            this->ui->space_1_label->setText("* Проверка осуществимости прошла успешно");
            this->ui->bid_add_button->setEnabled(true);
        }
    }
}

void AdministrationWindow::AddBid()
{
    // TODO организовать отправку заявки на сервер

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_1_label->setStyleSheet("color: #F5F116;");
        this->ui->space_1_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        ClearBidAddForm();

        this->ui->space_1_label->setStyleSheet("color: #00FF00;");
        this->ui->space_1_label->setText("* Заявка отправлена");
    }
}

void AdministrationWindow::ClearBidAddForm()
{
    // Возвращение начальных значений полей
    this->ui->organization_add_edit->clear();
    this->ui->INN_add_edit->clear();
    this->ui->phone_add_edit->clear();
    this->ui->mail_add_edit->clear();
    this->ui->cargo_add_edit->clear();
    this->ui->feature_add_edit->clear();
    this->ui->TNVED_add_edit->clear();
    this->ui->direction_add_box->setCurrentIndex(0);
    this->ui->length_add_spin->setValue(0);
    this->ui->width_add_spin->setValue(0);
    this->ui->height_add_spin->setValue(0);
    this->ui->weight_add_spin->setValue(0);
    this->ui->package_add_edit->clear();
    this->ui->quantity_add_spin->setValue(0);
    this->ui->traffic_in_add_box->setCurrentIndex(0);
    this->ui->traffic_out_add_box->setCurrentIndex(0);
    this->ui->date_in_add_date->setDate(QDate(1900, 1, 1));
    this->ui->date_out_add_date->setDate(QDate(1900, 1, 1));
    this->ui->storage_add_box->setCurrentIndex(0);
    this->ui->term_add_spin->setValue(0);
    this->ui->demand_add_edit->clear();
    this->ui->producer_add_edit->clear();
    this->ui->sender_add_edit->clear();
    this->ui->port_from_add_edit->clear();
    this->ui->country_from_add_edit->clear();
    this->ui->port_to_add_edit->clear();
    this->ui->country_to_add_edit->clear();
    this->ui->receiver_add_edit->clear();
    this->ui->other_add_edit->clear();

    // Возвращение начального вида полей
    this->ui->organization_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->INN_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->phone_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->mail_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->cargo_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->feature_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->TNVED_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->direction_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->length_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->width_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->height_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->weight_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->package_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->quantity_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->traffic_in_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->traffic_out_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->date_in_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->date_out_add_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->storage_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->term_add_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->demand_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->producer_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->sender_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->port_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_from_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->port_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_to_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->receiver_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->other_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных значений комментариев
    this->ui->organization_add_note_label->setText("* Обязательно для заполнения");
    this->ui->INN_add_note_label->setText("* Обязательно для заполнения");
    this->ui->phone_add_note_label->setText("* Обязательно для заполнения");
    this->ui->mail_add_note_label->setText("* Обязательно для заполнения");
    this->ui->cargo_add_note_label->setText("* Обязательно для заполнения");
    this->ui->feature_add_note_label->setText("* Обязательно для заполнения");
    this->ui->TNVED_add_note_label->setText("* Обязательно для заполнения");
    this->ui->direction_add_note_label->setText("* Обязательно для заполнения");
    this->ui->length_add_note_label->setText("* Обязательно для заполнения");
    this->ui->width_add_note_label->setText("* Обязательно для заполнения");
    this->ui->height_add_note_label->setText("* Обязательно для заполнения");
    this->ui->weight_add_note_label->setText("* Обязательно для заполнения");
    this->ui->package_add_note_label->setText("* Обязательно для заполнения");
    this->ui->quantity_add_note_label->setText("* Обязательно для заполнения");
    this->ui->traffic_in_add_note_label->setText("* Обязательно для заполнения");
    this->ui->traffic_out_add_note_label->setText("* Обязательно для заполнения");
    this->ui->date_in_add_note_label->setText("* Обязательно для заполнения");
    this->ui->date_out_add_note_label->setText("* Обязательно для заполнения");
    this->ui->storage_add_note_label->setText("* Обязательно для заполнения");
    this->ui->term_add_note_label->setText("* Обязательно для заполнения");
    this->ui->demand_add_note_label->setText("* Обязательно для заполнения");
    this->ui->producer_add_note_label->setText("* Обязательно для заполнения");
    this->ui->sender_add_note_label->setText("* Обязательно для заполнения");
    this->ui->port_from_add_note_label->setText("* Обязательно для заполнения");
    this->ui->country_from_add_note_label->setText("* Обязательно для заполнения");
    this->ui->port_to_add_note_label->setText("* Обязательно для заполнения");
    this->ui->country_to_add_note_label->setText("* Обязательно для заполнения");
    this->ui->receiver_add_note_label->setText("* Обязательно для заполнения");
    this->ui->other_add_note_label->clear();

    // Возвращение начального вида комментариев
    this->ui->organization_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->INN_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->phone_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->mail_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->cargo_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->feature_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->TNVED_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->direction_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->length_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->width_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->height_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->weight_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->package_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->quantity_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->traffic_in_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->traffic_out_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->date_in_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->date_out_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->storage_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->term_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->demand_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->producer_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->sender_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->port_from_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_from_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->port_to_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_to_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->receiver_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->other_add_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального вида кнопок формы
    this->ui->space_1_label->clear();
    this->ui->bid_check_add_button->setEnabled(true);
    this->ui->bid_feasibility_add_button->setEnabled(false);
    this->ui->bid_add_button->setEnabled(false);
}

void AdministrationWindow::CheckBidIdUpdate()
{
    // TODO снятие заявки с занятости

    ClearBidUpdateForm();
    ActivateBidUpdateForm(false);

    this->ui->bid_choose_update_label->clear();
    this->ui->bid_check_update_button->setEnabled(false);
}

void AdministrationWindow::FindBidUpdate()
{
    // TODO организовать отправку ID заявки на сервер

    // Заглушка отправки
    bool is_correct = this->ui->bid_id_update_edit->text().length() == 14;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка идентификатора заявки
    if (!is_correct)
    {
        this->ui->bid_id_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_id_update_note_label->setText("* Длина меньше 14 символов");
        this->ui->bid_id_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->bid_id_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_update_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->bid_id_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->bid_id_update_note_label->setText("* Обязательно для заполнения");
        this->ui->bid_id_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка ответа на поиск заявки
    if (!is_correct)
    {
        this->ui->bid_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_update_label->setText("* Ошибка в идентификаторе заявки");
    }
    else if (!is_work)
    {
        this->ui->bid_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_update_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->bid_choose_update_label->setStyleSheet("color: #F5F116;");
            this->ui->bid_choose_update_label->setText("* Заявки нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->bid_choose_update_label->setStyleSheet("color: #F5F116;");
                this->ui->bid_choose_update_label->setText("* Заявка занята сотрудником");
            }
            else
            {
                this->ui->bid_choose_update_label->setStyleSheet("color: #00FF00;");
                this->ui->bid_choose_update_label->setText("* Заявка найдена");

                ActivateBidUpdateForm(true);
                this->ui->bid_check_update_button->setEnabled(true);
            }
        }
    }
}

void AdministrationWindow::CheckBidUpdateForm()
{
    // Установка разрешённых символов для характеристик и требований к грузу
    QString feature_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789 -";
    QString demand_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                           "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                           "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                           "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    QChar wrong_feature = '-';
    QChar wrong_demand = '-';

    // Получение значений полей формы
    double length = this->ui->length_update_spin->value();
    double width = this->ui->width_update_spin->value();
    double height = this->ui->height_update_spin->value();
    QString feature = this->ui->feature_update_edit->toPlainText();
    QString demand = this->ui->demand_update_edit->toPlainText();

    // Проверка характеристик груза
    for (int i = 0; i < feature.length(); i++)
    {
        if (!feature_grant.contains(feature[i]))
        {
            wrong_feature = feature[i];
            break;
        }
    }

    // Проверка требований к грузу
    for (int i = 0; i < demand.length(); i++)
    {
        if (!demand_grant.contains(demand[i]))
        {
            wrong_demand = demand[i];
            break;
        }
    }

    // Проверка длины единицы груза
    if (length == 0)
    {
        this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->length_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->length_update_note_label->setText("* Длина единицы груза равна нулю");
    }
    else
    {
        this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->length_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->length_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка ширины единицы груза
    if (width == 0)
    {
        this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->width_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->width_update_note_label->setText("* Ширина единицы груза равна нулю");
    }
    else
    {
        this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->width_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->width_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка высоты единицы груза
    if (height == 0)
    {
        this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->height_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->height_update_note_label->setText("* Высота единицы груза равна нулю");
    }
    else
    {
        this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->height_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->height_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка характеристик груза
    if (wrong_feature != '-')
    {
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_update_note_label->setText(QString("* Запрещённый символ ") + wrong_feature);
    }
    else
    {
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->feature_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->feature_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка требований к грузу
    if (wrong_demand != '-')
    {
        int index = demand.indexOf(wrong_demand);
        QTextCursor cursor = this->ui->demand_update_edit->textCursor();

        cursor.setPosition(index);
        cursor.deleteChar();
    }

    // Установка доступности кнопок формы
    this->ui->space_2_label->clear();
    this->ui->bid_feasibility_update_button->setEnabled(false);
    this->ui->bid_update_button->setEnabled(false);
}

void AdministrationWindow::CheckBidUpdateContents()
{
    // Установка разрешённых символов для характеристик и прочей информации о грузе
    QString feature_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                            "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                            "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                            "0123456789 -";
    QString other_grant = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                          "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                          "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                          "0123456789"
                          "@#$%^&*() _+={}[]|\\;:\"'<>,.?/~-";
    bool is_feature_correct = true;
    bool is_other_correct = true;
    bool is_bid_correct = true;

    // Получение строковых значений полей
    QString mail = this->ui->mail_update_edit->text();
    QString feature = this->ui->feature_update_edit->toPlainText();
    QString demand = this->ui->demand_update_edit->toPlainText();
    QString other = this->ui->other_update_edit->toPlainText();

    // Получение длин значений полей
    int organization_length = this->ui->organization_update_edit->text().length();
    int INN_length = this->ui->INN_update_edit->text().length();
    int phone_length = this->ui->phone_update_edit->text().length();
    int mail_length = this->ui->mail_update_edit->text().length();
    int cargo_length = this->ui->cargo_update_edit->text().length();
    int TNVED_length = this->ui->TNVED_update_edit->text().length();
    int package_length = this->ui->package_update_edit->text().length();
    int feature_length = feature.length();
    int demand_length = demand.length();
    int producer_length = this->ui->producer_update_edit->text().length();
    int sender_length = this->ui->sender_update_edit->text().length();
    int port_from_length = this->ui->port_from_update_edit->text().length();
    int country_from_length = this->ui->country_from_update_edit->text().length();
    int port_to_length = this->ui->port_to_update_edit->text().length();
    int country_to_length = this->ui->country_to_update_edit->text().length();
    int receiver_length = this->ui->receiver_update_edit->text().length();

    // Получение числовых и датированных значений полей
    double length = this->ui->length_update_spin->value();
    double width = this->ui->width_update_spin->value();
    double height = this->ui->height_update_spin->value();
    double weight = this->ui->weight_update_spin->value();
    int quantity = this->ui->quantity_update_spin->value();
    int term = this->ui->term_update_spin->value();
    QDate date_in = this->ui->date_in_update_date->date().addYears(100);
    QDate date_out = this->ui->date_out_update_date->date().addYears(100);

    // Проверка характеристик груза
    for (int i = 0; i < feature.length(); i++)
    {
        if (!feature_grant.contains(feature[i]))
        {
            is_feature_correct = false;
            break;
        }
    }

    // Проверка прочей информации о грузе
    for (int i = 0; i < other.length(); i++)
    {
        if (!other_grant.contains(other[i]))
        {
            is_other_correct = false;
            break;
        }
    }

    // Проверка длины наименования организации
    if (organization_length == 0)
    {
        is_bid_correct = false;
        this->ui->organization_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->organization_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->organization_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->organization_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->organization_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->organization_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины ИНН
    if (INN_length == 0)
    {
        is_bid_correct = false;
        this->ui->INN_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->INN_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->INN_update_note_label->setText("* Длина равна нулю");
    }
    else if (INN_length < 10)
    {
        is_bid_correct = false;
        this->ui->INN_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->INN_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->INN_update_note_label->setText("* Длина меньше 10 символов");
    }
    else
    {
        this->ui->INN_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->INN_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->INN_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины номера телефона
    if (phone_length == 0)
    {
        is_bid_correct = false;
        this->ui->phone_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->phone_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->phone_update_note_label->setText("* Длина равна нулю");
    }
    else if (phone_length < 12)
    {
        is_bid_correct = false;
        this->ui->phone_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->phone_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->phone_update_note_label->setText("* Длина меньше 12 символов");
    }
    else
    {
        this->ui->phone_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->phone_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->phone_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка электронной почты
    if (mail_length == 0)
    {
        is_bid_correct = false;
        this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_update_note_label->setText("* Длина равна нулю");
    }
    else if (!mail.contains('@'))
    {
        is_bid_correct = false;
        this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_update_note_label->setText("* Отсутствие символа @");
    }
    else if (!mail.contains('.') || (mail.indexOf('.') - mail.indexOf('@') - 1) < 2 || (mail_length - mail.indexOf('.') - 1) < 2)
    {
        is_bid_correct = false;
        this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->mail_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->mail_update_note_label->setText("* Неправильный домен");
    }
    else
    {
        this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->mail_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->mail_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины наименования груза
    if (cargo_length == 0)
    {
        is_bid_correct = false;
        this->ui->cargo_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->cargo_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->cargo_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->cargo_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->cargo_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->cargo_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины кода ТН ВЭД
    if (TNVED_length == 0)
    {
        is_bid_correct = false;
        this->ui->TNVED_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->TNVED_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->TNVED_update_note_label->setText("* Длина равна нулю");
    }
    else if (TNVED_length < 10)
    {
        is_bid_correct = false;
        this->ui->TNVED_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->TNVED_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->TNVED_update_note_label->setText("* Длина меньше 10 символов");
    }
    else
    {
        this->ui->TNVED_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->TNVED_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->TNVED_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины единицы груза
    if (length == 0)
    {
        is_bid_correct = false;
        this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->length_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->length_update_note_label->setText("* Длина единицы груза равна нулю");
    }
    else
    {
        this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->length_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->length_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка ширины единицы груза
    if (width == 0)
    {
        is_bid_correct = false;
        this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->width_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->width_update_note_label->setText("* Ширина единицы груза равна нулю");
    }
    else
    {
        this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->width_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->width_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка высоты единицы груза
    if (height == 0)
    {
        is_bid_correct = false;
        this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->height_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->height_update_note_label->setText("* Высота единицы груза равна нулю");
    }
    else
    {
        this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->height_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->height_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка массы единицы груза
    if (weight == 0)
    {
        is_bid_correct = false;
        this->ui->weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->weight_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->weight_update_note_label->setText("* Масса единицы груза равна нулю");
    }
    else
    {
        this->ui->weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->weight_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->weight_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины упаковки груза
    if (package_length == 0)
    {
        is_bid_correct = false;
        this->ui->package_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->package_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->package_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->package_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->package_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->package_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка характеристик груза
    if (feature_length == 0)
    {
        is_bid_correct = false;
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_update_note_label->setText("* Длина равна нулю");
    }
    else if (!is_feature_correct)
    {
        is_bid_correct = false;
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->feature_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->feature_update_note_label->setText("* Наличие запрещённых символов");
    }
    else
    {
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->feature_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->feature_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка количества единиц груза
    if (quantity == 0)
    {
        is_bid_correct = false;
        this->ui->quantity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->quantity_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->quantity_update_note_label->setText("* Количество единиц груза равно нулю");
    }
    else
    {
        this->ui->quantity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->quantity_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->quantity_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка даты завоза груза
    if (date_in < QDate::currentDate())
    {
        is_bid_correct = false;
        this->ui->date_in_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_in_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_in_update_note_label->setText("* Дата уже прошла");
    }
    else
    {
        this->ui->date_in_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_in_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->date_in_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка даты вывоза груза
    if (date_out < QDate::currentDate())
    {
        is_bid_correct = false;
        this->ui->date_out_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_out_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_out_update_note_label->setText("* Дата уже прошла");
    }
    else if (date_out < date_in)
    {
        is_bid_correct = false;
        this->ui->date_out_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->date_out_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->date_out_update_note_label->setText("* Дата вывоза меньше даты завоза");
    }
    else
    {
        this->ui->date_out_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_out_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->date_out_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка срока хранения груза
    if (term == 0)
    {
        is_bid_correct = false;
        this->ui->term_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red; padding: 1px 18px 1px 4px;");
        this->ui->term_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->term_update_note_label->setText("* Срок хранения груза равен нулю");
    }
    else
    {
        this->ui->term_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->term_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->term_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка требований к грузу
    if (demand_length == 0)
    {
        is_bid_correct = false;
        this->ui->demand_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->demand_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->demand_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->demand_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->demand_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->demand_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины производителя
    if (producer_length == 0)
    {
        is_bid_correct = false;
        this->ui->producer_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->producer_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->producer_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->producer_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->producer_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->producer_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины получателя
    if (sender_length == 0)
    {
        is_bid_correct = false;
        this->ui->sender_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->sender_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->sender_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->sender_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->sender_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->sender_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины порта отправления
    if (port_from_length == 0)
    {
        is_bid_correct = false;
        this->ui->port_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->port_from_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->port_from_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->port_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_from_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->port_from_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины страны отправления
    if (country_from_length == 0)
    {
        is_bid_correct = false;
        this->ui->country_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->country_from_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_from_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->country_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_from_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_from_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины порта прибытия
    if (port_to_length == 0)
    {
        is_bid_correct = false;
        this->ui->port_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->port_to_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->port_to_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->port_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_to_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->port_to_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины страны прибытия
    if (country_to_length == 0)
    {
        is_bid_correct = false;
        this->ui->country_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->country_to_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->country_to_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->country_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_to_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->country_to_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка длины получателя
    if (receiver_length == 0)
    {
        is_bid_correct = false;
        this->ui->receiver_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->receiver_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->receiver_update_note_label->setText("* Длина равна нулю");
    }
    else
    {
        this->ui->receiver_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->receiver_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->receiver_update_note_label->setText("* Обязательно для заполнения");
    }

    // Проверка прочей информации о грузе
    if (!is_other_correct)
    {
        is_bid_correct = false;
        this->ui->other_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
        this->ui->other_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->other_update_note_label->setText("* Наличие запрещённых символов");
    }
    else
    {
        this->ui->other_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->other_update_note_label->clear();
    }

    // Проверка корректности заявки
    if (is_bid_correct)
    {
        this->ui->space_2_label->setStyleSheet("color: #00FF00;");
        this->ui->space_2_label->setText("* Проверка содержимого заявки прошла успешно");
        this->ui->bid_feasibility_update_button->setEnabled(true);
    }
    else
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* В содержимом заявки обнаружены ошибки");
    }
}

void AdministrationWindow::CheckBidUpdateFeasibility()
{
    // TODO проверить наличие контейнеров и морских судов по код ТН ВЭД

    // Заглушка проверки осуществимости
    bool is_work = true;
    bool is_feasibility = true;

    if (!is_work)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_feasibility)
        {
            this->ui->space_2_label->setStyleSheet("color: #F5F116;");
            this->ui->space_2_label->setText("* Невозможно выполнить заявку. Отсутствуют морские суда или контейнеры");
        }
        else
        {
            this->ui->space_2_label->setStyleSheet("color: #00FF00;");
            this->ui->space_2_label->setText("* Проверка осуществимости прошла успешно");
            this->ui->bid_update_button->setEnabled(true);
        }
    }
}

void AdministrationWindow::UpdateBid()
{
    // TODO организовать отправку заявки на сервер

    // Заглушка отправки
    bool is_work = true;

    if (!is_work)
    {
        this->ui->space_2_label->setStyleSheet("color: #F5F116;");
        this->ui->space_2_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->bid_id_update_edit->clear();
        this->ui->space_2_label->setStyleSheet("color: #00FF00;");
        this->ui->space_2_label->setText("* Заявка изменена");
    }
}

void AdministrationWindow::ClearBidUpdateForm()
{
    // Возвращение начальных значений полей формы
    this->ui->organization_update_edit->clear();
    this->ui->INN_update_edit->clear();
    this->ui->phone_update_edit->clear();
    this->ui->mail_update_edit->clear();
    this->ui->cargo_update_edit->clear();
    this->ui->feature_update_edit->clear();
    this->ui->TNVED_update_edit->clear();
    this->ui->direction_update_box->setCurrentIndex(0);
    this->ui->length_update_spin->setValue(0);
    this->ui->width_update_spin->setValue(0);
    this->ui->height_update_spin->setValue(0);
    this->ui->weight_update_spin->setValue(0);
    this->ui->package_update_edit->clear();
    this->ui->quantity_update_spin->setValue(0);
    this->ui->traffic_in_update_box->setCurrentIndex(0);
    this->ui->traffic_out_update_box->setCurrentIndex(0);
    this->ui->date_in_update_date->setDate(QDate(1900, 1, 1));
    this->ui->date_out_update_date->setDate(QDate(1900, 1, 1));
    this->ui->storage_update_box->setCurrentIndex(0);
    this->ui->term_update_spin->setValue(0);
    this->ui->demand_update_edit->clear();
    this->ui->producer_update_edit->clear();
    this->ui->sender_update_edit->clear();
    this->ui->port_from_update_edit->clear();
    this->ui->country_from_update_edit->clear();
    this->ui->port_to_update_edit->clear();
    this->ui->country_to_update_edit->clear();
    this->ui->receiver_update_edit->clear();
    this->ui->other_update_edit->clear();

    // Возвращение начального вида полей формы
    this->ui->organization_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->INN_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->phone_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->cargo_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->TNVED_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->direction_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->package_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->quantity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->traffic_in_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->traffic_out_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->date_in_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->date_out_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->storage_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->term_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->demand_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->producer_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->sender_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->port_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->port_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->country_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->receiver_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->other_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных комментариев формы
    this->ui->organization_update_note_label->setText("* Обязательно для заполнения");
    this->ui->INN_update_note_label->setText("* Обязательно для заполнения");
    this->ui->phone_update_note_label->setText("* Обязательно для заполнения");
    this->ui->mail_update_note_label->setText("* Обязательно для заполнения");
    this->ui->cargo_update_note_label->setText("* Обязательно для заполнения");
    this->ui->feature_update_note_label->setText("* Обязательно для заполнения");
    this->ui->TNVED_update_note_label->setText("* Обязательно для заполнения");
    this->ui->direction_update_note_label->setText("* Обязательно для заполнения");
    this->ui->length_update_note_label->setText("* Обязательно для заполнения");
    this->ui->width_update_note_label->setText("* Обязательно для заполнения");
    this->ui->height_update_note_label->setText("* Обязательно для заполнения");
    this->ui->weight_update_note_label->setText("* Обязательно для заполнения");
    this->ui->package_update_note_label->setText("* Обязательно для заполнения");
    this->ui->quantity_update_note_label->setText("* Обязательно для заполнения");
    this->ui->traffic_in_update_note_label->setText("* Обязательно для заполнения");
    this->ui->traffic_out_update_note_label->setText("* Обязательно для заполнения");
    this->ui->date_in_update_note_label->setText("* Обязательно для заполнения");
    this->ui->date_out_update_note_label->setText("* Обязательно для заполнения");
    this->ui->storage_update_note_label->setText("* Обязательно для заполнения");
    this->ui->term_update_note_label->setText("* Обязательно для заполнения");
    this->ui->demand_update_note_label->setText("* Обязательно для заполнения");
    this->ui->producer_update_note_label->setText("* Обязательно для заполнения");
    this->ui->sender_update_note_label->setText("* Обязательно для заполнения");
    this->ui->port_from_update_note_label->setText("* Обязательно для заполнения");
    this->ui->country_from_update_note_label->setText("* Обязательно для заполнения");
    this->ui->port_to_update_note_label->setText("* Обязательно для заполнения");
    this->ui->country_to_update_note_label->setText("* Обязательно для заполнения");
    this->ui->receiver_update_note_label->setText("* Обязательно для заполнения");
    this->ui->other_update_note_label->clear();

    // Возвращение начального вида комментариев формы
    this->ui->organization_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->INN_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->phone_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->mail_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->cargo_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->feature_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->TNVED_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->direction_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->length_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->width_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->height_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->weight_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->package_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->quantity_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->traffic_in_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->traffic_out_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->date_in_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->date_out_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->storage_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->term_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->demand_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->producer_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->sender_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->port_from_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_from_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->port_to_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->country_to_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->receiver_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->other_update_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального состояния кнопок формы
    this->ui->space_2_label->clear();
    this->ui->bid_check_update_button->setEnabled(true);
    this->ui->bid_feasibility_update_button->setEnabled(false);
    this->ui->bid_update_button->setEnabled(false);
}

void AdministrationWindow::ActivateBidUpdateForm(bool flag)
{
    // Активация или блокировка полей формы
    this->ui->organization_update_edit->setEnabled(flag);
    this->ui->INN_update_edit->setEnabled(flag);
    this->ui->phone_update_edit->setEnabled(flag);
    this->ui->mail_update_edit->setEnabled(flag);
    this->ui->cargo_update_edit->setEnabled(flag);
    this->ui->feature_update_edit->setEnabled(flag);
    this->ui->TNVED_update_edit->setEnabled(flag);
    this->ui->direction_update_box->setEnabled(flag);
    this->ui->length_update_spin->setEnabled(flag);
    this->ui->width_update_spin->setEnabled(flag);
    this->ui->height_update_spin->setEnabled(flag);
    this->ui->weight_update_spin->setEnabled(flag);
    this->ui->package_update_edit->setEnabled(flag);
    this->ui->quantity_update_spin->setEnabled(flag);
    this->ui->traffic_in_update_box->setEnabled(flag);
    this->ui->traffic_out_update_box->setEnabled(flag);
    this->ui->date_in_update_date->setEnabled(flag);
    this->ui->date_out_update_date->setEnabled(flag);
    this->ui->storage_update_box->setEnabled(flag);
    this->ui->term_update_spin->setEnabled(flag);
    this->ui->demand_update_edit->setEnabled(flag);
    this->ui->producer_update_edit->setEnabled(flag);
    this->ui->sender_update_edit->setEnabled(flag);
    this->ui->port_from_update_edit->setEnabled(flag);
    this->ui->country_from_update_edit->setEnabled(flag);
    this->ui->port_to_update_edit->setEnabled(flag);
    this->ui->country_to_update_edit->setEnabled(flag);
    this->ui->receiver_update_edit->setEnabled(flag);
    this->ui->other_update_edit->setEnabled(flag);

    // Выбор стиля полей формы
    if (flag)
    {
        this->ui->organization_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->INN_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->phone_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->mail_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->cargo_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->feature_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->TNVED_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->direction_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->length_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->width_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->height_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->weight_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->package_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->quantity_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->traffic_in_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->traffic_out_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_in_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->date_out_update_date->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->storage_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->term_update_spin->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->demand_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->producer_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->sender_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_from_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->port_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->country_to_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->receiver_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->other_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->organization_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->INN_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->phone_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->mail_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->cargo_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->feature_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->TNVED_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->direction_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->length_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->width_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->height_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->weight_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->package_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->quantity_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->traffic_in_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->traffic_out_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->date_in_update_date->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->date_out_update_date->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->storage_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->term_update_spin->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->demand_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->producer_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->sender_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->port_from_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->country_from_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->port_to_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->country_to_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->receiver_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->other_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
    }
}

void AdministrationWindow::DeleteBid()
{
    // TODO организовать удаление заявки на сервере

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

    // Установка результата удаления заявки
    if (!is_correct)
    {
        this->ui->bid_choose_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_delete_label->setText("* Ошибка в идентификаторе заявки");
    }
    else if (!is_work)
    {
        this->ui->bid_choose_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->bid_choose_delete_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->bid_choose_delete_label->setStyleSheet("color: #F5F116;");
            this->ui->bid_choose_delete_label->setText("* Заявки нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->bid_choose_delete_label->setStyleSheet("color: #F5F116;");
                this->ui->bid_choose_delete_label->setText("* Заявку нельзя удалить");
            }
            else
            {
                this->ui->bid_id_delete_edit->clear();
                this->ui->bid_choose_delete_label->setStyleSheet("color: #00FF00;");
                this->ui->bid_choose_delete_label->setText("* Заявка удалена");
            }
        }
    }
}

void AdministrationWindow::CheckBidIdRead()
{
    ClearBidReadForm();

    this->ui->bid_choose_read_label->clear();
}

void AdministrationWindow::FindBidRead()
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

void AdministrationWindow::ClearBidReadForm()
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

void AdministrationWindow::CheckCaseOptionsRead()
{
    ClearCaseReadForm();

    this->ui->case_choose_read_label->clear();
}

void AdministrationWindow::FindCaseRead()
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

void AdministrationWindow::ClearCaseReadForm()
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

void AdministrationWindow::CheckIMORead()
{
    ClearShipReadForm();

    this->ui->ship_choose_read_label->clear();
}

void AdministrationWindow::FindShipRead()
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

void AdministrationWindow::ClearShipReadForm()
{
    // Возвращение исходного состояния формы
    this->ui->ship_type_read_edit->clear();
    this->ui->ship_name_read_edit->clear();
    this->ui->ship_country_read_edit->clear();
    this->ui->ship_carrying_read_spin->setValue(0);
    this->ui->workload_read_spin->setValue(0);
    this->ui->ship_status_read_edit->clear();
}

void AdministrationWindow::CheckUserAddForm()
{
    // Получение длин проверяемых полей
    int username_length = this->ui->username_add_edit->text().length();
    int password_length = this->ui->password_add_edit->text().length();

    // Проверка длины имени пользователя
    if (username_length < 12 || username_length > 16)
    {
        this->ui->username_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_add_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_add_note_label->setText("* Обязательно для заполнения");
        this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка длины пароля
    if (password_length < 12 || password_length > 16)
    {
        this->ui->password_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_add_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_add_note_label->setText("* Обязательно для заполнения");
        this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
}

void AdministrationWindow::AddUser()
{
    // TODO организовать добавление пользователя на сервере

    // Заглушка отправки
    bool is_surname = this->ui->surname_add_edit->text().length() > 0;
    bool is_name = this->ui->name_add_edit->text().length() > 0;
    bool is_username = this->ui->username_add_edit->text().length() >= 12 && this->ui->username_add_edit->text().length() <= 16;
    bool is_password = this->ui->password_add_edit->text().length() >= 12 && this->ui->password_add_edit->text().length() <= 16;
    bool is_repeat = this->ui->repeat_add_edit->text() == this->ui->password_add_edit->text();
    bool is_username_unic = true;
    bool is_password_unic = true;
    bool is_correct = is_surname && is_name && is_username && is_password && is_repeat && is_username_unic && is_password_unic;
    bool is_work = true;

    // Проверка фамилии
    if (!is_surname)
    {
        this->ui->surname_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->surname_add_note_label->setText("* Длина равна нулю");
        this->ui->surname_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->surname_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->surname_add_note_label->setText("* Обязательно для заполнения");
        this->ui->surname_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка имени
    if (!is_name)
    {
        this->ui->name_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->name_add_note_label->setText("* Длина равна нулю");
        this->ui->name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->name_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->name_add_note_label->setText("* Обязательно для заполнения");
        this->ui->name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка имени пользователя
    if (!is_username)
    {
        this->ui->username_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_add_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_username_unic)
    {
        this->ui->username_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_add_note_label->setText("* Имя пользователя не уникально");
        this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_add_note_label->setText("* Обязательно для заполнения");
        this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка пароля
    if (!is_password)
    {
        this->ui->password_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_add_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_password_unic)
    {
        this->ui->password_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_add_note_label->setText("* Пароль не уникален");
        this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_add_note_label->setText("* Обязательно для заполнения");
        this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка повтора пароля
    if (!is_repeat)
    {
        this->ui->repeat_add_note_label->setStyleSheet("color: #F5F116;");
        this->ui->repeat_add_note_label->setText("* Отличен от пароля");
        this->ui->repeat_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->repeat_add_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->repeat_add_note_label->setText("* Обязательно для заполнения");
        this->ui->repeat_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата добавления пользователя
    if (!is_correct)
    {
        this->ui->user_add_label->setStyleSheet("color: #F5F116;");
        this->ui->user_add_label->setText("* В данных пользователя обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->user_add_label->setStyleSheet("color: #F5F116;");
        this->ui->user_add_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        ClearUserAddForm();

        this->ui->user_add_label->setStyleSheet("color: #00FF00;");
        this->ui->user_add_label->setText("* Пользователь добавлен");
    }
}

void AdministrationWindow::ClearUserAddForm()
{
    // Возвращение начальных значений полей формы
    this->ui->surname_add_edit->clear();
    this->ui->name_add_edit->clear();
    this->ui->patronym_add_edit->clear();
    this->ui->job_add_box->setCurrentIndex(0);
    this->ui->username_add_edit->clear();
    this->ui->password_add_edit->clear();
    this->ui->repeat_add_edit->clear();

    // Возвращение начального вида полей формы
    this->ui->surname_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->name_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->patronym_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->job_add_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->username_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->password_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->repeat_add_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных комментариев формы
    this->ui->surname_add_note_label->setText("* Обязательно для заполнения");
    this->ui->name_add_note_label->setText("* Обязательно для заполнения");
    this->ui->patronym_add_note_label->clear();
    this->ui->job_add_note_label->clear();
    this->ui->username_add_note_label->setText("* Обязательно для заполнения");
    this->ui->password_add_note_label->setText("* Обязательно для заполнения");
    this->ui->repeat_add_note_label->setText("* Обязательно для заполнения");

    // Возвращение начального вида комментариев формы
    this->ui->surname_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->name_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->patronym_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->job_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->username_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->password_add_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->repeat_add_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального состояния кнопок формы
    this->ui->user_add_button->setEnabled(true);
    this->ui->user_add_label->clear();
}

void AdministrationWindow::CheckUserOptionsUpdate()
{
    // Получение длин проверяемых полей формы
    int username_length = this->ui->username_update_edit->text().length();
    int password_length = this->ui->password_update_edit->text().length();

    // Проверка длины имени пользователя
    if (username_length < 12 || username_length > 16)
    {
        this->ui->username_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка длины пароля
    if (password_length < 12 || password_length > 16)
    {
        this->ui->password_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    ClearUserUpdateForm();
    ActivateUserUpdateForm(false);

    this->ui->user_choose_update_label->clear();
    this->ui->user_update_button->setEnabled(false);
}

void AdministrationWindow::FindUserUpdate()
{
    // TODO организовать отправку имени пользователя и пароля на сервер

    // Заглушка отправки
    bool is_username = this->ui->username_update_edit->text().length() >= 12 && this->ui->username_update_edit->text().length() <= 16;
    bool is_password = this->ui->password_update_edit->text().length() >= 12 && this->ui->password_update_edit->text().length() <= 16;
    bool is_correct = is_username && is_password;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка имени пользователя
    if (!is_username)
    {
        this->ui->username_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка пароля
    if (!is_password)
    {
        this->ui->password_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата поиска пользователя
    if (!is_correct)
    {
        this->ui->user_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->user_choose_update_label->setText("* Ошибка в данных пользователя");
    }
    else if (!is_work)
    {
        this->ui->user_choose_update_label->setStyleSheet("color: #F5F116;");
        this->ui->user_choose_update_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->user_choose_update_label->setStyleSheet("color: #F5F116;");
            this->ui->user_choose_update_label->setText("* Пользователя нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->user_choose_update_label->setStyleSheet("color: #F5F116;");
                this->ui->user_choose_update_label->setText("* Пользователь сейчас в системе");
            }
            else
            {
                this->ui->user_choose_update_label->setStyleSheet("color: #00FF00;");
                this->ui->user_choose_update_label->setText("* Пользователь найден");

                ActivateUserUpdateForm(true);
                this->ui->user_update_button->setEnabled(true);
            }
        }
    }
}

void AdministrationWindow::CheckUserUpdateForm()
{
    // Получение длин проверяемых полей
    int username_length = this->ui->new_username_update_edit->text().length();
    int password_length = this->ui->new_password_update_edit->text().length();

    // Проверка имени пользователя
    if (username_length < 12 || username_length > 16)
    {
        this->ui->new_username_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_username_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка пароля
    if (password_length < 12 || password_length > 16)
    {
        this->ui->new_password_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_password_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
}

void AdministrationWindow::UpdateUser()
{
    // TODO организовать изменение пользователя на сервере

    // Заглушка отправки
    bool is_surname = this->ui->surname_update_edit->text().length() > 0;
    bool is_name = this->ui->name_update_edit->text().length() > 0;
    bool is_username = this->ui->new_username_update_edit->text().length() >= 12 && this->ui->new_username_update_edit->text().length() <= 16;
    bool is_password = this->ui->new_password_update_edit->text().length() >= 12 && this->ui->new_password_update_edit->text().length() <= 16;
    bool is_repeat = this->ui->repeat_update_edit->text() == this->ui->new_password_update_edit->text();
    bool is_username_unic = true;
    bool is_password_unic = true;
    bool is_correct = is_surname && is_name && is_username && is_password && is_repeat && is_username_unic && is_password_unic;
    bool is_work = true;

    // Проверка фамилии
    if (!is_surname)
    {
        this->ui->surname_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->surname_update_note_label->setText("* Длина равна нулю");
        this->ui->surname_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->surname_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->surname_update_note_label->setText("* Обязательно для заполнения");
        this->ui->surname_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка имени
    if (!is_name)
    {
        this->ui->name_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->name_update_note_label->setText("* Длина равна нулю");
        this->ui->name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->name_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->name_update_note_label->setText("* Обязательно для заполнения");
        this->ui->name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка имени пользователя
    if (!is_username)
    {
        this->ui->new_username_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_username_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_username_unic)
    {
        this->ui->new_username_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_username_update_note_label->setText("* Имя пользователя не уникально");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка пароля
    if (!is_password)
    {
        this->ui->new_password_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_password_update_note_label->setText("* Длина меньше 12 символов");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_password_unic)
    {
        this->ui->new_password_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->new_password_update_note_label->setText("* Пароль не уникален");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->new_password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->new_password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка повтора пароля
    if (!is_repeat)
    {
        this->ui->repeat_update_note_label->setStyleSheet("color: #F5F116;");
        this->ui->repeat_update_note_label->setText("* Отличен от пароля");
        this->ui->repeat_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->repeat_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->repeat_update_note_label->setText("* Обязательно для заполнения");
        this->ui->repeat_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата изменения пользователя
    if (!is_correct)
    {
        this->ui->user_update_label->setStyleSheet("color: #F5F116;");
        this->ui->user_update_label->setText("* В данных пользователя обнаружены ошибки");
    }
    else if (!is_work)
    {
        this->ui->user_update_label->setStyleSheet("color: #F5F116;");
        this->ui->user_update_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        this->ui->username_update_edit->clear();
        this->ui->password_update_edit->clear();
        this->ui->username_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_update_note_label->setText("* Обязательно для заполнения");
        this->ui->username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->password_update_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_update_note_label->setText("* Обязательно для заполнения");
        this->ui->password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->user_update_label->setStyleSheet("color: #00FF00;");
        this->ui->user_update_label->setText("* Пользователь изменён");
    }
}

void AdministrationWindow::ClearUserUpdateForm()
{
    // Возвращение начальных значений полей формы
    this->ui->surname_update_edit->clear();
    this->ui->name_update_edit->clear();
    this->ui->patronym_update_edit->clear();
    this->ui->job_update_box->setCurrentIndex(0);
    this->ui->new_username_update_edit->clear();
    this->ui->new_password_update_edit->clear();
    this->ui->repeat_update_edit->clear();

    // Возвращение начального вида полей формы
    this->ui->surname_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->patronym_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->job_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    this->ui->repeat_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");

    // Возвращение начальных комментариев формы
    this->ui->surname_update_note_label->setText("* Обязательно для заполнения");
    this->ui->name_update_note_label->setText("* Обязательно для заполнения");
    this->ui->patronym_update_note_label->clear();
    this->ui->job_update_note_label->clear();
    this->ui->new_username_update_note_label->setText("* Обязательно для заполнения");
    this->ui->new_password_update_note_label->setText("* Обязательно для заполнения");
    this->ui->repeat_update_note_label->setText("* Обязательно для заполнения");

    // Возвращение начального вида комментариев формы
    this->ui->surname_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->name_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->patronym_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->job_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->new_username_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->new_password_update_note_label->setStyleSheet("color: #FFFFFF;");
    this->ui->repeat_update_note_label->setStyleSheet("color: #FFFFFF;");

    // Возвращение начального состояния кнопок формы
    this->ui->user_update_button->setEnabled(true);
    this->ui->user_update_label->clear();
}

void AdministrationWindow::ActivateUserUpdateForm(bool flag)
{
    // Активация и блокировка полей формы
    this->ui->surname_update_edit->setEnabled(flag);
    this->ui->name_update_edit->setEnabled(flag);
    this->ui->patronym_update_edit->setEnabled(flag);
    this->ui->job_update_box->setEnabled(flag);
    this->ui->new_username_update_edit->setEnabled(flag);
    this->ui->new_password_update_edit->setEnabled(flag);
    this->ui->repeat_update_edit->setEnabled(flag);

    // Установка вида полей формы
    if (flag)
    {
        this->ui->surname_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->name_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->patronym_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->job_update_box->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
        this->ui->repeat_update_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }
    else
    {
        this->ui->surname_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->name_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->patronym_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->job_update_box->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->new_username_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->new_password_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
        this->ui->repeat_update_edit->setStyleSheet("background-color: #BBBBBB; color: black;");
    }
}

void AdministrationWindow::CheckUserOptionsDelete()
{
    // Получение длин проверяемых значений
    int username_length = this->ui->username_delete_edit->text().length();
    int password_length = this->ui->password_delete_edit->text().length();

    // Проверка длины имени пользователя
    if (username_length < 12 || username_length > 16)
    {
        this->ui->username_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_delete_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка длины пароля
    if (password_length < 12 || password_length > 16)
    {
        this->ui->password_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_delete_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    this->ui->user_delete_label->clear();
}

void AdministrationWindow::DeleteUser()
{
    // TODO организовать удаление пользователя на сервере

    // Заглушка отправки
    bool is_username = this->ui->username_delete_edit->text().length() >= 12 && this->ui->username_delete_edit->text().length() <= 16;
    bool is_password = this->ui->password_delete_edit->text().length() >= 12 && this->ui->password_delete_edit->text().length() <= 16;
    bool is_correct = is_username && is_password;
    bool is_work = true;
    bool is_find = true;
    bool is_busy = false;

    // Проверка имени пользователя
    if (!is_username)
    {
        this->ui->username_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->username_delete_note_label->setText("* Длина меньше 12 символов");
        this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->username_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->username_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->username_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Проверка пароля
    if (!is_password)
    {
        this->ui->password_delete_note_label->setStyleSheet("color: #F5F116;");
        this->ui->password_delete_note_label->setText("* Длина меньше 12 символов");
        this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else if (!is_find)
    {
        this->ui->password_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000; border: 5px solid red;");
    }
    else
    {
        this->ui->password_delete_note_label->setStyleSheet("color: #FFFFFF;");
        this->ui->password_delete_note_label->setText("* Обязательно для заполнения");
        this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
    }

    // Установка результата удаления пользователя
    if (!is_correct)
    {
        this->ui->user_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->user_delete_label->setText("* Ошибка в данных пользователя");
    }
    else if (!is_work)
    {
        this->ui->user_delete_label->setStyleSheet("color: #F5F116;");
        this->ui->user_delete_label->setText("* Возникли неполадки на стороне сервера");
    }
    else
    {
        if (!is_find)
        {
            this->ui->user_delete_label->setStyleSheet("color: #F5F116;");
            this->ui->user_delete_label->setText("* Пользователя нет в системе");
        }
        else
        {
            if (is_busy)
            {
                this->ui->user_delete_label->setStyleSheet("color: #F5F116;");
                this->ui->user_delete_label->setText("* Пользователь сейчас в системе");
            }
            else
            {
                this->ui->username_delete_edit->clear();
                this->ui->password_delete_edit->clear();
                this->ui->username_delete_note_label->setStyleSheet("color: #FFFFFF;");
                this->ui->username_delete_note_label->setText("* Обязательно для заполнения");
                this->ui->username_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
                this->ui->password_delete_note_label->setStyleSheet("color: #FFFFFF;");
                this->ui->password_delete_note_label->setText("* Обязательно для заполнения");
                this->ui->password_delete_edit->setStyleSheet("background-color: #C5CAE9; color: #000000;");
                this->ui->user_delete_label->setStyleSheet("color: #00FF00;");
                this->ui->user_delete_label->setText("* Пользователь удалён");
            }
        }
    }
}

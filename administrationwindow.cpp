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
    QRegularExpression ship_name_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-zА-Яа-я\-])");
    QRegularExpression FIO_pattern(R"([А-Яа-яA-Za-z \-]+)");
    QRegularExpression username_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-z\-])");
    QRegularExpression password_pattern(R"([@#\$%\^&\*\(\)_\+\=\{\}\[\]\|\\;:"'<>,\./\?~0-9A-Za-z\-])");

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
    this->ui->IMO_read_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));

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
}

AdministrationWindow::~AdministrationWindow()
{
    delete this->ui;
}

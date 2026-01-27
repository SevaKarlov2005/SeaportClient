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
}

StorageWindow::~StorageWindow()
{
    delete this->ui;
}

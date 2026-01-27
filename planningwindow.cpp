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
    this->ui->IMO_read_edit->setValidator(new QRegularExpressionValidator(IMO_pattern));

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
}

PlanningWindow::~PlanningWindow()
{
    delete this->ui;
}

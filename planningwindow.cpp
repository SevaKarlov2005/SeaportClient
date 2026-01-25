#include "planningwindow.h"
#include "ui_planningwindow.h"

PlanningWindow::PlanningWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка интерфейса окна
    this->ui = new Ui::PlanningWindow;
    this->ui->setupUi(this);

    // Установка фиксированного размера окна
    setFixedSize(1045, 855);
}

PlanningWindow::~PlanningWindow()
{
    delete this->ui;
}

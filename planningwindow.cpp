#include "planningwindow.h"
#include "ui_planningwindow.h"

PlanningWindow::PlanningWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlanningWindow)
{
    ui->setupUi(this);
}

PlanningWindow::~PlanningWindow()
{
    delete ui;
}

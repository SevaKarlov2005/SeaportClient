#include "administrationwindow.h"
#include "ui_administrationwindow.h"

AdministrationWindow::AdministrationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdministrationWindow)
{
    ui->setupUi(this);
}

AdministrationWindow::~AdministrationWindow()
{
    delete ui;
}

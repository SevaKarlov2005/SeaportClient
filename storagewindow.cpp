#include "storagewindow.h"
#include "ui_storagewindow.h"

StorageWindow::StorageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StorageWindow)
{
    ui->setupUi(this);
}

StorageWindow::~StorageWindow()
{
    delete ui;
}

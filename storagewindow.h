#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class StorageWindow;
}

class StorageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StorageWindow(QWidget *parent = nullptr);
    ~StorageWindow();

private:
    Ui::StorageWindow *ui;
};

#endif // STORAGEWINDOW_H

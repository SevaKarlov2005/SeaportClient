#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StorageWindow;
}
QT_END_NAMESPACE

class StorageWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::StorageWindow *ui;
public:
    explicit StorageWindow(QWidget *parent = nullptr);
    ~StorageWindow();
};

#endif // STORAGEWINDOW_H

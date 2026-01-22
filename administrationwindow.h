#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministrationWindow;
}

class AdministrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministrationWindow(QWidget *parent = nullptr);
    ~AdministrationWindow();

private:
    Ui::AdministrationWindow *ui;
};

#endif // ADMINISTRATIONWINDOW_H

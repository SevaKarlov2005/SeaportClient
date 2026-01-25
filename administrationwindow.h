#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AdministrationWindow;
}
QT_END_NAMESPACE

class AdministrationWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::AdministrationWindow *ui;
public:
    explicit AdministrationWindow(QWidget *parent = nullptr);
    ~AdministrationWindow();
};

#endif // ADMINISTRATIONWINDOW_H

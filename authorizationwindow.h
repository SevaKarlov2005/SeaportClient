#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthorizationWindow;
}
QT_END_NAMESPACE

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::AuthorizationWindow *ui;
public:
    AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();
};

#endif // AUTHORIZATIONWINDOW_H

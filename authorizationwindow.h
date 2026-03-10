#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMainWindow>
#include "tcpserverconnection.h"

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
    QString host;
    TCPServerConnection connection;
public:
    AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();
    void CheckAuthorizationForm();
    void Enter();
};

#endif // AUTHORIZATIONWINDOW_H

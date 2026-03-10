#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "tcpserverconnection.h"

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
    QStandardItemModel* bid_model;
    QStandardItemModel* case_model;
    QStandardItemModel* ship_model;
    int bid_page;
    int case_page;
    int ship_page;
    QString host;
    QString username;
    QString bid_number;
    QString bid_status;
    TCPServerConnection connection;
public:
    explicit AdministrationWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent = nullptr);
    ~AdministrationWindow();
    void CheckBidAddForm();
    void CheckBidAddContents();
    void CheckBidAddFeasibility();
    void AddBid();
    void ClearBidAddForm();
    void CheckBidIdUpdate();
    void FindBidUpdate();
    void CheckBidUpdateForm();
    void CheckBidUpdateContents();
    void CheckBidUpdateFeasibility();
    void UpdateBid();
    void ClearBidUpdateForm();
    void ActivateBidUpdateForm(bool flag);
    void DeleteBid();
    void BidList();
    void CaseList();
    void ShipList();
    void CheckBidIdRead();
    void FindBidRead();
    void ClearBidReadForm();
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ClearCaseReadForm();
    void CheckIMORead();
    void FindShipRead();
    void ClearShipReadForm();
    void CheckUserAddForm();
    void AddUser();
    void ClearUserAddForm();
    void CheckUserOptionsUpdate();
    void FindUserUpdate();
    void CheckUserUpdateForm();
    void UpdateUser();
    void ClearUserUpdateForm();
    void ActivateUserUpdateForm(bool flag);
    void CheckUserOptionsDelete();
    void DeleteUser();
    void closeEvent(QCloseEvent *event) override;
};

#endif // ADMINISTRATIONWINDOW_H

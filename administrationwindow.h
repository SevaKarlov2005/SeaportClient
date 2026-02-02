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
};

#endif // ADMINISTRATIONWINDOW_H

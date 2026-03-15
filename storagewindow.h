#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "tcpserverconnection.h"

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
    QStandardItemModel* bid_model;
    QStandardItemModel* case_model;
    QStandardItemModel* case_assigned_model;
    int bid_page;
    int case_page;
    int case_assigned_page;
    int bid_read_page;
    int case_add_page;
    int case_update_page;
    int case_read_page;
    QString host;
    QString username;
    QString bid_number;
    QString bid_status;
    QString TN_VED;
    QString case_code;
    QString case_rig;
    QString case_item;
    QString case_number;
    QString case_status;
    TCPServerConnection connection;
public:
    explicit StorageWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent = nullptr);
    ~StorageWindow();
    void CheckBidIdWork();
    void FindBidWork();
    void CheckWeightingForm();
    void CheckWeighting();
    void SuggestDistribution();
    void CheckDistribution();
    void Refusal();
    void Reception();
    void ClearBidWorkForm(unsigned short mod);
    void ActivateBidWorkForm(bool flag, unsigned short mod);
    void AssignCase();
    void ReturnCase();
    void BidList();
    void CaseList();
    void NominatedCaseList();
    void CheckBidIdRead();
    void FindBidRead();
    void ChooseBidReadPage();
    void ClearBidReadForm();
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ChooseCaseReadPage();
    void ClearCaseReadForm();
    void CheckCaseAddForm();
    void CheckCaseAddContents();
    void AddCase();
    void ChooseCaseAddPage();
    void ClearCaseAddForm();
    void CheckCaseOptionsUpdate();
    void FindCaseUpdate();
    void CheckCaseUpdateForm();
    void CheckCaseUpdateContents();
    void UpdateCase();
    void ChooseCaseUpdatePage();
    void ClearCaseUpdateForm();
    void ActivateCaseUpdateForm(bool flag);
    void DeleteCaseByOptions();
    void DeleteCaseByBid();
    void closeEvent(QCloseEvent* event) override;
};

#endif // STORAGEWINDOW_H

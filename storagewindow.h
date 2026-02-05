#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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
    QStandardItemModel* case_assigned_model;
public:
    explicit StorageWindow(QWidget *parent = nullptr);
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
    void CheckBidIdRead();
    void FindBidRead();
    void ClearBidReadForm();
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ClearCaseReadForm();
    void CheckCaseAddForm();
    void CheckCaseAddContents();
    void AddCase();
    void ClearCaseAddForm();
    void CheckCaseOptionsUpdate();
    void FindCaseUpdate();
    void CheckCaseUpdateForm();
    void CheckCaseUpdateContents();
    void UpdateCase();
    void ClearCaseUpdateForm();
    void ActivateCaseUpdateForm(bool flag);
    void DeleteCaseByOptions();
    void DeleteCaseByBid();
};

#endif // STORAGEWINDOW_H

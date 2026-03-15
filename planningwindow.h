#ifndef PLANNINGWINDOW_H
#define PLANNINGWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "tcpserverconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlanningWindow;
}
QT_END_NAMESPACE

class PlanningWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::PlanningWindow *ui;
    QStandardItemModel* case_model;
    QStandardItemModel* ship_model;
    int case_page;
    int ship_page;
    int case_read_page;
    QString host;
    QString username;
    QString case_code;
    QString case_rig;
    QString case_item;
    QString case_number;
    QString case_status;
    QString ship_status;
    QString ship_update_imo;
    QString ship_update_status;
    TCPServerConnection connection;
public:
    explicit PlanningWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent = nullptr);
    ~PlanningWindow();
    void CheckCaseOptionsWork();
    void FindCaseWork();
    void SuggestPlan();
    void CheckPlan();
    void Reception();
    void ClearCaseWorkForm(unsigned short mod);
    void ActivateCaseWorkForm(bool flag, unsigned short mod);
    void AssignShip();
    void AssignPosition();
    void CaseList();
    void ShipList();
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ChooseCaseReadPage();
    void ClearCaseReadForm();
    void CheckIMORead();
    void FindShipRead();
    void ClearShipReadForm();
    void CheckShipAddForm();
    void CheckShipAddContents();
    void AddShip();
    void ClearShipAddForm();
    void CheckIMOUpdate();
    void FindShipUpdate();
    void CheckShipUpdateForm();
    void CheckShipUpdateContents();
    void UpdateShip();
    void ClearShipUpdateForm();
    void ActivateShipUpdateForm(bool flag);
    void DeleteShip();
    void closeEvent(QCloseEvent* event) override;
};

#endif // PLANNINGWINDOW_H

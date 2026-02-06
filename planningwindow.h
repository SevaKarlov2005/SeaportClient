#ifndef PLANNINGWINDOW_H
#define PLANNINGWINDOW_H

#include <QMainWindow>

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
public:
    explicit PlanningWindow(QWidget *parent = nullptr);
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
    void CheckCaseOptionsRead();
    void FindCaseRead();
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
};

#endif // PLANNINGWINDOW_H

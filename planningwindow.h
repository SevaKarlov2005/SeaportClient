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
};

#endif // PLANNINGWINDOW_H

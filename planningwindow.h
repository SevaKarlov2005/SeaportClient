#ifndef PLANNINGWINDOW_H
#define PLANNINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlanningWindow;
}

class PlanningWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlanningWindow(QWidget *parent = nullptr);
    ~PlanningWindow();

private:
    Ui::PlanningWindow *ui;
};

#endif // PLANNINGWINDOW_H

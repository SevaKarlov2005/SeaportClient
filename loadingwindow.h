#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoadingWindow;
}
QT_END_NAMESPACE

class LoadingWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::LoadingWindow *ui;
public:
    explicit LoadingWindow(QWidget *parent = nullptr);
    ~LoadingWindow();
    void CheckCaseOptionsWork();
    void FindCaseWork();
    void CheckResult();
    void Reception();
    void ClearCaseWorkForm(unsigned short mod);
    void ActivateCaseWorkForm(bool flag, unsigned short mod);
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ClearCaseReadForm();
    void CheckBidIdRead();
    void FindBidRead();
    void ClearBidReadForm();
};

#endif // LOADINGWINDOW_H

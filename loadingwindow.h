#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "tcpserverconnection.h"

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
    QStandardItemModel* case_model;
    int case_page;
    QString host;
    QString username;
    QString case_code;
    QString case_rig;
    QString case_item;
    QString case_number;
    QString case_status;
    TCPServerConnection connection;
public:
    explicit LoadingWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent = nullptr);
    ~LoadingWindow();
    void CheckCaseOptionsWork();
    void FindCaseWork();
    void CheckResult();
    void Reception();
    void ClearCaseWorkForm(unsigned short mod);
    void ActivateCaseWorkForm(bool flag, unsigned short mod);
    void CaseList();
    void CheckCaseOptionsRead();
    void FindCaseRead();
    void ClearCaseReadForm();
    void CheckBidIdRead();
    void FindBidRead();
    void ClearBidReadForm();
    void closeEvent(QCloseEvent* event) override;
};

#endif // LOADINGWINDOW_H

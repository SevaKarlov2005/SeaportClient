#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "tcpserverconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SearchWindow;
}
QT_END_NAMESPACE

class SearchWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::SearchWindow *ui;
    QStandardItemModel* bid_model;
    int bid_page;
    int bid_read_page;
    QString host;
    QString username;
    QString bid_number;
    QString bid_status;
    TCPServerConnection connection;
public:
    explicit SearchWindow(QString surname, QString name, QString patronym, QString username, QWidget *parent = nullptr);
    ~SearchWindow();
    void CheckBidIdWork();
    void FindBidWork();
    void CheckBidConditionsWork();
    void CheckBidFulfillmentWork();
    void Refusal();
    void Reception();
    void ClearBidWorkForm(unsigned short mod);
    void ActivateBidWorkForm(bool flag, unsigned short mod);
    void BidList();
    void CheckBidIdRead();
    void FindBidRead();
    void ChooseBidReadPage();
    void ClearBidReadForm();
    void closeEvent(QCloseEvent* event) override;
};

#endif // SEARCHWINDOW_H

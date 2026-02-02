#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>

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
public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();
    void CheckBidIdWork();
    void FindBidWork();
    void CheckBidConditionsWork();
    void CheckBidFulfillmentWork();
    void Refusal();
    void Reception();
    void ClearBidWorkForm(unsigned short mod);
    void ActivateBidWorkForm(bool flag, unsigned short mod);
    void CheckBidIdRead();
    void FindBidRead();
    void ClearBidReadForm();
};

#endif // SEARCHWINDOW_H

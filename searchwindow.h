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
};

#endif // SEARCHWINDOW_H

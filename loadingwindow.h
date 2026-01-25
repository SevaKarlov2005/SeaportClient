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
};

#endif // LOADINGWINDOW_H

#include "authorizationwindow.h"
#include "searchwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchWindow w;
    w.show();
    return a.exec();
}

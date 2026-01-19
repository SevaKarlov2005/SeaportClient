#include "authorizationwindow.h"
#include "searchwindow.h"
#include "loadingwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingWindow w;
    w.show();
    return a.exec();
}

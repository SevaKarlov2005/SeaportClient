#include "authorizationwindow.h"
#include "searchwindow.h"
#include "loadingwindow.h"
#include "storagewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StorageWindow w;
    w.show();
    return a.exec();
}

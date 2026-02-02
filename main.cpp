#include "authorizationwindow.h"
#include "searchwindow.h"
#include "loadingwindow.h"
#include "storagewindow.h"
#include "planningwindow.h"
#include "administrationwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchWindow w;
    w.show();
    return a.exec();
}

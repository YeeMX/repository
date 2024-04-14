#include "mymainwindow.h"
#include "welcomewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand((int)time(0));
    QApplication a(argc, argv);
    WelcomeWindow w;
    w.show();
    return a.exec();
}

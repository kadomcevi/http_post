#include <QApplication>
#include "httppostwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttppostWindow w;
    w.show();
    
    return a.exec();
}

#include <QtGui/QApplication>
#include "serveur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serveur w;
    w.show();
    
    return a.exec();
}

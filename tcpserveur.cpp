#include "tcpserveur.h"

TCPServeur::TCPServeur(QObject *parent) :
    QTcpServer(parent)
{

}

void TCPServeur::incomingConnection(int socketDescriptor)
{
    ThreadServeur *thServeur =new ThreadServeur(socketDescriptor);
    connect(thServeur,SIGNAL(siRecoieConnection(QString)),this,SLOT(slRecoieConnection(QString)));
    connect(thServeur,SIGNAL(siTermineConnection(QString)),this,SLOT(slTermineConnection(QString)));
    thServeur->start();
}

void TCPServeur::slRecoieConnection(QString ba)
{
    emit(siRecoieNom(ba));
}

void TCPServeur::slTermineConnection(QString ba)
{
    emit(siFin(ba));
}

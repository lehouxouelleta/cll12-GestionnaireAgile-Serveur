#include "tcpserveur.h"

TCPServeur::TCPServeur(QObject *parent) :
    QTcpServer(parent)
{

}

void TCPServeur::incomingConnection(int socketDescriptor)
{
    ThreadServeur *thServeur =new ThreadServeur(socketDescriptor);
    connect(thServeur,SIGNAL(siRecoieConnection(QByteArray)),this,SLOT(slRecoieConnection(QByteArray)));
    thServeur->start();
}

void TCPServeur::slRecoieConnection(QByteArray ba)
{
    emit(siRecoieNom(ba));
}

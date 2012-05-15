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
    connect(this,SIGNAL(siNouvelleTache(QStringList)),thServeur,SLOT(slNouvelleTache(QStringList)));
    connect(thServeur,SIGNAL(siTacheTerminee(QString,QString)),this,SLOT(slTacheTerminee(QString,QString)));
    connect(this,SIGNAL(siDeconnection()),thServeur,SLOT(slDeconnection()));
    connect(thServeur,SIGNAL(siFermeture()),this,SLOT(slFermeture()));
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

void TCPServeur::slEnvoieTache(QStringList qsl)
{
    emit(siNouvelleTache(qsl));
}

void TCPServeur::slTacheTerminee(QString str,QString nom)
{
    emit(siEnleverTache(str,nom));
}

void TCPServeur::slDeconnecter()
{
    emit(siDeconnection());
}

void TCPServeur::slFermeture()
{
    this->close();
    emit(siFermer());
}

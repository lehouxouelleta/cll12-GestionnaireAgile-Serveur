#ifndef TCPSERVEUR_H
#define TCPSERVEUR_H

#include <QTcpServer>
#include "threadserveur.h"

class TCPServeur : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServeur(QObject *parent = 0);
    void incomingConnection(int socketDescriptor);
    
signals:
    void siRecoieNom(QString);
    void siFin(QString);
    void siNouvelleTache(QStringList);
    void siEnleverTache(QString,QString);
    void siDeconnection();
    void siFermer();
    
public slots:
    void slRecoieConnection(QString ba);
    void slTermineConnection(QString ba);
    void slEnvoieTache(QStringList);
    void slTacheTerminee(QString, QString nom);
    void slDeconnecter();
    void slFermeture();
    
};

#endif // TCPSERVEUR_H

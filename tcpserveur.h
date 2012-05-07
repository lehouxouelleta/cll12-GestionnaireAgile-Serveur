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
    
public slots:
    void slRecoieConnection(QString ba);
    void slTermineConnection(QString ba);
    
};

#endif // TCPSERVEUR_H

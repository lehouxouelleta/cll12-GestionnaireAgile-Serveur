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
    void siRecoieNom(QByteArray);
    
public slots:
    void slRecoieConnection(QByteArray ba);
    
};

#endif // TCPSERVEUR_H

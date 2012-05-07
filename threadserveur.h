#ifndef THREADSERVEUR_H
#define THREADSERVEUR_H

#include <QThread>
#include "serveur.h"

class ThreadServeur : public QThread
{
    Q_OBJECT
public:
    explicit ThreadServeur(int Descriptor = 0);
    QTcpSocket *socket;
    int m_socketDescriptor;
    void run();
    
signals:
    void siRecoieConnection(QString);
    void siTermineConnection(QString);
    
public slots:
    
};

#endif // THREADSERVEUR_H

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
    int codeServeur;
    QString codeClient;
    QByteArray baTaches;
    void run();
    
signals:
    void siRecoieConnection(QString);
    void siTermineConnection(QString);
    void siTacheTerminee(QString);
    
public slots:
    void slNouvelleTache(QStringList);
    
};

#endif // THREADSERVEUR_H

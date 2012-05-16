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
    QString nomClient;
    QString codeClient;
    QByteArray baTaches;
    bool termine;
    QString valide;
    void run();
    
signals:
    void siRecoieConnection(QString);
    void siTermineConnection(QString);
    void siTacheTerminee(QString,QString);
    void siFermeture();
    void siPrendreTache(QString,QString);
    void siAbandon(QString,QString);
    
public slots:
    void slNouvelleTache(QStringList);
    void slDeconnection();
    void slRepondu(QString);
    
};

#endif // THREADSERVEUR_H

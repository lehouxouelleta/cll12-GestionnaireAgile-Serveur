#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>
#include "tcpserveur.h"
#include "threadserveur.h"
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class serveur;
}

class serveur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit serveur(QWidget *parent = 0);
    ~serveur();
    
private slots:
    void on_btnCreerTache_clicked();

    void on_btnConnecter_clicked();
    void slRecoitNom(QByteArray ba);

private:
    Ui::serveur *ui;
};

#endif // SERVEUR_H

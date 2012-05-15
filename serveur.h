#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>
#include "tcpserveur.h"
#include "threadserveur.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QTimer>

namespace Ui {
class serveur;
}

class serveur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit serveur(QWidget *parent = 0);
    ~serveur();
    QStringList Taches;
    QTimer *ti;
    
private slots:
    void on_btnCreerTache_clicked();

    void on_btnConnecter_clicked();
    void slRecoitNom(QString ba);
    void slFin(QString ba);
    void slEnleverTache(QString);

    void on_btnDeconnecter_clicked();
    void update();

signals:
    void siEnvoieTaches(QStringList);
    void timeout();

private:
    Ui::serveur *ui;
};

#endif // SERVEUR_H

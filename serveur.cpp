#include "serveur.h"
#include "ui_serveur.h"

serveur::serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serveur)
{
    ui->setupUi(this);
    ui->twEmployes->resizeColumnsToContents();
    ui->twTaches->resizeColumnsToContents();
    ti=new QTimer(this);
    connect(ti, SIGNAL(timeout()), this, SLOT(update()));
    ti->setInterval(1000);
    ti->start();
}

serveur::~serveur()
{
    delete ui;
}

void serveur::on_btnCreerTache_clicked()
{
    Taches.append(QString(Taches.size()+1)+';'+ui->txtTitre->text()+';'+ui->txtDescription->text()+';'+ui->txtDifficulte->text()+';'+ui->txtTemps->text()+';'+ui->txtBonus->text()+';'+"0"+'%');
    ui->twTaches->setColumnCount(8);
    ui->twTaches->setRowCount(ui->twTaches->rowCount()+1);
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,0,new QTableWidgetItem(ui->txtTitre->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,1,new QTableWidgetItem(ui->txtDescription->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,2,new QTableWidgetItem("0"));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,3,new QTableWidgetItem(ui->txtDifficulte->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,4,new QTableWidgetItem(ui->txtTemps->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,5,new QTableWidgetItem(ui->txtBonus->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,6,new QTableWidgetItem("0"));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,7,new QTableWidgetItem("aucun"));
    ui->twTaches->resizeColumnsToContents();
    emit(siEnvoieTaches(Taches));
}

void serveur::on_btnConnecter_clicked()
{
    TCPServeur *socketServeur=new TCPServeur;
    connect(socketServeur,SIGNAL(siRecoieNom(QString)),this,SLOT(slRecoitNom(QString)));
    connect(socketServeur,SIGNAL(siFin(QString)),this,SLOT(slFin(QString)));
    connect(this,SIGNAL(siEnvoieTaches(QStringList)),socketServeur,SLOT(slEnvoieTache(QStringList)));
    connect(socketServeur,SIGNAL(siEnleverTache(QString,QString)),this,SLOT(slEnleverTache(QString,QString)));
    connect(this,SIGNAL(siDeconnecter()),socketServeur,SLOT(slDeconnecter()));
    connect(socketServeur,SIGNAL(siFermer()),this,SLOT(slFermer()));
    connect(socketServeur,SIGNAL(siTachePrise(QString,QString)),this,SLOT(slTachePrise(QString,QString)));
    connect(socketServeur,SIGNAL(siAbandonnee(QString,QString)),this,SLOT(slAbandonnee(QString,QString)));
    connect(this,SIGNAL(siReponse(QString)),socketServeur,SLOT(slReponse(QString)));
    socketServeur->listen(QHostAddress::Any, 60123);

    ui->btnDeconnecter->setEnabled(true);
    ui->btnConnecter->setEnabled(false);
}

void serveur::slRecoitNom(QString ba)
{
    ui->twEmployes->setColumnCount(4);
    ui->twEmployes->setRowCount(ui->twEmployes->rowCount()+1);
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,0,new QTableWidgetItem(ba));
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,1,new QTableWidgetItem("0"));
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,2,new QTableWidgetItem("0"));
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,3,new QTableWidgetItem("0"));
    ui->twEmployes->resizeColumnsToContents();
    emit(siEnvoieTaches(Taches));
}

void serveur::slFin(QString ba)
{
    QTableWidgetItem *qti;
    for(int i=0;i<ui->twEmployes->rowCount();i++)
    {
        qti=(ui->twEmployes->item(i,0));
        if(qti->text()==ba)
        {
            ui->twEmployes->removeRow(i);
        }
    }
    for(int i=0;i<ui->twTaches->rowCount();i++)
    {
        qti=(ui->twTaches->item(i,7));
        if(qti->text()==ba)
        {
            ui->twTaches->setItem(i,6,new QTableWidgetItem(QString::number(0)));
            ui->twTaches->setItem(i,7,new QTableWidgetItem(QString("aucun")));

            QString strTache=Taches.at(i);
            strTache.replace(strTache.length()-2,1,"0");
            Taches.replace(i,strTache);
        }
    }
    emit(siEnvoieTaches(Taches));
}

void serveur::slEnleverTache(QString str,QString nom)
{
    QByteArray i=str.toLocal8Bit();
    ui->twTaches->removeRow(i[0]);
    Taches.removeAt(i[0]);

    QTableWidgetItem *qti;
    for(int i=0;i<ui->twEmployes->rowCount();i++)
    {
        qti=(ui->twEmployes->item(i,0));
        if(qti->text()==nom)
        {
            ui->twEmployes->setItem(i,3,new QTableWidgetItem(QString::number(ui->twEmployes->item(i,3)->text().toInt()+1)));
        }
    }

    emit(siEnvoieTaches(Taches));
}

void serveur::on_btnDeconnecter_clicked()
{
    emit(siDeconnecter());
    ui->btnConnecter->setEnabled(true);
    ui->btnDeconnecter->setEnabled(false);
}

void serveur::update()
{
    for(int i=0;i<ui->twEmployes->rowCount();i++)
    {
        ui->twEmployes->setItem(i,1,new QTableWidgetItem(QString::number(ui->twEmployes->item(i,1)->text().toInt()+1)));
    }
    for(int i=0;i<ui->twTaches->rowCount();i++)
    {
        ui->twTaches->setItem(i,2,new QTableWidgetItem(QString::number(ui->twTaches->item(i,2)->text().toInt()+1)));
    }
}

void serveur::slFermer()
{

}

void serveur::slTachePrise(QString tache, QString nom)
{
    QTableWidgetItem *qti;
    for(int i=0;i<ui->twEmployes->rowCount();i++)
    {
        qti=(ui->twEmployes->item(i,0));
        if(qti->text()==nom)
        {
            ui->twEmployes->setItem(i,2,new QTableWidgetItem(QString::number(1)));
        }
    }

    QString strTache=Taches.at(tache.toInt());
    strTache.replace(strTache.length()-2,1,"1");
    Taches.replace(tache.toInt(),strTache);

    ui->twTaches->setItem(tache.toInt(),6,new QTableWidgetItem(QString::number(1)));
    ui->twTaches->setItem(tache.toInt(),7,new QTableWidgetItem(QString(nom)));

    emit(siEnvoieTaches(Taches));
}

void serveur::slAbandonnee(QString tache, QString nom)
{
    QTableWidgetItem *qti;
    for(int i=0;i<ui->twEmployes->rowCount();i++)
    {
        qti=(ui->twEmployes->item(i,0));
        if(qti->text()==nom)
        {
            ui->twEmployes->setItem(i,2,new QTableWidgetItem(QString::number(0)));
        }
    }

    QString strTache=Taches.at(tache.toInt());
    strTache.replace(strTache.length()-2,1,"0");
    Taches.replace(tache.toInt(),strTache);

    ui->twTaches->setItem(tache.toInt(),6,new QTableWidgetItem(QString::number(0)));
    ui->twTaches->setItem(tache.toInt(),7,new QTableWidgetItem(QString("aucun")));

    emit(siEnvoieTaches(Taches));
}

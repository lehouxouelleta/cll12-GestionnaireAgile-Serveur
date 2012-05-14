#include "serveur.h"
#include "ui_serveur.h"

serveur::serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serveur)
{
    ui->setupUi(this);
    ui->twEmployes->resizeColumnsToContents();
    ui->twTaches->resizeColumnsToContents();

}

serveur::~serveur()
{
    delete ui;
}

void serveur::on_btnCreerTache_clicked()
{
    //numero;titre;description;difficulte;temps;bonus
    Taches.append(QString(Taches.size()+1)+';'+ui->txtTitre->text()+';'+ui->txtDescription->text()+';'+ui->txtDifficulte->text()+';'+ui->txtTemps->text()+';'+ui->txtBonus->text()+'%');
    ui->twTaches->setColumnCount(6);
    ui->twTaches->setRowCount(ui->twTaches->rowCount()+1);
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,0,new QTableWidgetItem(ui->txtTitre->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,1,new QTableWidgetItem(ui->txtDescription->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,3,new QTableWidgetItem(ui->txtDifficulte->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,4,new QTableWidgetItem(ui->txtTemps->text()));
    ui->twTaches->setItem(ui->twTaches->rowCount()-1,5,new QTableWidgetItem(ui->txtBonus->text()));

    ui->twTaches->resizeColumnsToContents();
    emit(siEnvoieTaches(Taches));
}

void serveur::on_btnConnecter_clicked()
{
    TCPServeur *socketServeur=new TCPServeur;
    connect(socketServeur,SIGNAL(siRecoieNom(QString)),this,SLOT(slRecoitNom(QString)));
    connect(socketServeur,SIGNAL(siFin(QString)),this,SLOT(slFin(QString)));
    connect(this,SIGNAL(siEnvoieTaches(QStringList)),socketServeur,SLOT(slEnvoieTache(QStringList)));
    connect(socketServeur,SIGNAL(siEnleverTache(QString)),this,SLOT(slEnleverTache(QString)));
    socketServeur->listen(QHostAddress::Any, 60123);
}

void serveur::slRecoitNom(QString ba)
{
    ui->twEmployes->setColumnCount(2);
    ui->twEmployes->setRowCount(ui->twEmployes->rowCount()+1);
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,0,new QTableWidgetItem(ba));
    ui->twEmployes->resizeColumnsToContents();

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
}

void serveur::slEnleverTache(QString str)
{
    int i=str.toInt();
    ui->twTaches->removeRow(i+1);
    //ui->twTaches->setRowCount(ui->twTaches->rowCount()-1);
    Taches.removeAt(i+1);
    emit(siEnvoieTaches(Taches));
}

void serveur::on_btnDeconnecter_clicked()
{

}

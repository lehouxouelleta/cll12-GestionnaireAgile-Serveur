#include "serveur.h"
#include "ui_serveur.h"

serveur::serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serveur)
{
    ui->setupUi(this);
    ui->twEmployes->resizeColumnsToContents();
}

serveur::~serveur()
{
    delete ui;
}

void serveur::on_btnCreerTache_clicked()
{

}

void serveur::on_btnConnecter_clicked()
{
    TCPServeur *socketServeur=new TCPServeur;
    connect(socketServeur,SIGNAL(siRecoieNom(QByteArray)),this,SLOT(slRecoitNom(QByteArray)));

    socketServeur->listen(QHostAddress::Any, 60123);
}

void serveur::slRecoitNom(QByteArray ba)
{
    QString employe(ba);
    ui->twEmployes->setColumnCount(2);
    ui->twEmployes->setRowCount(ui->twEmployes->rowCount()+1);
    ui->twEmployes->setItem(ui->twEmployes->rowCount()-1,0,new QTableWidgetItem(employe));
    ui->twEmployes->resizeColumnsToContents();
}

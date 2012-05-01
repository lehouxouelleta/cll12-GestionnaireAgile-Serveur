#include "serveur.h"
#include "ui_serveur.h"

serveur::serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serveur)
{
    ui->setupUi(this);
}

serveur::~serveur()
{
    delete ui;
}

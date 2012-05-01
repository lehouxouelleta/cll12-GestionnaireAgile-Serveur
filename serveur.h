#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>

namespace Ui {
class serveur;
}

class serveur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit serveur(QWidget *parent = 0);
    ~serveur();
    
private:
    Ui::serveur *ui;
};

#endif // SERVEUR_H

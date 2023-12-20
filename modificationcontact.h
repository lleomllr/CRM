#ifndef MODIFICATIONCONTACT_H
#define MODIFICATIONCONTACT_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include "popup.h"

namespace Ui {
class ModificationContact;
}

class ModificationContact : public QDialog
{
    Q_OBJECT

public:
    explicit ModificationContact(QWidget *parent = nullptr);
    ~ModificationContact();
    QFileDialog *fileDialog;
    PopUp *pop;

private:
    Ui::ModificationContact *ui;
    QString nom;
    QString prenom;

private slots:
    void remplirFormulaire(QString nom,QString prenom,QString entreprise,QString mail,QString photo, QString telephone);
    void on_ConfirmerModificationContact_clicked();

    void on_AnnulerModificationContact_clicked();

    void on_changementPhoto_clicked();

signals:
     void modifierContact(QString,QString,QString,QString,QString,QString);
     void majListe();
     void afficheMessage(QString);
};

#endif // MODIFICATIONCONTACT_H

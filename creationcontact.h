#ifndef CREATIONCONTACT_H
#define CREATIONCONTACT_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>
#include "contact.h"
#include "popup.h"


/**
 * @brief La classe CreationContact possède une interface et permet à l'utilisateur de créer un contact en remplissant ses informations.
 */
namespace Ui {
class CreationContact;
}

class CreationContact : public QDialog
{
    Q_OBJECT

public:
    explicit CreationContact(QWidget *parent = nullptr);
    ~CreationContact();
    Ui::CreationContact *ui;
    QFileDialog *fileDialog;
    PopUp *pop;

signals:
    void envoieContact(Contact* c);
    void actualiserContacts();
    void afficheMessage(QString);

private slots:

    void on_BoutonAnnulerCreationContact_clicked();
    void slotEffacerFormulaire();
    void on_BoutonConfirmerCreationContact_clicked();

    void on_BoutonSelectionPhoto_clicked();

private:

};

#endif // CREATIONCONTACT_H

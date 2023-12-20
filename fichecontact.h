#ifndef FICHECONTACT_H
#define FICHECONTACT_H

#include <QDialog>
#include <QString>
#include <QTableWidgetItem>
#include "modificationcontact.h"
#include "gestioninteraction.h"
#include "contact.h"
#include "gestionbd.h"
#include "ajoutinteraction.h"
#include "ficheinteraction.h"
#include "gestiontodo.h"
#include "popup.h"


/**
 * @brief La classe FicheContact possède une interface et permet d'afficher toutes les informations d'un contact ainsi que ses interactions.
 */

namespace Ui {
class FicheContact;
}

class FicheContact : public QDialog
{
    Q_OBJECT

public:
    explicit FicheContact(GestionBD* gbd,QWidget *parent = nullptr);
    ~FicheContact();
    ModificationContact *modifierC;
    GestionInteraction* gI;
    ajoutInteraction* ajouterI;
    FicheInteraction* fichI;
    GestionBD* BD;
    PopUp *pop;
    void ConversionStringDate(std::string &texte, tm* date);

private:
    Ui::FicheContact *ui;
    QString nom;
    QString prenom;
    QString entreprise;
    QString photo;
    QString telephone;
    QString mail;


private slots:
    void remplirFiche(GestionBD* gbd,QString nom,QString prenom,QString entreprise,QString mail,QString photo, QString telephone);
    void on_BoutonModifierContact_clicked();
    void slotmodifierContact(QString,QString,QString,QString,QString,QString);
    //void remplirTableWidget(vector<Interaction*>* liste);
    void mettreAJourFiche(QString qnom,QString qprenom,QString qentreprise,QString qmail,QString qphoto, QString qtelephone);
    void creerInteraction(QString contenu);
    void on_pushButton_clicked();
    void actualiserInteractions();
    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_BoutonRechercheInteraction_clicked();

    void on_BoutonSuppInteraction_clicked();

    void on_tableWidget_cellClicked(int row, int column);

signals:
    void remplirModifContact(QString nom,QString prenom,QString entreprise,QString mail,QString photo,QString telephone);
    void signalmodifierContact(QString,QString,QString,QString,QString,QString,QString,QString);
    void chargerListe(Contact*);
    void AfficherFicheInterac(QString date, QString interaction);
    void envoieListeTodo(std::vector<Todo*> *liste);
    void rechercheByDate(std::string date);
    void actualiserRecherche();
    void effacerContenu();
    void supprimerInteraction(Interaction* i);
    void afficheMessage(QString);

};
#endif // FICHECONTACT_H

#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H

#include "contact.h"
#include <vector>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include "gestionbd.h"
/**
 * @brief La classe GestionContact comporte une série de méthode qui permettent de manipuler un contact ou une liste de contacts.
 */
class GestionContact : public QObject
{
    Q_OBJECT

    private:
        GestionBD* bd;
        std::vector<Contact*> listeContacts;
        QSqlDatabase db;
        bool dbOuverte;
        void RemplirListeContacts();
        void modifierNom(Contact*, std::string NewNom);
        void modifierPrenom(Contact*, std::string NewPrenom);
        void modifierEntrep(Contact*, std::string NewEntreprise);
        void modifierMail(Contact*, std::string NewMail);
        void modifierTel(Contact*, std::string NewTel);
        void modifierPhoto(Contact*, std::string NewUri);

    public:
        explicit GestionContact(GestionBD* bd, QObject *parent = nullptr);
        ~GestionContact();
        void ajouterContactListe(Contact *c);
        void supprimerContactListe(const std::string nom, const std::string prenom);
        Contact* getContact(std::string nom, std::string prenom);
        int getNombreContact();
        void modifierContact(std::string OldNom, std::string OldPrenom,std::string NewNom, std::string NewPrenom,std::string NewEntreprise,std::string NewMail,std::string NewTel,std::string NewUri);
        std::vector<Contact*>* getListeContacts();


    private slots:
        void ajouterContact(Contact* c);
        void DemandeEnvoyerContact();
        void supprimerContact(QString nom, QString prenom);
        void slotModifierContact(QString,QString,QString,QString,QString,QString,QString,QString);
        void rechercheCritere(QString critere, QString recherche);
        void rechercheEntreDeuxDates(int jourDebut,int moisDebut,int anneeDebut,int jourFin,int moisFin,int anneeFin);
        void DemandeListeJson();

    signals:
        void EnvoyerContact(vector<Contact*>*);
        void EnvoyerListeJson(vector<Contact*>*);
};


#endif

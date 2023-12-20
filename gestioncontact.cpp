#include "gestioncontact.h"
#include "gestionbd.h"
#include <string.h>
#include <iostream>


GestionContact::GestionContact(GestionBD* gbd, QObject *parent): QObject(parent)
{
    bd=gbd;
    dbOuverte = false;
    bd->RemplirListeContacts(&listeContacts);
}

GestionContact::~GestionContact()
{
}

void GestionContact::ajouterContact(Contact* c)
{
    ajouterContactListe(c);
}

void GestionContact::DemandeEnvoyerContact()
{
    qDebug() << "Demande recue";
    vector<Contact*>* liste = getListeContacts();
    emit EnvoyerContact(liste);
}

void GestionContact::DemandeListeJson()
{
    vector<Contact*>* liste = getListeContacts();
    emit EnvoyerListeJson(liste);
}
/**
 * @brief GestionContact::ajouterContact Cette méthode permet d'ajouter un contact à une liste de contacts. Les deux sont donnés en paramètre.
 * @param listeContacts Liste de contacts à laquelle on souhaite ajouter un contact.
 * @param c Contact que l'on souhaite ajouter.
 */

void GestionContact::ajouterContactListe(Contact* c)
{
    listeContacts.push_back(c);
    bd->ajouterContactBD(c);
}

void GestionContact::rechercheCritere(QString critere, QString recherche)
{
    bd->RechercheBy(critere, recherche, &listeContacts);
    vector<Contact*>* liste = getListeContacts();
    emit EnvoyerContact( &listeContacts);
}

/**
 * @brief GestionContact::supprimerContact Cette méthode permet de supprimer un contact à une liste de contacts. Les deux sont donnés en paramètre.
 * @param listeContacts Liste de contacts à laquelle on souhaite supprimer un contact.
 * @param c  Contact que l'on souhaite supprimer.
 */

void GestionContact::supprimerContactListe(const std::string nom, const std::string prenom)
{
    Contact* c=getContact(nom, prenom);
    auto itContact = listeContacts.begin();
    bool found = false;
    while((itContact!=listeContacts.end()) && (found==false)){
        if(((*itContact)->nom == c->nom) && ((*itContact)->prenom == c->prenom)){
            found = true;
            bd->supprimerContactBD(*itContact);
            listeContacts.erase(itContact);
        }
        else ++itContact;
    }
}

void GestionContact::supprimerContact(QString nom, QString prenom)
{
    supprimerContactListe(nom.toStdString(),prenom.toStdString());
}


void GestionContact::slotModifierContact(QString oldnom,QString oldprenom,QString nom,QString prenom,QString entreprise,QString mail,QString uri,QString telephone)
{
    modifierContact(oldnom.toStdString(),oldprenom.toStdString(),nom.toStdString(),prenom.toStdString(),entreprise.toStdString(),mail.toStdString(),telephone.toStdString(),uri.toStdString());
}
/**
 * @brief GestionContact::getContact Permet de récupérer le contact correspond au nom et prénom donnés en paramètre dans la liste donnée en paramètre.
 * @param listeContacts Liste dans laquelle on cherche le contact.
 * @param nom Nom du contact que l'on cherche.
 * @param prenom Prénom du contact que l'on cherche.
 * @return Contact de la lsite qui a le nom et le prénom passés en paramètre.
 */

Contact* GestionContact::getContact(const std::string nom, const std::string prenom)
{
    auto it = listeContacts.begin();
    bool found = false;
    while((it!=listeContacts.end()) && (found==false))
    {
        if(((*it)->nom == nom) && ((*it)->prenom == prenom))
        {
            found = true;
            return *it;
        }

        else
            ++it;
    }
    perror("Pas de contact trouvé");
}

int GestionContact::getNombreContact()
{
    return listeContacts.size();
}

void GestionContact::modifierNom(Contact* c, std::string NewNom){c->setNom(NewNom);}
void GestionContact::modifierPrenom(Contact* c, std::string NewPrenom){c->setPrenom(NewPrenom);}
void GestionContact::modifierEntrep(Contact* c, std::string NewEntreprise){c->setEntreprise(NewEntreprise);}
void GestionContact::modifierMail(Contact* c, std::string NewMail){c->setMail(NewMail);}
void GestionContact::modifierTel(Contact* c, std::string NewTel){c->setTelephone(NewTel);}
void GestionContact::modifierPhoto(Contact* c, std::string NewUri){c->setUriPhoto(NewUri);}

void GestionContact::modifierContact(std::string OldNom, std::string OldPrenom,std::string NewNom, std::string NewPrenom,std::string NewEntreprise,std::string NewMail,std::string NewTel,std::string NewUri)
{
    Contact* c= this->getContact(OldNom, OldPrenom);
    modifierNom(c, NewNom);
    modifierPrenom(c, NewPrenom);
    modifierEntrep(c, NewEntreprise);
    modifierMail(c, NewMail);
    modifierTel(c, NewTel);
    modifierPhoto(c, NewUri);

    bd->modifierContact(OldNom,OldPrenom,NewNom,NewPrenom,NewEntreprise,NewMail,NewTel,NewUri);
}

std::vector<Contact*>* GestionContact::getListeContacts()
{
    return &listeContacts;
}

void GestionContact::rechercheEntreDeuxDates(int jourDebut,int moisDebut,int anneeDebut,int jourFin,int moisFin,int anneeFin)
{
    bd->RemplirListeContacts(&listeContacts);
    auto it = listeContacts.begin();
    while(it!=listeContacts.end())
    {
        if((*it)->getDate()->tm_year<anneeDebut-1900)
            listeContacts.erase(it);
        else
            if((*it)->getDate()->tm_mon<moisDebut-1)
                listeContacts.erase(it);
            else
                if((*it)->getDate()->tm_mday<jourDebut)
                    listeContacts.erase(it);
                else
                    ++it;
    }

    auto itBis = listeContacts.begin();
    while(itBis!=listeContacts.end())
    {
        if((*itBis)->getDate()->tm_year>anneeFin-1900)
            listeContacts.erase(itBis);
        else
            if((*itBis)->getDate()->tm_mon>moisFin-1)
                listeContacts.erase(itBis);
            else
                if((*itBis)->getDate()->tm_mday>jourFin)
                    listeContacts.erase(itBis);
                else
                    ++itBis;
    }


    emit EnvoyerContact(&listeContacts);
}

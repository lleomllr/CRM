#include "contact.h"
#include "interaction.h"
#include <string>

/**
 * @brief Contact::Contact Constructeur de la classe Contact. Le constructeur affecte la date courante à l'attribut dateMAJ de la classe.
 * @param n Nom du contact
 * @param p Prénom du contact
 * @param m Mail du contact
 * @param e Nom de l'entreprise du contact
 * @param u Uri de la photo du contact
 * @param tel Numéro de téléphone du contact
 */
Contact::Contact(std::string n, std::string p, std::string m, std::string e, std::string u, std::string tel)
{
    setNom(n);
    setPrenom(p);
    setMail(m);
    setEntreprise(e);
    setUriPhoto(u);
    setTelephone(tel);
    time_t tn = time(0);
    dateCreation= localtime(&tn);
}

/**
 * @brief Contact::Contact Constructeur de la classe Contact. La date est passée en paramètre.
 * @param n Nom du contact
 * @param p Prénom du contact
 * @param m Mail du contact
 * @param e Nom de l'entreprise du contact
 * @param u Uri de la photo du contact
 * @param tel Numéro de téléphone du contact
 * @param jour Jour de la date
 * @param mois Mois de la date
 * @param annee Annee de la date
 */
Contact::Contact(std::string n, std::string p, std::string m, std::string e, std::string u, std::string tel, int jour, int mois, int annee)
{
    setNom(n);
    setPrenom(p);
    setMail(m);
    setEntreprise(e);
    setUriPhoto(u);
    setTelephone(tel);

    dateCreation = new tm();
    std::cout << "Ancienne date : "<< dateCreation->tm_mday << std::endl;
    dateCreation->tm_mday=jour;
    std::cout << "Nouvelle date : "<< dateCreation->tm_mday << std::endl;
    dateCreation->tm_mon=mois;
    dateCreation->tm_year=annee;
}

/**
 * @brief Contact::ajoutInteraction Le contact possède une liste d'interactions. Cette méthode permet d'ajouter une interaction à cette liste.
 * @param interaction Interaction qui sera ajouté à la liste d'interactions.
 */
/*void Contact::ajoutInteraction(const Interaction* interaction) {
        listeInteractions.push_back(interaction);
    }*/

const std::string Contact::getPrenom(){return prenom;}
const std::string Contact::getNom(){return nom;}
const std::string Contact::getEntreprise(){return entreprise;}
const std::string Contact::getTelephone(){return telephone;}
const std::string Contact::getMail(){return mail;}
const std::string Contact::getPhoto(){return uriPhoto;}
const tm* Contact::getDate(){return dateCreation;}

/**
 * @brief Contact::setMail Cette méthode vérifie que le mail est conforme.
 * @param mail Mail que l'on veut associer au contact.
 */
void Contact::setMail(const std::string& mail){
    if(mail.length() == 0 && !mail.find('@') && !mail.find('.')){
        throw std::invalid_argument("erreur");
    }
    else{
        this->mail = mail;
    }
}

void Contact::setNom(std::string n){nom = n;}
void Contact::setPrenom(std::string p){prenom = p;}
void Contact::setEntreprise(std::string e){entreprise = e;}
void Contact::setUriPhoto(std::string u){uriPhoto = u;}
void Contact::setTelephone(std::string t){telephone =t;}

/**
 * @brief operator << Surcharge de l'opérateur << afin d'afficher un contact sous la forme "Nom Prénom".
 * @param c Contact que l'on veut afficher.
 */
std::ostream &operator<<(std::ostream& o, const Contact& c)
{
    o << c.nom << " " <<c.prenom;
    return o;
}

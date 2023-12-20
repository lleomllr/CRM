#ifndef CONTACT_H
#define CONTACT_H

#include <ctime>
#include <string>
#include "interaction.h"
#include <vector>

using namespace std;

/**
 * @brief La classe Contact contient les coordonnées d'un contact ainsi qu'une liste d'interactions qui lui est propre. Elle contient également un attribut dateMAj qui correspond à la dernière mise à jour effectuée sur le contact.
 */

class Contact
{
    private:
        std::string nom;
        std::string prenom;
        std::string mail;
        std::string entreprise;
        std::string uriPhoto;
        std::string telephone;
        tm * dateCreation;
    public:
        std::vector<Interaction*> listeInteractions;
        //void ajoutInteraction(const Interaction* interaction);

        Contact(std::string n, std::string p, std::string m, std::string e, std::string u, std::string tel);
        Contact(std::string n, std::string p, std::string m, std::string e, std::string u, std::string tel, int jour, int mois, int annee);
        ~Contact(){telephone.clear();listeInteractions.clear();}

        const std::string getPrenom();
        const std::string getNom();
        const std::string getEntreprise();
        const std::string getTelephone();
        const std::string getMail();
        const std::string getPhoto();
        const tm* getDate();


        void setNom(std::string n);
        void setPrenom(std::string p);
        void setEntreprise(std::string e);
        void setUriPhoto(std::string u);
        void setTelephone(std::string t);

        void setMail(const std::string& mail);


        friend std::ostream &operator<<(std::ostream& o, const Contact& c);

    friend class GestionContact;
};



#endif

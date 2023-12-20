#include "interaction.h"
#include <string>
#include <sstream>

/**
 * @brief Interaction::Interaction Constructeur de la classe Interaction. Le constructeur ajoute le contenu passé en paramètre et ajoute la date courant dans l'attribut date.
 * @param c Contenu de l'interaction
 */
Interaction::Interaction(std::string c)
{
    setContenu(c);
    time_t tn = time(0);
    date = localtime(&tn);
}

/**
 * @brief Interaction::Interaction Constructeur de la classe Interaction. Le constructeur ajoute le contenu passé en paramètre et ajoute la date courant dans l'attribut date.
 * @param c Contenu de l'interaction
 * @param jour Jour de la date
 * @param mois Mois de la date
 * @param annee Annee de la date
 */
Interaction::Interaction(std::string c, int jour, int mois, int annee)
{
    setContenu(c);
    time_t tn = time(0);
    date = new tm();
    std::cout << "Ancienne date : "<< date->tm_mday << std::endl;
    date->tm_mday=jour;
    std::cout << "Nouvelle date : "<< date->tm_mday << std::endl;
    date->tm_mon=mois;
    date->tm_year=annee;
}

/**
 * @brief Interaction::Interaction Constructeur de la classe Interaction. Le constructeur ajoute le contenu passé en paramètre et ajoute la date courant dans l'attribut date.
 * @param c Contenu de l'interaction
 * @param newdate Pointeur vers un tm correspondant à la date de l'interaction
 */
Interaction::Interaction(std::string c, tm* newdate)
{
    setContenu(c);
    date = newdate;
}

void Interaction::setContenu(std::string c){contenu = c;}

const std::string Interaction::getContenu(){return contenu;}
const tm* Interaction::getDate(){return date;}

/**
 * @brief operator << Surchage de l'opérateur << pour afficher une Interaction de la forme " Contenu DateCreation : date".
 * @param i Interaction à afficher.
 */
std::ostream& operator<<(std::ostream& os, const Interaction& i){
    std::stringstream sdate;
    sdate << i.date->tm_mday << "-" << (i.date->tm_mon + 1) << "-" << (i.date->tm_year + 1900);
    std::string sdate2 = sdate.str();
    os << i.contenu << " DateCreation : " << sdate2;
    return os;
}

/**
 * @brief Interaction::operator == Surcharge de l'opérateur == pour comparer deux Interactions.
 * @param i Deuxième interaction à comparer.
 * @return true si les interactions sont égales et false sinon.
 */
bool Interaction::operator==( Interaction& i)
{
    if(getContenu() == i.contenu)
    {
        if(getDate() == i.date)
        {
            return true;
        }
    }
    return false;
}

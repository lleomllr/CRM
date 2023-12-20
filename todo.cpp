#include "todo.h"
#include <ctime>
#include <string>
#include <sstream>

/**
 * @brief Todo::Todo Constructeur de la classe Todo. Le constructeur ajoute le contenu passé en paramètre et ajoute la date courant dans l'attribut date.
 * @param c Contenu du todo
 */

Todo::Todo(std::string c)
{
    setContenu(c);
    time_t tn = time(0);
    date = localtime(&tn);
}

/**
 * @brief Todo::Todo Constructeur de la classe Todo qui prend une date en paramètre. Le constructeur ajoute le contenu passé en paramètre et ajoute la date passée en paramètre dans l'attribut date.
 * @param c Contenu du todo
 * @param d Date du todo
 */

Todo::Todo(std::string c,tm* d)
{
    setContenu(c);
    date = d;

}

/**
 * @brief Todo::Todo Constructeur de la classe Todo qui prend une date en paramètre. Le constructeur ajoute le contenu passé en paramètre et ajoute la date passée en paramètre dans l'attribut date.
 * @param c Contenu du todo
 * @param d Date du todo
 * @param jour Jour de la date
 * @param mois Mois de la date
 * @param annee Annee de la date
 */
Todo::Todo(std::string c, int jour, int mois, int annee)
{
    setContenu(c);
    time_t tn = time(0);
    date = new tm();
    date->tm_mday=jour;
    date->tm_mon=mois;
    date->tm_year=annee;
}



void Todo::setContenu(std::string c){contenu = c;}
const std::string Todo::getContenu(){return contenu;}
const tm* Todo::getDate(){return date;}

/**
 * @brief operator << Surcharge de l'opérateur << pour afficher un Todo sous la forme "%Contenu Date: %date".
 * @param t
 */
std::ostream& operator<<(std::ostream& os, const Todo& t){
    std::stringstream sdate;
    sdate << t.date->tm_mday << "-" << (t.date->tm_mon + 1) << "-" << (t.date->tm_year + 1900);
    std::string sdate2 = sdate.str();
    os << t.contenu << " Date : " << sdate2;
    return os;
}

/**
 * @brief Todo::ConversionStringDate permet de changer la date de type tm passée en paramètre par une date passée en paramètre sous la forme d'un string.
 * @param texte Nouvelle date de la forme "JJ-MM-AAAA"
 * @param date Pointeur vers le tm à modifier
 */

void Todo::ConversionStringDate(std::string &texte, tm* date)
{
    sscanf(texte.c_str(), "%d-%d-%d", &date->tm_mday, &date->tm_mon, &date->tm_year);
    date->tm_mon-=1;
    date->tm_year-=1900;
}

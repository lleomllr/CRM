#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "todo.h"

/**
 * @brief La classe Interaction possède un contenu ainsi qu'une date de création. Une interaction est liée à un contact puisqu'elle se situe dans une liste contenue dans la classe Contact.
 */

class Interaction
{
    private:
        std::string contenu;
        tm * date;
    public:
        Interaction(std::string c);
        Interaction(std::string c,int jour, int mois, int annee);
        Interaction(std::string c, tm* newdate);
        std::vector<Todo*> listeTodos;

        void setContenu(std::string c);

        const std::string getContenu();
        const tm* getDate();

        friend std::ostream& operator<<(std::ostream& , const Interaction&);
        bool operator==( Interaction& i);
};


#endif

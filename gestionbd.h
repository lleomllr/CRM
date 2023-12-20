#ifndef GESTIONBD_H
#define GESTIONBD_H

#include <vector>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include "contact.h"
#include "todo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class GestionBD
{

    private:
        QSqlDatabase db;
        bool dbOuverte;

    public:
        GestionBD();
        ~GestionBD();
        bool connectDB();
        void closeDB();
        bool ajouterContactBD(Contact* c);
        bool supprimerContactBD(Contact* c);
        void RemplirListeContacts(std::vector<Contact*> *listeContacts);
        void modifierContact(std::string OldNom, std::string OldPrenom,std::string NewNom, std::string NewPrenom,std::string NewEntreprise,std::string NewMail,std::string NewTel,std::string NewUri);
        void RemplirListeInteractions(std::vector<Interaction*> *listeInteractions, Contact *c);
        bool ajouterInteraction(Interaction* i,Contact* contact);
        void supprimerInteraction(Interaction* i);
        bool ajouterTodo(Todo* t,Interaction* i);
        void supprimerTodo(Todo* t);
        void RemplirListeTodos(std::vector<Todo*>* listeTodos, Interaction* i);
        void RechercheBy(QString critere, QString recherche, std::vector<Contact*> *listeContacts);
        void RechercheInteractionByDate(string date, std::vector<Interaction*> *listeInteractions, Contact *c);
};

#endif // GESTIONBD_H

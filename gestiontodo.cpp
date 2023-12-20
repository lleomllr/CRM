#include "gestiontodo.h"
#include <string.h>
#include <iostream>

GestionTodo::GestionTodo(GestionBD *gbd, std::vector<Todo*> *liste, Interaction* i, QObject *parent): QObject(parent)
{
    bd = gbd;
    listeTodos = liste;
    interaction = i;
    bd->RemplirListeTodos(listeTodos, interaction);
}

GestionTodo::~GestionTodo()
{
}

void GestionTodo::ajouterTodo(Todo* t)
{
    listeTodos->push_back(t);
    bd->ajouterTodo(t,interaction);
}

void GestionTodo::supprimerTodo(Todo* t)
{
    auto it = listeTodos->begin();
    bool found = false;
    while((it!=listeTodos->end()) && (found==false)){
        if(((*it)->getContenu() == t->getContenu()) && ((*it)->getDate() == t->getDate())){
            found = true;
            bd->supprimerTodo(*it);
            listeTodos->erase(it);
        }
        else ++it;
    }
}

std::vector<Todo*>* GestionTodo::getTodos()
{
    return listeTodos;
}

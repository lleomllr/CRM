#include "gestioninteraction.h"
#include <string.h>
#include <iostream>

GestionInteraction::GestionInteraction(GestionBD *gbd, Contact* c, QObject *parent): QObject(parent)
{
    bd = gbd;
    listeInteractions = new std::vector<Interaction*>();
    contact = c;
    //bd->RemplirListeInteractions(listeInteractions, contact);

}

GestionInteraction::GestionInteraction(GestionBD *gbd, QObject *parent): QObject(parent)
{
    bd = gbd;
    listeInteractions = new std::vector<Interaction*>();
    contact = NULL;
}
GestionInteraction::~GestionInteraction()
{
    free(listeInteractions);
}
void GestionInteraction::RemplirListeInteractions(Contact * contact)
{
    bd->RemplirListeInteractions(listeInteractions, contact);
    //qDebug() << QString::fromStdString(listeInteractions->at(0)->getContenu());
}

void GestionInteraction::RechercheByDate(string date,Contact * contact)
{
    bd->RechercheInteractionByDate(date,listeInteractions, contact);
    //qDebug() << QString::fromStdString(listeInteractions->at(0)->getContenu());
}

void GestionInteraction::ajouterInteraction(Interaction* i)
{
    listeInteractions->push_back(i);
    bd->ajouterInteraction(i,contact);
}

void GestionInteraction::supprimerInteraction(Interaction* i)
{
    auto it = listeInteractions->begin();
    bool found = false;
    while((it!=listeInteractions->end()) && (found==false)){
        qDebug()<<QString::fromStdString((*it)->getContenu());
        qDebug()<<QString::fromStdString(i->getContenu());
        if(((*it)->getContenu() == i->getContenu())){
            found = true;
            bd->supprimerInteraction(*it);
            listeInteractions->erase(it);
            qDebug()<<"Interaction supprimée";
        }
        else ++it;
    }
}
/**
 * @brief GestionInteraction::getInteraction Permet de récupérer la i-ème interaction d'une liste d'interactions.
 * @param listeInteractions Liste dans laquelle on recherche l'interaction.
 * @param i Position de l'interaction que l'on recherche.
 * @return i-ème interaction de la liste.
 */
std::vector<Interaction*>* GestionInteraction::getInteractions()
{
    return listeInteractions;
}

void GestionInteraction::slotSupprimerInteraction(Interaction* i)
{
    supprimerInteraction(i);
    emit actualiserListeInteraction();
}

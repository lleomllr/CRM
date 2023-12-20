#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H

#include "interaction.h"
#include <vector>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include "contact.h"
#include "gestionbd.h"

/**
 * @brief La classe GestionInteraction possède des méthodes permettant de manipuler une liste d'interactions. Cette classe sera enrichie par la suite.
 */
class GestionInteraction : public QObject
{
    Q_OBJECT

    private:
        GestionBD* bd;

    public:
        explicit GestionInteraction(GestionBD* bd,Contact* c, QObject *parent = nullptr);
        explicit GestionInteraction(GestionBD *gbd, QObject *parent);
        ~GestionInteraction();
        void RemplirListeInteractions(Contact *c);
        void ajouterInteraction(Interaction* i);
        std::vector<Interaction*>* getInteractions();
        void supprimerInteraction(Interaction* i);
        std::vector<Interaction*> *listeInteractions;
        Contact* contact;
        void RechercheByDate(string date,Contact * contact);

    private slots:
        void slotSupprimerInteraction(Interaction* i);

    signals:
        void actualiserListeInteraction();
};

#endif

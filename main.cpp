#include <iostream>
#include "gestioncontact.h"
#include <list>
#include <unistd.h>
#include "mainwindow.h"
#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GestionBD bd =GestionBD();
    MainWindow w(&bd);
    w.show();
    GestionContact gc = GestionContact(&bd);
    QObject::connect(w.creerC,SIGNAL(envoieContact(Contact*)),&gc,SLOT(ajouterContact(Contact*)));
    QObject::connect(&w,SIGNAL(demanderListeContacts()),&gc,SLOT(DemandeEnvoyerContact()));
    QObject::connect(&gc,SIGNAL(EnvoyerContact(vector<Contact*>*)),&w,SLOT(remplirTableWidget(vector <Contact*>*)));
    QObject::connect(&w,SIGNAL(supprimerContact(QString, QString)),&gc,SLOT(supprimerContact(QString, QString)));
    QObject::connect(w.ficheC,SIGNAL(signalmodifierContact(QString,QString,QString,QString,QString,QString,QString,QString)),&gc,SLOT(slotModifierContact(QString,QString,QString,QString,QString,QString,QString,QString)));
    QObject::connect(&w,SIGNAL(rechercheContact(QString,QString)),&gc,SLOT(rechercheCritere(QString,QString)));
    w.emit demanderListeContacts();
    QObject::connect(&w,SIGNAL(rechercheDate(int, int, int, int, int, int)),&gc,SLOT(rechercheEntreDeuxDates(int,int,int,int,int,int)));
    QObject::connect(&w,SIGNAL(getListeContacts()),&gc,SLOT(DemandeListeJson()));
    QObject::connect(&gc,SIGNAL(EnvoyerListeJson(vector<Contact*>*)),&w,SLOT(getListeJson(vector<Contact*>*)));

    return a.exec();
}

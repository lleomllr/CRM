#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creationcontact.h"
#include "modificationcontact.h"
#include "fichecontact.h"
#include "gestionbd.h"
#include "popup.h"
#include "jsonform.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GestionBD* gbd,QWidget *parent = nullptr);
    ~MainWindow();
    CreationContact *creerC;
    FicheContact *ficheC;
    GestionBD *bd;
    PopUp *pop;
    JsonForm *jsf;

private slots:
    void on_BoutonCreerContact_clicked();
    void on_tableWidget_itemSelectionChanged();
    void remplirTableWidget(vector <Contact*>*);
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void actualiserContacts();
    void on_BoutonSupprimerContact_clicked();
    void on_BoutonRechercher_clicked();
    void on_BoutonRechercheDates_clicked();
    void onQActionExportJsonClicked();
    void on_BoutonNombreContact_clicked();
    void getListeJson(vector<Contact*>* liste);
    QJsonObject creationContactJSON(Contact * contact);
    void creaFichJSON(QString);

    void on_tableWidget_cellClicked(int row, int column);

    void on_ValeurRecherche_textChanged();

private:
    Ui::MainWindow *ui;
    QString jsonExport;
    vector<Contact*>* listeJSON;


signals:
    void demanderListeContacts();
    void EnvoieModifContact(QString nom,QString prenom,QString entreprise,QString mail,QString photo, QString telephone);
    void AfficherFicheContact(GestionBD* bd,QString nom,QString prenom,QString entreprise,QString mail,QString photo,QString tel);
    void supprimerContact(QString nom,QString prenom);
    void effacerFormulaire();
    void rechercheContact(QString critere, QString recherche);
    void rechercheDate(int, int, int, int, int, int);
    void afficheContact(QString);
    void getListeContacts();

};

#endif // MAINWINDOW_H

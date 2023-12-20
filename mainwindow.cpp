#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(GestionBD* gbd, QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creerC=new CreationContact(this);
    bd=gbd;
    pop = new PopUp();
    jsf = new JsonForm();

    ficheC = new FicheContact(gbd);
    QObject::connect(this,SIGNAL(AfficherFicheContact(GestionBD*, QString,QString,QString,QString,QString,QString)),this->ficheC,SLOT(remplirFiche(GestionBD*,QString,QString,QString,QString,QString,QString)));
    QObject::connect(this->creerC,SIGNAL(actualiserContacts()),this,SLOT(actualiserContacts()));
    QObject::connect(this,SIGNAL(effacerFormulaire()),this->creerC,SLOT(slotEffacerFormulaire()));
    QObject::connect(this->ficheC->modifierC,SIGNAL(majListe()),this,SLOT(actualiserContacts()));
    QObject::connect(this,SIGNAL(afficheContact(QString)),this->pop,SLOT(afficherNbContacts(QString)));
    QObject::connect(this->ui->actionExport_JSON, SIGNAL(triggered()), this, SLOT(onQActionExportJsonClicked()));
    QObject::connect(this->jsf, SIGNAL(exporterJson(QString)), this, SLOT(creaFichJSON(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    free(creerC);
    free(pop);
    free(jsf);
}

void MainWindow::on_BoutonCreerContact_clicked()
{
    emit effacerFormulaire();
    creerC->show();
}


void MainWindow::on_tableWidget_itemSelectionChanged()
{
    //affiche la photo
}


void MainWindow::remplirTableWidget(vector<Contact*>* liste)
{
    qDebug()<< "tableau recu";

    ui->tableWidget->clear();
    for(int i = 0; i < liste->size(); i++) //Boucle pour les lignes
    {
        string date="";
        if ((*liste)[i]->getDate()->tm_mday<=9)
            date = date+ "0";
        date=date + to_string((*liste)[i]->getDate()->tm_mday)+"-";
        if ((*liste)[i]->getDate()->tm_mon<=9)
            date = date+ "0";
        date = date+to_string((*liste)[i]->getDate()->tm_mon + 1)+"-"+to_string((*liste)[i]->getDate()->tm_year + 1900);
        ui->tableWidget->insertRow(i+1);
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getNom())));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getPrenom())));
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getEntreprise())));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getMail())));
        ui->tableWidget->setItem(i,4, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getPhoto())));
        ui->tableWidget->setItem(i,5, new QTableWidgetItem(QString::fromStdString((*liste)[i]->getTelephone())));
        ui->tableWidget->setItem(i,6, new QTableWidgetItem(QString::fromStdString(date)));
    }
}





void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(ui->tableWidget->item(row,0)!=NULL)
    {
        ficheC->show();

        QString nom = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
        QString prenom = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
        QString entreprise = ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toString();
        QString mail= ui->tableWidget->item(row, 3)->data(Qt::DisplayRole).toString();
        QString photo = ui->tableWidget->item(row, 4)->data(Qt::DisplayRole).toString();
        QString tel = ui->tableWidget->item(row, 5)->data(Qt::DisplayRole).toString();
        emit AfficherFicheContact(bd,nom, prenom, entreprise, mail, photo, tel);
    }

    else
    {
        pop->show();
        emit afficheContact("Aucun contact selectionné !");
        qDebug()<<"L'utilisateur a tenté de sélectionner un contact NULL";
    }

}

void MainWindow::actualiserContacts()
{
    emit demanderListeContacts();
}

void MainWindow::on_BoutonSupprimerContact_clicked()
{
    if(ui->tableWidget->currentRow()!=-1)
    {
        QString nom = ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->data(Qt::DisplayRole).toString();
        QString prenom = ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->data(Qt::DisplayRole).toString();
        emit supprimerContact(nom,prenom);
        emit demanderListeContacts();
    }
    else
        qDebug()<<"Aucun contact selectionné";

}


void MainWindow::on_BoutonRechercher_clicked()
{
    QString critere = ui->CritereRecherche->currentText();
    QString recherche = ui->ValeurRecherche->toPlainText();
    emit rechercheContact(critere, recherche);
}


void MainWindow::on_BoutonRechercheDates_clicked()
{
    int jourDebut =ui->DateDebut->date().day();
    int moisDebut = ui->DateDebut->date().month();
    int anneeDebut = ui->DateDebut->date().year();
    int jourFin =ui->DateFin->date().day();
    int moisFin = ui->DateFin->date().month();
    int anneeFin = ui->DateFin->date().year();
    if(anneeDebut<anneeFin)
        emit rechercheDate(jourDebut, moisDebut, anneeDebut, jourFin, moisFin, anneeFin);
    else
        if(moisDebut<moisFin)
            emit rechercheDate(jourDebut, moisDebut, anneeDebut, jourFin, moisFin, anneeFin);
        else
            if(jourDebut<jourFin)
                emit rechercheDate(jourDebut, moisDebut, anneeDebut, jourFin, moisFin, anneeFin);
            else
            {
                pop->show();
                emit afficheContact("La première date doit être plus petite que la deuxième.");
                qDebug()<<"L'utilisateur a rentré des dates incompatibles.";
            }
}





void MainWindow::on_BoutonNombreContact_clicked()
{
    int nb=0;
    while(ui->tableWidget->item(nb, 0)!=NULL)
        nb+=1;
    pop->show();
    string message = "Nombre de contacts : "+to_string(nb);
    QString m = QString::fromStdString(message);
    emit afficheContact(m);

}

void MainWindow::onQActionExportJsonClicked()
{

    jsf->show();
}

void MainWindow::getListeJson(vector<Contact*>* liste)
{
    listeJSON=liste;
}


QJsonObject MainWindow::creationContactJSON(Contact * contact)
{
    QJsonObject contactObject;
    contactObject["Nom"] = QString::fromStdString(contact->getNom());
    contactObject["Prenom"] = QString::fromStdString(contact->getPrenom());
    contactObject["Entreprise"] = QString::fromStdString(contact->getEntreprise());
    contactObject["Mail"] = QString::fromStdString(contact->getMail());
    contactObject["Telephone"] = QString::fromStdString(contact->getTelephone());
    return contactObject;

}

void MainWindow::creaFichJSON(QString chemin)
{
    emit getListeContacts();
    QJsonObject fichierJSON;
    QFile fich(chemin+"/jsonExport.json");
    QJsonObject existingJson;
    QFile existingFile(chemin+"/jsonExport.json");
    QJsonArray contactsArray = existingJson["contacts"].toArray();
    for(int i=0;i<listeJSON->size();i++)
    {
        QJsonObject jsonContact = creationContactJSON(listeJSON->at(i));
        contactsArray.append(jsonContact);
        existingJson["contacts"] = contactsArray;
    }
    QJsonDocument jsonDocument(existingJson);
    QFile file(chemin+"/jsonExport.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(jsonDocument.toJson(QJsonDocument::Indented));
        file.close();
    }

}



void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    ui->BoutonSupprimerContact->setEnabled(ui->tableWidget->item(row,0)!=NULL);
}




void MainWindow::on_ValeurRecherche_textChanged()
{
    ui->BoutonRechercher->setEnabled(ui->ValeurRecherche->toPlainText()!=NULL);
}


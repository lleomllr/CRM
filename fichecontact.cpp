#include "fichecontact.h"
#include "ui_fichecontact.h"

/**
 * @brief FicheContact::CreationContact Constructeur de la classe CreationContact qui initialise l'interface et toutes les fenêtres associés à la fiche du contact.
 * @param gbd Pointeur vers un gestionnaire de base de données.
 */
FicheContact::FicheContact(GestionBD* gbd,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FicheContact)
{
    ui->setupUi(this);
    modifierC=new ModificationContact(this);
    ajouterI=new ajoutInteraction(this);
    fichI = new FicheInteraction(this);
    gI = new GestionInteraction(gbd, parent);
    BD = gbd;
    pop = new PopUp();
    QObject::connect(this, SIGNAL(afficheMessage(QString)), this->pop,SLOT(afficherMessage(QString)));
    QObject::connect(this,SIGNAL(remplirModifContact(QString,QString,QString,QString,QString,QString)),this->modifierC,SLOT(remplirFormulaire(QString,QString,QString,QString,QString,QString)));
    QObject::connect(this->modifierC,SIGNAL(modifierContact(QString,QString,QString,QString,QString,QString)),this,SLOT(slotmodifierContact(QString,QString,QString,QString,QString,QString)));
    QObject::connect(this->modifierC,SIGNAL(modifierContact(QString,QString,QString,QString,QString,QString)),this,SLOT(mettreAJourFiche(QString,QString,QString,QString,QString,QString)));
    QObject::connect(this->ajouterI,SIGNAL(envoieContenuInteraction(QString)),this,SLOT(creerInteraction(QString)));
    QObject::connect(this,SIGNAL(envoieListeTodo(std::vector<Todo*>*)),this->fichI,SLOT(afficheListeTodo(std::vector<Todo*> *)));
    QObject::connect(this->ajouterI,SIGNAL(actualiserFiche()),this,SLOT(actualiserInteractions()));
    QObject::connect(this,SIGNAL(actualiserRecherche()),this,SLOT(actualiserInteractions()));
    QObject::connect(this,SIGNAL(effacerContenu()),this->ajouterI,SLOT(effacerTexte()));
    QObject::connect(this, SIGNAL(supprimerInteraction(Interaction*)),this->gI,SLOT(slotSupprimerInteraction(Interaction*)));
    QObject::connect(this->gI, SIGNAL(actualiserListeInteraction()),this,SLOT(actualiserInteractions()));


}
/**
 * @brief FicheContact::~FicheContact Destructeur de la classe FicheContact qui libère la mémoire de la gestion d'interaction et de l'interface.
 */
FicheContact::~FicheContact()
{
    delete gI;
    delete ui;
}

/**
 * @brief FicheContact::slotmodifierContact slot associé à la modification du contact.
 * @param n Nouveau nom du contact
 * @param p Nouveau prenom du contact
 * @param e Nouvelle entreprise du contact
 * @param m Nouveau mail du contact
 * @param u Nouvel uriPhoto du contact
 * @param t Nouveau numéro de téléphone du contact
 */
void FicheContact::slotmodifierContact(QString n,QString p,QString e ,QString m,QString u,QString t)
{
    emit signalmodifierContact(ui->NomContact->text(),ui->PrenomContact->text(),n,p,e,m,u,t);
}

/**
 * @brief FicheContact::mettreAJourFiche Slot permettant de mettre à jour la fiche du contact qui a été modifié.
 * @param qnom Nouveau nom du contact
 * @param qprenom Nouveau prenom du contact
 * @param qentreprise Nouvelle entreprise du contact
 * @param qmail Nouveau mail du contact
 * @param qphoto Nouvel uriPhoto du contact
 * @param qtelephone Nouveau numéro de téléphone du contact
 */
void FicheContact::mettreAJourFiche(QString qnom,QString qprenom,QString qentreprise,QString qmail,QString qphoto, QString qtelephone)
{
    ui->NomContact->setText(qnom);
    ui->PrenomContact->setText(qprenom);
    ui->EntrepriseContact->setText(qentreprise);
    ui->TelephoneContact->setText(qtelephone);
    ui->MailContact->setText(qmail);

    nom=qnom;
    prenom =qprenom;
    entreprise= qentreprise;
    mail=qmail;
    photo = qphoto;
    telephone = qtelephone;

    QImage image = QImage(photo);
    if(!image.isNull())
    {
        QImage photoScaled;
        if(image.width() > image.height()){
            photoScaled = image.scaledToWidth(200);

        }else {
            photoScaled = image.scaledToHeight(200);

        }
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->addPixmap(QPixmap::fromImage(photoScaled));
        delete ui->PhotoContact->scene();
        ui->PhotoContact->setScene(scene);
        ui->PhotoContact->setMinimumSize(photoScaled.width(), photoScaled.height());
    }else{
        qDebug() << "Echec chargement depuis le chemin :" << photo;
    }
}

/**
 * @brief FicheContact::remplirFiche Slot permettant de remplir la fiche du contact.
 * @param gbd Pointeur vers le gestionnaire de base de données contenant les contacts.
 * @param qnom nom du contact
 * @param qprenom  prenom du contact
 * @param qentreprise  entreprise du contact
 * @param qmail  mail du contact
 * @param qphoto  uriPhoto du contact
 * @param qtelephone  numéro de téléphone du contact
 */
void FicheContact::remplirFiche(GestionBD* gbd, QString qnom,QString qprenom,QString qentreprise,QString qmail,QString qphoto, QString qtelephone)
{
    ui->NomContact->setText(qnom);
    ui->PrenomContact->setText(qprenom);
    ui->EntrepriseContact->setText(qentreprise);
    ui->TelephoneContact->setText(qtelephone);
    ui->MailContact->setText(qmail);

    nom=qnom;
    prenom =qprenom;
    entreprise= qentreprise;
    mail=qmail;
    photo = qphoto;
    telephone = qtelephone;

    Contact *c= new Contact(nom.toStdString(),prenom.toStdString(),mail.toStdString(),entreprise.toStdString(), photo.toStdString(),telephone.toStdString());
    gI->RemplirListeInteractions(c);
    gI->contact = c;
    ui->tableWidget->clear();
    for(int i = 0; i < gI->listeInteractions->size(); i++) //Boucle pour les lignes
    {
            ui->tableWidget->insertRow(i+1);
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(gI->listeInteractions->at(i)->getContenu())));
            string date="";
            string jour=to_string(gI->listeInteractions->at(i)->getDate()->tm_mday);
            string mois=to_string(gI->listeInteractions->at(i)->getDate()->tm_mon + 1);
            string annee=to_string(gI->listeInteractions->at(i)->getDate()->tm_year + 1900);
            date=date +jour +"-"+mois+"-"+annee;
            cout << (gI->listeInteractions)->at(i)->getContenu() << endl;
            cout << "Date : " << jour << "-" << mois <<"-" << annee << endl;
            cout << i << endl;
            ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(date)));
    }

    QImage image = QImage(photo);
    if(!image.isNull())
    {
        QImage photoScaled;
        if(image.width() > image.height())
        {
            photoScaled = image.scaledToWidth(238);

        }
        else
        {
            photoScaled = image.scaledToHeight(238);

        }
        QGraphicsScene* scene = new QGraphicsScene(this);
        scene->addPixmap(QPixmap::fromImage(photoScaled));
        delete ui->PhotoContact->scene();
        ui->PhotoContact->setScene(scene);
        ui->PhotoContact->setMinimumSize(photoScaled.width(), photoScaled.height());
    }
    else
    {
        qDebug() << "Echec chargement depuis le chemin :" << photo;
    }
}

/**
 * @brief FicheContact::actualiserInteractions Slot permettant d'actualiser la liste d'interaction de la fiche du contact.
 */
void FicheContact::actualiserInteractions()
{
    ui->tableWidget->clear();
    for(int i = 0; i < gI->listeInteractions->size(); i++) //Boucle pour les lignes
        {
            cout << (gI->listeInteractions)->at(i)->getContenu() << endl;
            cout << (gI->listeInteractions)->at(i)->getDate()->tm_mday << endl;
            ui->tableWidget->insertRow(i+1);
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(gI->listeInteractions->at(i)->getContenu())));
            string date="";
            date=date + to_string(gI->listeInteractions->at(i)->getDate()->tm_mday)+"-"+to_string(gI->listeInteractions->at(i)->getDate()->tm_mon + 1)+"-"+to_string(gI->listeInteractions->at(i)->getDate()->tm_year + 1900);
            ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(date)));
    }
}

/**
 * @brief FicheContact::on_BoutonModifierContact_clicked Slot associé au bouton de modification de contact.
 */
void FicheContact::on_BoutonModifierContact_clicked()
{
    modifierC->show();
    emit remplirModifContact(nom,prenom,entreprise,mail,photo,telephone);
}

/**
 * @brief FicheContact::on_pushButton_clicked Slot associé au bouton d'ajout d'une interaction
 */
void FicheContact::on_pushButton_clicked()
{
    ajouterI->show();
    emit effacerContenu();
}

/**
 * @brief FicheContact::string_to_tm Méthode permettant de convertir une date au format JJ-MM-AAAA en struct tm.
 * @param dateString chaine de caractère de la forme JJ-MM-AAAA
 */
tm string_to_tm(const std::string &dateString) {
    std::tm timeStruct = {0};
    std::sscanf(dateString.c_str(), "%d-%d-%d", &timeStruct.tm_mday, &timeStruct.tm_mon, &timeStruct.tm_year);
    timeStruct.tm_mon -= 1;
    timeStruct.tm_year -= 1900;

    return timeStruct;
}

/**
 * @brief FicheContact::creerInteraction Permet de découper la chaine saisie par l'utilisateur et de créer une interaction et ses todos associés.
 * @param contenu QString à découper.
 */
void FicheContact::creerInteraction(QString contenu)
{
    string interaction = contenu.toStdString();
    GestionTodo* gT;
    int it =0;
     int pos;
     int posDate;
     time_t tn = time (0) ;
     tm * tdate = localtime (& tn ) ;
     std::string date;
     std::string copie = interaction;
     while (copie.find("@todo") !=-1)
     {
         pos = copie.find("@todo");
         std::string s = copie.substr(0,pos);
         date = "23.10.23";
         tdate = localtime (& tn );
         if (s.find("@date") !=-1)
         {
               posDate = s.find("@date");
               *tdate = string_to_tm(s.substr(posDate+6));
               s=s.substr(0,posDate);
         }
         if (it==0)
         {
               std::cout << "Contenu de l'interaction :" << s << std::endl;

               Interaction* i =new Interaction(s, tdate);
               gI->ajouterInteraction(i);
               gT= new GestionTodo(BD,&(i->listeTodos),i);
         }
         else
         {
               std::cout << "Nouveau Todo :" <<  s << "A la date du : "<< tdate->tm_mday << "-"<< tdate->tm_mon+1 << "-" << tdate->tm_year+1900 << std::endl;
               Todo* t = new Todo(s, tdate);
               gT->ajouterTodo(t);
         }
         it++;
         copie = copie.substr(pos+6);
     }
     if (copie.find("@date") !=-1)
     {
         posDate = copie.find("@date");
         date = copie.substr(posDate+6);
         *tdate = string_to_tm(copie.substr(posDate+6));
         copie = copie.substr(0,posDate);
     }
     if(it==0)
     {
         std::cout << "Contenu de l'interaction :" << copie << std::endl;
         Interaction* i =new Interaction(copie, tdate);
         gI->ajouterInteraction(i);
     }
     else
     {
         std::cout << "Nouveau Todo :" <<  copie << "A la date du : "<< tdate->tm_mday << "-"<< tdate->tm_mon+1 << "-" << tdate->tm_year+1900 << std::endl;
         Todo* t = new Todo(copie, tdate);
         gT->ajouterTodo(t);
     }

}

/**
 * @brief FicheContact::string_to_tm Méthode permettant de convertir une date au format JJ-MM-AAAA et de la stocker dans une struct tm passée en paramètre.
 * @param texte chaine de caractère de la forme JJ-MM-AAAA
 * @param date Pointeur vers une struct tm qui prendra la valeur de la date saisie.
 */
void FicheContact::ConversionStringDate(std::string &texte, tm* date)
{
    sscanf(texte.c_str(), "%d-%d-%d", &date->tm_mday, &date->tm_mon, &date->tm_year);
    date->tm_mon-=1;
    date->tm_year-=1900;
}

/**
 * @brief FicheContact::on_tableWidget_cellDoubleClicked Slot associé au double clique sur une ligne du tableau.
 */
void FicheContact::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if(ui->tableWidget->item(row,0)!=NULL)
    {
        qDebug()<<"Double clique";
        time_t tn = time (0) ;
        tm * tdate = localtime (& tn ) ;
        QString dateI = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
        string date = dateI.toStdString();
        ConversionStringDate(date,tdate);
        QString interaction = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
        Interaction* i = new Interaction(interaction.toStdString(),tdate);
        GestionTodo* gT = new GestionTodo(BD,&(i->listeTodos),i );
        emit envoieListeTodo(gT->getTodos());
        qDebug()<<"Signal Double Clique envoyé";
        fichI->show();
    }
    else
    {
        pop->show();
        emit afficheMessage("Aucune interaction selectionnée !");
        qDebug()<<"L'utilisateur a tenté de sélectionner une interaction NULL";
    }
}

/**
 * @brief FicheContact::on_BoutonRechercheInteraction_clicked Slot associé au bouton de recherche d'une interaction par date.
 */
void FicheContact::on_BoutonRechercheInteraction_clicked()
{
   int jour= ui->dateRecherche->date().day();
   int mois= ui->dateRecherche->date().month();
   int annee= ui->dateRecherche->date().year();
   string sjour;
   string smois;
   string sannee;
   if(jour<=9)
       sjour ="0"+to_string(jour);
   else
       sjour=to_string(jour);
   if(mois<=9)
       smois ="0"+to_string(mois);
   else
       smois=to_string(mois);
   sannee=to_string(annee);
   string date = sjour+"-"+smois+"-"+sannee;
   qDebug()<< QString::fromStdString(date);

   gI->RechercheByDate(date,gI->contact);
   emit actualiserRecherche();
}

/**
 * @brief FicheContact::on_BoutonSuppInteraction_clicked Slot associé au bouton de suppression d'une interaction.
 */
void FicheContact::on_BoutonSuppInteraction_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(ui->tableWidget->currentRow()!=-1)
    {
        time_t tn = time (0) ;
        tm * tdate = localtime (& tn ) ;
        QString dateI = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
        string date = dateI.toStdString();
        ConversionStringDate(date,tdate);
        QString interaction = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
        Interaction* i = new Interaction(interaction.toStdString(),tdate);
        emit supprimerInteraction(i);
    }
    else
        qDebug()<<"Aucune interaction selectionnée";
}

/**
 * @brief FicheContact::on_tableWidget_cellClicked Slot associé au clic simple sur une ligne du tableau.
 */
void FicheContact::on_tableWidget_cellClicked(int row, int column)
{
     ui->BoutonSuppInteraction->setEnabled(ui->tableWidget->item(row,0)!=NULL);
}


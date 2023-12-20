#include "creationcontact.h"
#include "ui_creationcontact.h"


/**
 * @brief CreationContact::CreationContact Constructeur de la classe CreationContact qui initialise l'interface et une fenêtre de message.
 */
CreationContact::CreationContact(QWidget *parent) :QDialog(parent),ui(new Ui::CreationContact)
{
    ui->setupUi(this);
    pop = new PopUp();
    QObject::connect(this, SIGNAL(afficheMessage(QString)), this->pop,SLOT(afficherMessage(QString)));
}

/**
 * @brief CreationContact::~CreationContact Destructeur de la classe CreationContact qui libère la mémoire de l'interface et de la fenêtre de message.
 */
CreationContact::~CreationContact()
{
    delete ui;
    free(pop);
}


/**
 * @brief CreationContact::on_BoutonAnnulerCreationContact_clicked Slot associé au bouton permettant d'annuler la création d'un contact. Le slot ferme la fenêtre.
 */
void CreationContact::on_BoutonAnnulerCreationContact_clicked()
{
    close();
}

/**
 * @brief CreationContact::on_BoutonConfirmerCreationContact_clicked Slot associé au bouton de création de contact. Il récupère tous les champs, vérifie qu'ils sont saisis correctement et envoie le contact à la gestion de contact.
 */
void CreationContact::on_BoutonConfirmerCreationContact_clicked()
{
    QString qnom = ui->NomContact->text();
    string nom = qnom.toStdString();
    QString qprenom = ui->PrenomContact->text();
    string prenom = qprenom.toStdString();
    QString qentreprise = ui->EntrepriseContact->text();
    string entreprise = qentreprise.toStdString();
    QString qemail = ui->EmailContact->text();
    string email = qemail.toStdString();
    QString quriPhoto = ui->uriPhotoContact->text();
    string uriPhoto = quriPhoto.toStdString();
    QString qtel = ui->TelephoneContact->text();
    string tel = qtel.toStdString();
    if(nom.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-")!=std::string::npos || qnom==NULL)
    {
        pop->show();
        emit afficheMessage("Le nom doit être composé de lettres uniquement");
        qDebug()<<"L'utilisateur tente de créer un nom avec d'autres choses que des lettres";
    }
    else
    {
        if(prenom.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-")!=std::string::npos|| qprenom==NULL)
        {
            pop->show();
            emit afficheMessage("Le prénom doit être composé de lettres uniquement");
            qDebug()<<"L'utilisateur tente de créer un prénom avec d'autres choses que des lettres";
        }
        else
            if(email.find_first_not_of("@")==std::string::npos || qemail==NULL)
            {
                pop->show();
                emit afficheMessage("L'adresse Mail n'est pas au bon format");
                qDebug()<<"L'utilisateur tente de créer une adresse mail erronée";
            }
            else
            {
                if(tel.find_first_not_of("1234567890+")!=std::string::npos || qtel==NULL)
                {
                    pop->show();
                    emit afficheMessage("Le numéro de téléphone n'est pas au bon format");
                    qDebug()<<"L'utilisateur tente de créer un numéro de téléphone erroné";
                }
                else
                    if(quriPhoto==NULL)
                    {
                        pop->show();
                        emit afficheMessage("Il faut sélectionner une photo");
                        qDebug()<<"L'utilisateur tente de créer un contact sans photo";
                    }
                    else
                    {
                        Contact *c= new Contact(nom,prenom,email,entreprise, uriPhoto,tel);
                        emit envoieContact(c);
                        emit actualiserContacts();
                        close();
                    }
            }
    }



}

/**
 * @brief CreationContact::slotEffacerFormulaire Slot permettant d'effacer le contenu du formulaire.
 */
void CreationContact::slotEffacerFormulaire()
{
    ui->NomContact->clear();
    ui->PrenomContact->clear();
    ui->EntrepriseContact->clear();
    ui->EmailContact->clear();
    ui->uriPhotoContact->clear();
    ui->TelephoneContact->clear();
}

/**
 * @brief CreationContact::on_BoutonSelectionPhoto_clicked Slot associé au bouton de sélection de photo. Il ouvre une fenêtre de sélection de fichier.
 */
void CreationContact::on_BoutonSelectionPhoto_clicked()
{
    fileDialog = new QFileDialog();
    fileDialog->setAttribute(Qt::WA_DeleteOnClose);
    fileDialog->setWindowModality(Qt::ApplicationModal);
    QString filtre = "PNG File (*.png) ;; JPG File (*.jpg)";
    QString chemin = fileDialog->getOpenFileName(this, "Open file", QDir::homePath(), filtre);
    qDebug() << "Chemin selectionné : " << chemin;
    ui->uriPhotoContact->setText(chemin);
    if (!chemin.isEmpty())
    {
            QString dossierDestination =QDir::currentPath()+ "/images/";
            QDir().mkpath(dossierDestination);
            QString nomFichier = QFileInfo(chemin).fileName();
            QString cheminDestination = dossierDestination + nomFichier;
            if (QFile::copy(chemin, cheminDestination)) {
                qDebug() << "Fichier copié avec succès vers" << cheminDestination;
            } else {
                qDebug() << "Erreur lors de la copie du fichier";
            }
    }

}


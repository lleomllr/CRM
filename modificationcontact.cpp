#include "modificationcontact.h"
#include "ui_modificationcontact.h"

ModificationContact::ModificationContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificationContact)
{
    ui->setupUi(this);
    pop = new PopUp();
    QObject::connect(this, SIGNAL(afficheMessage(QString)), this->pop,SLOT(afficherMessage(QString)));
}

ModificationContact::~ModificationContact()
{
    delete ui;
    free(pop);
}

void ModificationContact::remplirFormulaire(QString nom,QString prenom,QString entreprise,QString mail,QString photo, QString telephone)
{
    ui->NomContact->setText(nom);
    ui->PrenomContact->setText(prenom);
    ui->EntrepriseContact->setText(entreprise);
    ui->EmailContact->setText(mail);
    ui->PhotoContact->setText(photo);
    ui->TelephoneContact->setText(telephone);
    nom= ui->NomContact->text();
    prenom=ui->PrenomContact->text();

}

void ModificationContact::on_ConfirmerModificationContact_clicked()
{
    if(ui->NomContact->text().toStdString().find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-")!=std::string::npos || ui->NomContact->text()==NULL)
    {
        pop->show();
        emit afficheMessage("Le nom doit être composé de lettres uniquement");
        qDebug()<<"L'utilisateur tente de créer un nom avec d'autres choses que des lettres";
    }
    else
    {
        if(ui->PrenomContact->text().toStdString().find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-")!=std::string::npos|| ui->PrenomContact->text()==NULL)
        {
            pop->show();
            emit afficheMessage("Le prénom doit être composé de lettres uniquement");
            qDebug()<<"L'utilisateur tente de créer un prénom avec d'autres choses que des lettres";
        }
        else
        {
            if(ui->EmailContact->text().toStdString().find_first_not_of("@")!=std::string::npos || ui->EmailContact->text()==NULL)
            {
                pop->show();
                emit afficheMessage("L'adresse Mail n'est pas au bon format");
                qDebug()<<"L'utilisateur tente de créer une adresse mail erronée";
            }
            else
            {
                if(ui->TelephoneContact->text().toStdString().find_first_not_of("1234567890+")!=std::string::npos || ui->TelephoneContact->text()==NULL)
                {
                    pop->show();
                    emit afficheMessage("Le numéro de téléphone n'est pas au bon format");
                    qDebug()<<"L'utilisateur tente de créer un numéro de téléphone erroné";
                }
                else
                {
                    if(ui->PhotoContact->text()==NULL)
                    {
                        pop->show();
                        emit afficheMessage("Il faut sélectionner une photo");
                        qDebug()<<"L'utilisateur tente de créer un contact sans photo";
                    }
                    else
                    {
                        emit modifierContact(ui->NomContact->text(),ui->PrenomContact->text(),ui->EntrepriseContact->text(),ui->EmailContact->text(),ui->PhotoContact->text(),ui->TelephoneContact->text());
                        emit majListe();
                        close();
                    }
                }
            }
        }
    }
}


void ModificationContact::on_AnnulerModificationContact_clicked()
{
    close();
}


void ModificationContact::on_changementPhoto_clicked()
{
    fileDialog = new QFileDialog();
    fileDialog->setAttribute(Qt::WA_DeleteOnClose);
    fileDialog->setWindowModality(Qt::ApplicationModal);
    QString filtre = "PNG File (*.png) ;; JPG File (*.jpg)";
    QString chemin = fileDialog->getOpenFileName(this, "Open file", QDir::homePath(), filtre);
    qDebug() << "Chemin selectionné : " << chemin;
    ui->PhotoContact->setText(chemin);
    if (!chemin.isEmpty())
    {
            QString dossierDestination = QDir::currentPath() + "/images/";
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


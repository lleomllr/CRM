#include "ajoutinteraction.h"
#include "ui_ajoutinteraction.h"

/**
 * @brief ajoutInteraction::ajoutInteraction Constructeur de la classe qui initialise l'ui ainsi qu'une fenêtre de message.
 */
ajoutInteraction::ajoutInteraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutInteraction)
{
    ui->setupUi(this);
    pop = new PopUp();
    QObject::connect(this, SIGNAL(afficheMessage(QString)), this->pop,SLOT(afficherMessage(QString)));
}

/**
 * @brief ajoutInteraction::~ajoutInteraction Destructeur de la classe qui libère la mémoire de l'ui et de la fenêtre de message.
 */
ajoutInteraction::~ajoutInteraction()
{
    delete ui;
    free(pop);
}



/**
 * @brief ajoutInteraction::on_BoutonCreation_clicked Slot associé au bouton de création de l'interaction.
 */
void ajoutInteraction::on_BoutonCreation_clicked()
{
    QString contenu = ui->TexteContenu->toPlainText();
    if(contenu!=NULL)
    {
        emit envoieContenuInteraction(contenu);
        emit actualiserFiche();
        close();
    }
    else
    {
        pop->show();
        emit afficheMessage("Merci de remplir les champs");
        qDebug()<<"L'utilisateur tente de créer une interaction vide";
    }
}

/**
 * @brief ajoutInteraction::on_BoutonAnnuler_clicked Slot associé au bouton d'annulation de la saisie. Ce slot ferme la fenêtre.
 */
void ajoutInteraction::on_BoutonAnnuler_clicked()
{
    close();
}

/**
 * @brief ajoutInteraction::effacerTexte Slot permettant d'effacer le contenu de la zone de saisie.
 */
void ajoutInteraction::effacerTexte()
{
    ui->TexteContenu->clear();
}

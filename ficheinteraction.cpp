#include "ficheinteraction.h"
#include "ui_ficheinteraction.h"

/**
 * @brief FicheInteraction::FicheInteraction Constructeur de la classe FicheInteraction qui initialise l'interface.
 */
FicheInteraction::FicheInteraction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FicheInteraction)
{
    ui->setupUi(this);
}

/**
 * @brief FicheInteraction::~FicheInteraction Constructeur de la classe FicheInteraction qui libère la mémoire de l'interface.
 */
FicheInteraction::~FicheInteraction()
{
    delete ui;
}

/**
 * @brief FicheInteraction::afficheListeTodo Slot permettant d'afficher la liste des todos associés à l'interaction.
 */
void FicheInteraction::afficheListeTodo(std::vector<Todo*> *liste)
{
    qDebug()<<"Signal recu";
    ui->tableWidget->clear();
    for(int i = 0; i < liste->size(); i++) //Boucle pour les lignes
        {
            qDebug()<< QString::fromStdString(liste->at(i)->getContenu());
            ui->tableWidget->insertRow(i+1);
            ui->tableWidget->setItem(i,1, new QTableWidgetItem(QString::fromStdString(liste->at(i)->getContenu())));
            std::string date="";
            date=date + std::to_string(liste->at(i)->getDate()->tm_mday)+"-"+std::to_string(liste->at(i)->getDate()->tm_mon + 1)+"-"+std::to_string(liste->at(i)->getDate()->tm_year + 1900);
            ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::fromStdString(date)));
    }
}

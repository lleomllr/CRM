#ifndef AJOUTINTERACTION_H
#define AJOUTINTERACTION_H

#include <QDialog>
#include "popup.h"
#include <QDebug>


/**
 * @brief La classe ajoutInteraction possède ui permettant d'ajouter une interaction à notre système avec des todos associés.
 */
namespace Ui {
class ajoutInteraction;
}

class ajoutInteraction : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutInteraction(QWidget *parent = nullptr);
    ~ajoutInteraction();
    PopUp *pop;

private:
    Ui::ajoutInteraction *ui;

private slots:
    void on_BoutonCreation_clicked();
    void effacerTexte();
    void on_BoutonAnnuler_clicked();

signals:
    void envoieContenuInteraction(QString contenu);
    void actualiserFiche();
    void afficheMessage(QString);
};

#endif // AJOUTINTERACTION_H

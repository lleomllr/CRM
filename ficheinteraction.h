#ifndef FICHEINTERACTION_H
#define FICHEINTERACTION_H

#include <QDialog>
#include <todo.h>
#include <iostream>
#include <QDebug>

/**
 * @brief La classe FicheInteraction possède une interface permettant d'afficher la liste des todos d'une interaction.
 */

namespace Ui {
class FicheInteraction;
}

class FicheInteraction : public QDialog
{
    Q_OBJECT

public:
    explicit FicheInteraction(QWidget *parent = nullptr);
    ~FicheInteraction();
    Ui::FicheInteraction *ui;
private slots:
    void afficheListeTodo(std::vector<Todo*> *liste);

};

#endif // FICHEINTERACTION_H

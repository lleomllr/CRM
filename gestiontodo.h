#ifndef GESTIONTODO_H
#define GESTIONTODO_H

#include "interaction.h"
#include <vector>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include "todo.h"
#include "gestionbd.h"


class GestionTodo : public QObject
{
    Q_OBJECT

    private:
        GestionBD* bd;
        std::vector<Todo*>* listeTodos;
        Interaction* interaction;

    public:
        explicit GestionTodo(GestionBD* bd, std::vector<Todo*>* liste,Interaction* i, QObject *parent = nullptr);
        ~GestionTodo();
        void ajouterTodo(Todo* i);
        std::vector<Todo*>* getTodos();
        void supprimerTodo(Todo* i);
};


#endif

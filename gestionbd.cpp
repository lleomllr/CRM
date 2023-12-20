#include "gestionbd.h"

GestionBD::GestionBD()
{
    dbOuverte = false;
    connectDB();

}

GestionBD::~GestionBD()
{
    qDebug()<<"Fermeture de la BD !";
    closeDB();
}

bool GestionBD::connectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE") ;
    QString localeUri = "tmp/baseProjet.sqlite";
    db.setDatabaseName(localeUri);
    if(!db.open())
    {
        qDebug()<<"Pas de connexion à la BDD !";
        dbOuverte = false;
    }
    else
    {
        qDebug()<<"Connexion réussie à la BDD !" ;
        dbOuverte = true;
    }
    return dbOuverte;
}

void GestionBD::closeDB()
{
    if (dbOuverte==true)
        db.close();
}

bool GestionBD::ajouterContactBD(Contact* c)
{

    string date="";
    if (c->getDate()->tm_mday<=9)
        date = date+ "0";
    date=date + to_string(c->getDate()->tm_mday)+"-";
    if (c->getDate()->tm_mon<=9)
        date = date+ "0";
    date = date+to_string(c->getDate()->tm_mon + 1)+"-"+to_string(c->getDate()->tm_year + 1900);
    if(dbOuverte)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Contact (Nom, Prenom, Entreprise, Email, Telephone, Photo, DateCreation) VALUES (:n, :p, :e, :m, :t,:u, :d)");
        query.bindValue(":n", QString::fromStdString(c->getNom()));
        query.bindValue(":p", QString::fromStdString(c->getPrenom()));
        query.bindValue(":e", QString::fromStdString(c->getEntreprise()));
        query.bindValue(":m", QString::fromStdString(c->getMail()));
        query.bindValue(":u", QString::fromStdString(c->getPhoto()));
        query.bindValue(":t", QString::fromStdString(c->getTelephone()));
        query.bindValue(":d", QString::fromStdString(date));

        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter l'ajout du contact dans la BD";
            qDebug()<< query.lastError().text();
            return false;
        }
    }
    return true;
}

bool GestionBD::supprimerContactBD(Contact* c)
{
    if(dbOuverte)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM Contact WHERE Nom=:n and Prenom=:p;");
        query.bindValue(":n", QString::fromStdString(c->getNom()));
        query.bindValue(":p", QString::fromStdString(c->getPrenom()));
        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la suppression du contact dans la BD";
            return false;
        }
    }
    return true;
}

void GestionBD::RemplirListeContacts(std::vector<Contact*> *listeContacts)
{
    listeContacts->clear();
    if(dbOuverte)
    {
        QSqlQuery query("SELECT Nom, Prenom, Email, Entreprise, Photo, Telephone, DateCreation from Contact");
        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la lecture des contacts dans la BD";
        }
        else
        {
            qDebug()<<"Requete reussie";

            while (query.next())
            {
                QString qNom=query.value(0).toString();
                string nom = qNom.toStdString();
                QString qPrenom=query.value(1).toString();
                string prenom = qPrenom.toStdString();
                QString qEmail=query.value(2).toString();
                string mail = qEmail.toStdString();
                QString qEntreprise=query.value(3).toString();
                string entreprise = qEntreprise.toStdString();
                QString qPhoto=query.value(4).toString();
                string photo = qPhoto.toStdString();
                QString qTelephone=query.value(5).toString();
                string telephone = qTelephone.toStdString();
                QString qDate=query.value(6).toString();
                string date = qDate.toStdString();
                string jour = "";
                jour = jour+date[0]+date[1];
                string mois = "";
                mois = mois+date[3]+date[4];
                string annee = "";
                annee = annee+date[6]+date[7]+date[8]+date[9];

                time_t tn = time(0);
                tm * newdate = localtime(&tn);
                newdate->tm_mday = stoi(jour);
                newdate->tm_mon = stoi(mois)-1;
                newdate->tm_year = stoi(annee)-1900;
                qDebug()<<newdate->tm_mday;
                qDebug()<<newdate->tm_mon;
                qDebug()<<newdate->tm_year;

                Contact* contact= new Contact(nom,prenom,mail,entreprise,photo,telephone,stoi(jour),stoi(mois)-1,stoi(annee)-1900);
                listeContacts->push_back(contact);
            }
            auto it = listeContacts->begin();
            while((it!=listeContacts->end())){
                cout<< (*it)->getNom()<<endl;
                ++it;
            }
        }
    }
}

void GestionBD::RechercheBy(QString critere, QString recherche, std::vector<Contact*> *listeContacts)
{
    listeContacts->clear();
    qDebug() <<critere;
    qDebug() <<recherche;
    if(dbOuverte)
    {
        QSqlQuery query;
        if (critere=="Nom")
        {

            query.prepare("SELECT Nom, Prenom, Email, Entreprise, Photo, Telephone, DateCreation from Contact WHERE Nom = :r");
            query.bindValue(":r",recherche);
        }
        else
            if(critere=="Entreprise")
            {
                query.prepare("SELECT Nom, Prenom, Email, Entreprise, Photo, Telephone, DateCreation from Contact WHERE Entreprise = :r");
                query.bindValue(":r",recherche);
            }
            else
                if(critere=="Telephone")
                {
                    query.prepare("SELECT Nom, Prenom, Email, Entreprise, Photo, Telephone, DateCreation from Contact WHERE Telephone = :r");
                    query.bindValue(":r",recherche);
                }
                else
                {
                    query.prepare("SELECT Nom, Prenom, Email, Entreprise, Photo, Telephone, DateCreation from Contact");
                }
        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la lecture des contacts dans la BD";
        }
        else
        {
            qDebug()<<"Requete reussie";

            while (query.next())
            {
                qDebug() << "+1";
                QString qNom=query.value(0).toString();
                string nom = qNom.toStdString();
                QString qPrenom=query.value(1).toString();
                string prenom = qPrenom.toStdString();
                QString qEmail=query.value(2).toString();
                string mail = qEmail.toStdString();
                QString qEntreprise=query.value(3).toString();
                string entreprise = qEntreprise.toStdString();
                QString qPhoto=query.value(4).toString();
                string photo = qPhoto.toStdString();
                QString qTelephone=query.value(5).toString();
                string telephone = qTelephone.toStdString();
                QString qDate=query.value(6).toString();
                string date = qDate.toStdString();
                string jour = "";
                jour = jour+date[0]+date[1];
                string mois = "";
                mois = mois+date[3]+date[4];
                string annee = "";
                annee = annee+date[6]+date[7]+date[8]+date[9];

                time_t tn = time(0);
                tm * newdate = localtime(&tn);
                newdate->tm_mday = stoi(jour);
                newdate->tm_mon = stoi(mois)-1;
                newdate->tm_year = stoi(annee)-1900;
                qDebug()<<newdate->tm_mday;
                qDebug()<<newdate->tm_mon;
                qDebug()<<newdate->tm_year;

                Contact* contact= new Contact(nom,prenom,mail,entreprise,photo,telephone,stoi(jour),stoi(mois)-1,stoi(annee)-1900);
                listeContacts->push_back(contact);
            }
            auto it = listeContacts->begin();
            while((it!=listeContacts->end())){
                cout<< (*it)->getNom()<<endl;
                ++it;
            }
        }
    }
}

void GestionBD::RechercheInteractionByDate(string date, std::vector<Interaction*> *listeInteractions, Contact *c)
{
    listeInteractions->clear();
    if(dbOuverte)
    {
        QSqlQuery query;

        query.prepare("SELECT Contenu, DateCreation from Interaction WHERE DateCreation = :d");
        query.bindValue(":d",QString::fromStdString(date));

        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la lecture des contacts dans la BD";
        }
        else
        {
            qDebug()<<"Requete reussie";

            while (query.next())
            {
                qDebug() << "+1";
                QString qContenu=query.value(0).toString();
                string contenu = qContenu.toStdString();
                QString qDate=query.value(1).toString();
                string date = qDate.toStdString();
                string jour = "";
                jour = jour+date[0]+date[1];
                string mois = "";
                mois = mois+date[3]+date[4];
                string annee = "";
                annee = annee+date[6]+date[7]+date[8]+date[9];

                time_t tn = time(0);
                tm * newdate = localtime(&tn);
                newdate->tm_mday = stoi(jour);
                newdate->tm_mon = stoi(mois)-1;
                newdate->tm_year = stoi(annee)-1900;
                qDebug()<<newdate->tm_mday;
                qDebug()<<newdate->tm_mon;
                qDebug()<<newdate->tm_year;

                Interaction* interaction = new Interaction(contenu, stoi(jour),stoi(mois)-1,stoi(annee)-1900);
                cout << *interaction << endl;
                listeInteractions->push_back(interaction);


            }
        }


    }
}


void GestionBD::modifierContact(std::string OldNom, std::string OldPrenom,std::string NewNom, std::string NewPrenom,std::string NewEntreprise,std::string NewMail,std::string NewTel,std::string NewUri)
{
    if(dbOuverte)
    {
        QSqlQuery query;
        query.prepare("UPDATE Contact SET Nom = :n, Prenom = :p, Entreprise = :e, Email = :m, Telephone = :t, Photo = :u, WHERE Nom = :an AND Prenom = :ap");
        query.bindValue(":an", QString::fromStdString(OldNom));
        query.bindValue(":ap", QString::fromStdString(OldPrenom));
        query.bindValue(":n", QString::fromStdString(NewNom));
        query.bindValue(":p", QString::fromStdString(NewPrenom));
        query.bindValue(":e", QString::fromStdString(NewEntreprise));
        query.bindValue(":m", QString::fromStdString(NewMail));
        query.bindValue(":u", QString::fromStdString(NewUri));
        query.bindValue(":t", QString::fromStdString(NewTel));

        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter la mise à jour du contact dans la BD";
            qDebug()<< query.lastError().text();
        }
    }
}

void GestionBD::RemplirListeInteractions(std::vector<Interaction*>* listeInteractions, Contact *c)
{
    listeInteractions->clear();
    if(dbOuverte)
    {
        QSqlQuery query;
        query.prepare("SELECT Contenu, Interaction.DateCreation from Contact, Interaction, ContactInteraction WHERE Nom = :n AND Prenom = :p AND Contact.IdContact = ContactInteraction.IdContact AND ContactInteraction.IdInteraction = Interaction.IdInteraction");
        query.bindValue(":n", QString::fromStdString(c->getNom()));
        query.bindValue(":p", QString::fromStdString(c->getPrenom()));
        if(!query.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la lecture des Interactions dans la BD";
            qDebug()<< query.lastError().text();
        }
        else
        {
            qDebug()<<"Requete reussie x";

            while (query.next())
            {
                QString qContenu=query.value(0).toString();
                string contenu = qContenu.toStdString();
                QString qDate=query.value(1).toString();
                string date = qDate.toStdString();
                string jour = "";
                jour = jour+date[0]+date[1];
                string mois = "";
                mois = mois+date[3]+date[4];
                string annee = "";
                annee = annee+date[6]+date[7]+date[8]+date[9];

                time_t tn = time(0);
                tm * newdate = localtime(&tn);
                newdate->tm_mday = stoi(jour);
                newdate->tm_mon = stoi(mois)-1;
                newdate->tm_year = stoi(annee)-1900;
                qDebug()<<newdate->tm_mday;
                qDebug()<<newdate->tm_mon;
                qDebug()<<newdate->tm_year;

                Interaction* interaction = new Interaction(contenu, stoi(jour),stoi(mois)-1,stoi(annee)-1900);
                cout << *interaction << endl;
                listeInteractions->push_back(interaction);
            }
        }
    }
}

bool GestionBD::ajouterInteraction(Interaction* i,Contact* contact)
{
    string date="";
    if (i->getDate()->tm_mday<=9)
        date = date+ "0";
    date=date + to_string(i->getDate()->tm_mday)+"-";
    if (i->getDate()->tm_mon<=9)
        date = date+ "0";
    date = date+to_string(i->getDate()->tm_mon + 1)+"-"+to_string(i->getDate()->tm_year + 1900);
    int idContact;
    int idInteraction;
    if(dbOuverte)
    {
        QSqlQuery query1;
        query1.prepare("INSERT INTO Interaction (Contenu, DateCreation) VALUES (:c, :d)");
        query1.bindValue(":c", QString::fromStdString(i->getContenu()));
        query1.bindValue(":d", QString::fromStdString(date));

        if(!query1.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter l'ajout de l'interaction dans la BD";
            qDebug()<< query1.lastError().text();
            return false;
        }
        else
        {
            qDebug()<<"Ajout effectué";
            qDebug()<<QString::fromStdString(contact->getNom());
            qDebug()<<QString::fromStdString(contact->getPrenom());
        }

        QSqlQuery query2;
        query2.prepare("SELECT IdContact from Contact WHERE Nom = :n AND Prenom = :p");
        query2.bindValue(":n", QString::fromStdString(contact->getNom()));
        query2.bindValue(":p", QString::fromStdString(contact->getPrenom()));
        if(!query2.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idContact dans la BD";
        }
        else
        {
            while (query2.next())
            {
                QString qidContact=query2.value(0).toString();
                string a =qidContact.toStdString();
                idContact = stoi(a);
                qDebug()<<"Requete2 reussie";
            }
        }

        QSqlQuery query3;
        query3.prepare("SELECT IdInteraction from Interaction WHERE Contenu = :c ");
        query3.bindValue(":c", QString::fromStdString(i->getContenu()));

        if(!query3.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idInteraction dans la BD";
        }
        else
        {
            query3.first();
            {
                qDebug()<<"Requete3 reussie";
                QString qidInteraction=query3.value(0).toString();
                string b =qidInteraction.toStdString();
                idInteraction = stoi(b);
            }

        }

        qDebug() << idContact;
        qDebug() << idInteraction;


        QSqlQuery query4;
        query4.prepare("INSERT INTO ContactInteraction (IdContact, IdInteraction) VALUES (:c, :d)");
        query4.bindValue(":c", QString::number(idContact));
        query4.bindValue(":d", QString::number(idInteraction));

        if(!query4.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter l'ajout du ContactInteraction dans la BD";
            qDebug()<< query4.lastError().text();
            return false;
        }
    }
    return true;
}

void GestionBD::supprimerInteraction(Interaction* i)
{
    int idInteraction;
    QSqlQuery query1;
    query1.prepare("SELECT IdInteraction from Interaction WHERE Contenu = :c");
    query1.bindValue(":c", QString::fromStdString(i->getContenu()));

    if(dbOuverte)
    {
        if(!query1.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'interaction dans la BD";
        }
        else
        {
            query1.first();
            QString qidInteraction=query1.value(0).toString();
            string a =qidInteraction.toStdString();
            idInteraction = stoi(a);
            qDebug()<<"Requete2 reussie";
        }

        QSqlQuery query2;
        query2.prepare("DELETE FROM ContactInteraction WHERE IdInteraction = :i;");
        query2.bindValue(":i", QString::number(idInteraction));
        if(!query2.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la suppression du ContactInteraction dans la BD";
        }

        QSqlQuery query3;
        query3.prepare("DELETE FROM Interaction WHERE IdInteraction = :i;");
        query3.bindValue(":i", QString::number(idInteraction));
        if(!query3.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la suppression de l'interaction dans la BD";
        }
    }

}

bool GestionBD::ajouterTodo(Todo* t,Interaction* interaction)
{
    int idTodo;
    int idInteraction;
    string date="";
    if (t->getDate()->tm_mday<=9)
        date = date+ "0";
    date=date + to_string(t->getDate()->tm_mday)+"-";
    if (t->getDate()->tm_mon<=9)
        date = date+ "0";
    date = date+to_string(t->getDate()->tm_mon + 1)+"-"+to_string(t->getDate()->tm_year + 1900);
    if(dbOuverte)
    {
        QSqlQuery query1;
        query1.prepare("INSERT INTO Todo (Contenu, Date) VALUES (:c, :d)");
        query1.bindValue(":c", QString::fromStdString(t->getContenu()));
        query1.bindValue(":d", QString::fromStdString(date));

        if(!query1.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter l'ajout du Todo dans la BD";
            qDebug()<< query1.lastError().text();
            return false;
        }

        QSqlQuery query2;
        query2.prepare("SELECT IdInteraction from Interaction WHERE Contenu = :c");
        query2.bindValue(":c", QString::fromStdString(interaction->getContenu()));


        if(!query2.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idInteraction dans la BD";
        }
        else
        {
            while (query2.next())
            {
                QString qidInteraction=query2.value(0).toString();
                string a =qidInteraction.toStdString();
                idInteraction = stoi(a);
                qDebug()<<"Requete2 reussie";
            }
        }

        QSqlQuery query3;
        query3.prepare("SELECT IdTodo from Todo WHERE Contenu = :c ");
        query3.bindValue(":c", QString::fromStdString(t->getContenu()));

        if(!query3.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idTodo dans la BD";
        }
        else
        {
            query3.first();
            {
                qDebug()<<"Requete3 reussie";
                QString qidTodo=query3.value(0).toString();
                string b =qidTodo.toStdString();
                idTodo = stoi(b);
            }

        }

        qDebug() << idTodo;
        qDebug() << idInteraction;


        QSqlQuery query4;
        query4.prepare("INSERT INTO InteractionTodo (IdInteraction, IdTodo) VALUES (:i, :t)");
        query4.bindValue(":i", QString::number(idInteraction));
        query4.bindValue(":t", QString::number(idTodo));

        if(!query4.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuter l'ajout de l'interactionTodo dans la BD";
            qDebug()<< query4.lastError().text();
            return false;
        }
    }
    return true;
}

void GestionBD::supprimerTodo(Todo* t)
{
    int idTodo;
    QSqlQuery query1;
    query1.prepare("SELECT IdTodo from Todo WHERE Contenu=:c");
    query1.bindValue(":c", QString::fromStdString(t->getContenu()));

    if(dbOuverte)
    {
        if(!query1.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idTodo dans la BD";
        }
        else
        {
            query1.first();
            QString qidTodo=query1.value(0).toString();
            string a =qidTodo.toStdString();
            idTodo = stoi(a);
            qDebug()<<"Requete2 reussie";
            qDebug()<<idTodo;
        }

        QSqlQuery query2;
        query2.prepare("DELETE FROM InteractionTodo WHERE IdTodo=:x;");
        query2.bindValue(":x", QString::number(idTodo));
        if(!query2.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la suppression du InteractionTodo dans la BD";
        }

        QSqlQuery query3;
        query3.prepare("DELETE FROM Todo WHERE IdTodo=:h;");
        query3.bindValue(":h", QString::number(idTodo));
        if(!query3.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la suppression du todo dans la BD";
        }
    }

}


void GestionBD::RemplirListeTodos(std::vector<Todo*>* listeTodos, Interaction* i)
{
    qDebug()<<QString::fromStdString(i->getContenu());
    listeTodos->clear();
    if(dbOuverte)
    {
        int idInteraction;
        QSqlQuery query1;
        query1.prepare("SELECT IdInteraction from Interaction WHERE Contenu = :c");
        query1.bindValue(":c", QString::fromStdString(i->getContenu()));

        if(!query1.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la selection d'idInteraction dans la BD";
        }
        else
        {
            query1.first();
            QString qidInteraction=query1.value(0).toString();
            string a =qidInteraction.toStdString();
            idInteraction = stoi(a);
            qDebug()<<"Requete2 reussie";
            qDebug()<<idInteraction;
        }

        QSqlQuery query2;
        query2.prepare("SELECT Contenu, Date FROM Todo, InteractionTodo WHERE InteractionTodo.IdInteraction = :i AND InteractionTodo.IdTodo = Todo.IdTodo");
        query2.bindValue(":i", QString::number(idInteraction));
        if(!query2.exec())
        {
            try {
                throw std::exception();
            } catch (std::exception e) {
                qDebug()<<"catch"<< e.what();
            }
            qDebug()<<"Impossible d'éxecuer la lecture des contacts dans la BD";
        }
        else
        {
            qDebug()<<"Requete reussie";

            while (query2.next())
            {
                QString qContenu=query2.value(0).toString();
                string contenu = qContenu.toStdString();
                QString qDate=query2.value(1).toString();
                string date = qDate.toStdString();
                string jour = "";
                jour = jour+date[0]+date[1];
                string mois = "";
                mois = mois+date[3]+date[4];
                string annee = "";
                annee = annee+date[6]+date[7]+date[8]+date[9];

                time_t tn = time(0);
                tm * newdate = localtime(&tn);
                newdate->tm_mday = stoi(jour);
                newdate->tm_mon = stoi(mois)-1;
                newdate->tm_year = stoi(annee)-1900;
                Todo* todo = new Todo(contenu, stoi(jour),stoi(mois)-1,stoi(annee)-1900);

                listeTodos->push_back(todo);
            }
        }
    }
}

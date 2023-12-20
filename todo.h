#ifndef TODO_H
#define TODO_H

#include <string>
#include <ctime>

/**
 * @brief La classe Todo contient un contenu ainsi qu'une date.
 */
class Todo
{
    private:
        std::string contenu;
        tm* date;
    public:
        Todo(std::string c);
        Todo(std::string c, tm* date);
        Todo(std::string c,int jour,int mois, int annee);

        void setContenu(std::string c);

        const std::string getContenu();
        const tm* getDate();


        void ConversionStringDate(std::string &texte, tm* date);
        friend std::ostream& operator<<(std::ostream& , const Todo&);
};


#endif

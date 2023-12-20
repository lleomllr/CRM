#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();
    Ui::PopUp *ui;

private slots:
    void afficherNbContacts(QString);
    void afficherMessage(QString message);
};

#endif // POPUP_H

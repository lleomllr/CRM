#include "popup.h"
#include "ui_popup.h"

PopUp::PopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::afficherNbContacts(QString message)
{
    ui->informations->setText(message);
}

void PopUp::afficherMessage(QString message)
{
    ui->informations->setText(message);
}

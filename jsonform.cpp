#include "jsonform.h"
#include "ui_jsonform.h"

JsonForm::JsonForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JsonForm)
{
    ui->setupUi(this);
    this->ui->boutonOK->setEnabled(false);
}

JsonForm::~JsonForm()
{
    delete ui;
}



void JsonForm::on_boutonChoix_clicked()
{
    fileDialog = new QFileDialog();
    fileDialog->setAttribute(Qt::WA_DeleteOnClose);
    fileDialog->setWindowModality(Qt::ApplicationModal);
    QString filtre = "PNG File (*.png) ;; JPG File (*.jpg)";
    QString chemin = fileDialog->getExistingDirectory();
    qDebug() << "Chemin selectionné : " << chemin;
    ui->lineChemin->setText(chemin);
    ui->boutonOK->setEnabled(1);
}


void JsonForm::on_boutonOK_clicked()
{
    QString chemin = ui->lineChemin->text();
    emit exporterJson(chemin);
    this->ui->msglabel->setText("Export vers "+chemin+" réussi !");
}


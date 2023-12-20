#ifndef JSONFORM_H
#define JSONFORM_H

#include <QWidget>
#include <qfiledialog.h>
#include <qdebug.h>

namespace Ui {
class JsonForm;
}

class JsonForm : public QWidget
{
    Q_OBJECT

public:
    explicit JsonForm(QWidget *parent = nullptr);
    ~JsonForm();

    Ui::JsonForm *ui;
    QFileDialog * fileDialog;

public slots:

    void on_boutonChoix_clicked();



signals:
    void  exporterJson(QString);

private slots:
    void on_boutonOK_clicked();
};

#endif // JSONFORM_H

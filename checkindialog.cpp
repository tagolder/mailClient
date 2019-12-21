#include "checkindialog.h"
#include "ui_checkindialog.h"

CheckInDialog::CheckInDialog(QString login_p, QString password_p, QWidget *parent) :
    QDialog(parent),login(login_p), password(password_p),
    ui(new Ui::CheckInDialog)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec(QString("call get_postal_offices"));
    QSqlQueryModel * modelOffices = new QSqlQueryModel;

    modelOffices->setQuery(query);

    qDebug() << modelOffices->rowCount();
    for(int i = 0; i < modelOffices->rowCount(); i++)
    {
        ui->postalIndexComboBox->addItem(modelOffices->index(i, 0).data().toString() + " " + modelOffices->index(i, 1).data().toString());
    }

}

CheckInDialog::~CheckInDialog()
{
    delete ui;
}

void CheckInDialog::on_checkInButton_clicked()
{
    phoneNumber = ui->phoneNumberEdit->text();
    fio = ui->fioEdit->text();
    indexPostalOffice = ui->postalIndexComboBox->currentIndex() + 1;

    if(fio != "" && phoneNumber != "" && indexPostalOffice != 0)
    {
        qDebug() << fio << phoneNumber << QString::number(indexPostalOffice) << login << password;
        QSqlQuery query;
        query.exec(QString("call create_new_client('%1', '%2', '%3', '%4', '%5')")
                   .arg(fio, phoneNumber, QString::number(indexPostalOffice), login, password));
        this->close();
    }
}



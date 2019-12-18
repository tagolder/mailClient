#include "checkindialog.h"
#include "ui_checkindialog.h"

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
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
    fio = ui->phoneNumberEdit->text();
    phoneNumber = ui->fioEdit->text();
    indexPostalOffice = ui->postalIndexComboBox->currentIndex() + 1;

    if(fio != "" && phoneNumber != "" && indexPostalOffice != 0)
    {
        this->close();
    }
}

QString CheckInDialog::getFIO()
{
    return fio;
}

QString CheckInDialog::getPhoneNumber()
{
    return phoneNumber;
}

int CheckInDialog::getIndexPostalOffice()
{
    return indexPostalOffice;
}

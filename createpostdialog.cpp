#include "createpostdialog.h"
#include "ui_createpostdialog.h"

createPostDialog::createPostDialog(QString userName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createPostDialog)
{
    login = userName;
    ui->setupUi(this);

    QSqlQuery query;
    query.exec(QString("call get_forms"));
    QSqlQueryModel * modelForms = new QSqlQueryModel;

    modelForms->setQuery(query);

    qDebug() << modelForms->rowCount();
    for(int i = 0; i < modelForms->rowCount(); i++)
    {
        ui->formComboBox->addItem(modelForms->index(i, 1).data().toString());
    }

    query.exec(QString("call get_clients_for_client('%1')").arg(login));
    QSqlQueryModel * modelClients = new QSqlQueryModel;

    modelClients->setQuery(query);

    qDebug() << modelClients->rowCount();

    for(int i = 0; i < modelClients->rowCount(); i++)
    {
        ui->repComboBox->addItem(modelClients->index(i, 1).data().toString() + " " + modelClients->index(i, 2).data().toString());
    }
}

createPostDialog::~createPostDialog()
{
    delete ui;
}

void createPostDialog::on_createButton_clicked()
{
    QSqlQuery query;
    query.exec(QString("call get_forms"));
    QSqlQueryModel * modelForms = new QSqlQueryModel;
    modelForms->setQuery(query);

    QSqlQuery queryClients;
    queryClients.exec(QString("call get_clients_for_client('%1')").arg(login));
    QSqlQueryModel * modelClients = new QSqlQueryModel;
    modelClients->setQuery(queryClients);

    if(ui->formComboBox->currentIndex() != -1 && ui->repComboBox->currentIndex() != -1 && ui->weightSpinBox->value() != 0.0)
    {
        QSqlQuery queryNewPost;

        QString id_form = modelForms->index(ui->formComboBox->currentIndex(), 0).data().toString();
        QString id_recipient = modelClients->index(ui->repComboBox->currentIndex(), 0).data().toString();

        queryNewPost.exec(QString("call insert_into_waiting('%1', '%2', '%3', '%4')")
                .arg(id_form, login, id_recipient, QString::number(ui->weightSpinBox->value())));
        this->close();
    }
}

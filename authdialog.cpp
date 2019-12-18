#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::on_authButton_clicked()
{
    userName = ui->editName->text();
    userPassword = ui->editPassword->text();

    QSqlQuery query;
    query.exec(QString("call get_client_password('%1')")
               .arg(userName));
    QSqlQueryModel * modelPassword = new QSqlQueryModel;
    modelPassword->setQuery(query);

    qDebug() << "userPassword : " << userPassword;
    qDebug() << "modelPassword : " << modelPassword->rowCount();
    qDebug() << "userName : " << userName;
    if(userName != "" && userPassword != "")
    {
        if(modelPassword->rowCount() == 0)
        {
            needCheckIn = true;
            this->close();
        }
        else if(userPassword == modelPassword->index(0,0).data().toString())
        {
            this->close();
        }
    }
}

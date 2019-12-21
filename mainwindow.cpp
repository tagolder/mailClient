#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    initDataBase();

    AuthDialog * dia = new AuthDialog(this);
    dia->exec();

    login = dia->getUserName();
    password = dia->getUserPassword();

    if(dia->getNeedCheckIn())
    {        
        CheckInDialog * checkInDialog = new CheckInDialog(login, password, this);
        checkInDialog->exec();
    }

    ui->setupUi(this);

    postalItems->addTab(tab1, "Созданные");

    postalItems->addTab(tab2, "Отправленные мной");

    postalItems->addTab(tab3, "Отправленные мне");

    postalItems->setUsesScrollButtons(false);


    connect(postalItems, SIGNAL(currentChanged(int)), this, SLOT(clickTabWidget(int)));


    ui->verticalLayout->addWidget(postalItems);

    centralWidget()->setLayout(ui->gridLayout);

    QSqlQuery queryWaitPostal;
    QSqlQuery querySandToPostal;
    QSqlQuery querySandFromPostal;

    queryWaitPostal.exec(QString("call get_client_postals_waiting('%1')")
               .arg(login));
    modelWaitPostal->setQuery(queryWaitPostal);
    tab1->setModel(modelWaitPostal);
    tab1->resizeColumnsToContents();
    tab1->resizeRowsToContents();
    tab1->horizontalHeader()->setStretchLastSection(true);

    querySandToPostal.exec(QString("call get_client_postals('%1')")
                           .arg(login));
    modelSandToPostal->setQuery(querySandToPostal);
    tab2->setModel(modelSandToPostal);
    tab2->resizeColumnsToContents();
    tab2->resizeRowsToContents();
    tab2->horizontalHeader()->setStretchLastSection(true);


    querySandFromPostal.exec(QString("call get_to_client_postals('%1')")
                             .arg(login));
    modelSandFromPostal->setQuery(querySandFromPostal);
    tab3->setModel(modelSandFromPostal);
    tab3->resizeColumnsToContents();
    tab3->resizeRowsToContents();
    tab3->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDataBase()
{
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("taya");
    db.setDatabaseName("mail");

    db.open();
}

void MainWindow::on_createButton_clicked()
{
    createPostDialog * postDialog = new createPostDialog(login);
    postDialog->exec();

    QSqlQuery queryWaitPostal;
    queryWaitPostal.exec(QString("call get_client_postals_waiting('%1')")
               .arg(login));
    modelWaitPostal->setQuery(queryWaitPostal);
    tab1->setModel(modelWaitPostal);
}

void MainWindow::clickTabWidget(int index)
{
    qDebug() << "func, index : " << index;
    switch (index) {
    case 0:
    {
        QSqlQuery queryWaitPostal;
        queryWaitPostal.exec(QString("call get_client_postals_waiting('%1')")
                   .arg(login));
        modelWaitPostal->setQuery(queryWaitPostal);
        tab1->setModel(modelWaitPostal);
        ui->dropButton->setEnabled(true);
        break;
    }
    case 1:
    {
        QSqlQuery querySandToPostal;
        querySandToPostal.exec(QString("call get_client_postals('%1')")
                               .arg(login));
        modelSandToPostal->setQuery(querySandToPostal);
        tab2->setModel(modelSandToPostal);
        ui->dropButton->setEnabled(false);
        break;
    }
    case 2:
    {
        QSqlQuery querySandFromPostal;
        querySandFromPostal.exec(QString("call get_to_client_postals('%1')")
                                 .arg(login));
        modelSandFromPostal->setQuery(querySandFromPostal);
        tab3->setModel(modelSandFromPostal);
        ui->dropButton->setEnabled(false);
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_dropButton_clicked()
{

    QSqlQuery queryDeleteRow;
    QString index = modelWaitPostal->index(tab1->selectionModel()->currentIndex().row(), 0).data().toString();

    QMessageBox * pMes =  new QMessageBox(QMessageBox::Question, "Удалить отправление",
                                          "Хотите удалить отправление с индексом : " + index + " ?",
                                          QMessageBox::Yes | QMessageBox::No, this);

    if(pMes->exec() == QMessageBox::Yes)
    {
        queryDeleteRow.exec(QString("call delete_postal_wait('%1')")
                   .arg(index));

        QSqlQuery queryWaitPostal;
        queryWaitPostal.exec(QString("call get_client_postals_waiting('%1')")
                   .arg(login));
        modelWaitPostal->setQuery(queryWaitPostal);
        tab1->setModel(modelWaitPostal);
    }

}

void MainWindow::on_exitAkkButton_clicked()
{
    AuthDialog * dia = new AuthDialog(this);
    dia->exec();

    login = dia->getUserName();
    password = dia->getUserPassword();

    QSqlQuery queryWaitPostal;
    QSqlQuery querySandToPostal;
    QSqlQuery querySandFromPostal;

    if(dia->getNeedCheckIn())
    {
        CheckInDialog * checkInDialog = new CheckInDialog(login, password, this);
        checkInDialog->exec();
    }

    queryWaitPostal.exec(QString("call get_client_postals_waiting('%1')")
               .arg(login));
    modelWaitPostal->setQuery(queryWaitPostal);
    tab1->setModel(modelWaitPostal);

    querySandToPostal.exec(QString("call get_client_postals('%1')")
                           .arg(login));
    modelSandToPostal->setQuery(querySandToPostal);
    tab2->setModel(modelSandToPostal);

    querySandFromPostal.exec(QString("call get_to_client_postals('%1')")
                             .arg(login));
    modelSandFromPostal->setQuery(querySandFromPostal);
    tab3->setModel(modelSandFromPostal);

}

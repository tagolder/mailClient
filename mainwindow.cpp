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

    QSqlQuery query;

    if(dia->getNeedCheckIn())
    {        
        CheckInDialog * checkInDialog = new CheckInDialog(this);
        checkInDialog->exec();
        QString fio = checkInDialog->getFIO();
        QString phoneNumber = checkInDialog->getPhoneNumber();
        int indexPostalOffice = checkInDialog->getIndexPostalOffice();

        query.exec(QString("call create_new_client('%1', '%2', '%3', '%4', '%5')")
                   .arg(fio, phoneNumber, QString::number(indexPostalOffice), login, password));
    }

    ui->setupUi(this);


    QTabWidget * postalItems = new QTabWidget;

    QTableView * tab1 = new QTableView;
    postalItems->addTab(tab1, "Созданные");

    QTableView * tab2 = new QTableView;
    postalItems->addTab(tab2, "Отправленные мной");

    QTableView * tab3 = new QTableView;
    postalItems->addTab(tab3, "Отправленные мне");

    QTableView * tab4 = new QTableView;
    postalItems->addTab(tab4, "Пришедшие");

    QTableView * tab5 = new QTableView;
    postalItems->addTab(tab5, "Полученные");

    postalItems->setUsesScrollButtons(false);

    ui->verticalLayout->addWidget(postalItems);

    centralWidget()->setLayout(ui->gridLayout);

    query.exec(QString("call get_client_postals_waiting('%1')")
               .arg(login));

    modelWaitPostal->setQuery(query);
    tab1->setModel(modelWaitPostal);

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
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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

}



MainWindow::~MainWindow()
{
    delete ui;
}
\

void MainWindow::on_exitAkkButton_clicked()
{
    if(ui->exitAkkButton->text() == "Войти")
    {
        QDialog * dialogAuth = new QDialog();

        QVBoxLayout *dialogAuthLayout = new QVBoxLayout;

        QLabel * labelLogin = new QLabel("Логин :");
        QLineEdit * editLogin = new QLineEdit;
        QLabel * labelPassword = new QLabel("Пароль :");
        QLineEdit * editPassword = new QLineEdit;

        QDialogButtonBox *btn_box = new QDialogButtonBox(dialogAuth);
        btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        connect(btn_box, &QDialogButtonBox::accepted, dialogAuth, &QDialog::accept);
        connect(btn_box, &QDialogButtonBox::rejected, dialogAuth, &QDialog::reject);

        dialogAuth->setWindowFlags(Qt::CustomizeWindowHint);
        dialogAuth->setWindowTitle("Вход");
        dialogAuth->setGeometry(690,360,540,360);

        dialogAuthLayout->addWidget(labelLogin);
        dialogAuthLayout->addWidget(editLogin);
        dialogAuthLayout->addWidget(labelPassword);
        dialogAuthLayout->addWidget(editPassword);
        dialogAuthLayout->addWidget(btn_box);

        dialogAuth->setLayout(dialogAuthLayout);

        QFile file("/home/ya/mailClient/dialogAuth.css");
        file.open(QIODevice::ReadOnly);

        QString cssDialog = file.readAll();

        qDebug()  << cssDialog;

        file.close();

        dialogAuth->setStyleSheet(cssDialog);

        if(dialogAuth->exec() == QDialog::Accepted)
        {
           login = editLogin->text();
           password = editPassword->text();
           if(login != "" && password != "")
           {
              ui->exitAkkButton->setText("Выйти");
           }
        }
    }
    else
    {
        login = "";
        password = "";
        ui->exitAkkButton->setText("Войти");
    }
}

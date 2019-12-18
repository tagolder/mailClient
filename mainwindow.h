#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableView>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFile>
#include <QDebug>
#include "authdialog.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "checkindialog.h"
#include "createpostdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void on_exitAkkButton_clicked();

    void on_createButton_clicked();

private:
    Ui::MainWindow *ui;

    QString login = "";
    QString password = "";

    void initDataBase();
//    QSqlQuery query;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QSqlQueryModel * modelPassword = new QSqlQueryModel;
    QSqlQueryModel * modelWaitPostal = new QSqlQueryModel;

};

#endif // MAINWINDOW_H

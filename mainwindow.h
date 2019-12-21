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
#include <QPalette>
#include <QMessageBox>

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

    void on_createButton_clicked();
    void clickTabWidget(int index);

    void on_dropButton_clicked();

    void on_exitAkkButton_clicked();

private:
    Ui::MainWindow *ui;

    QString login = "";
    QString password = "";

    QTabWidget * postalItems = new QTabWidget;
    QTableView * tab1 = new QTableView;
    QTableView * tab2 = new QTableView;
    QTableView * tab3 = new QTableView;

    void initDataBase();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QSqlQueryModel * modelPassword = new QSqlQueryModel;
    QSqlQueryModel * modelWaitPostal = new QSqlQueryModel;
    QSqlQueryModel * modelSandToPostal = new QSqlQueryModel;
    QSqlQueryModel * modelSandFromPostal = new QSqlQueryModel;
};

#endif // MAINWINDOW_H

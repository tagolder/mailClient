#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class CheckInDialog;
}

class CheckInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInDialog(QString login, QString password,QWidget *parent = 0);
    ~CheckInDialog();

private slots:

    void on_checkInButton_clicked();

private:
    Ui::CheckInDialog *ui;
    QString fio = "";
    QString phoneNumber = "";
    int indexPostalOffice = 0;
    QString login = "";
    QString password = "";
};

#endif // CHECKINDIALOG_H

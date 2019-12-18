#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

    QString getUserName()
    {
        return userName;
    }

    QString getUserPassword()
    {
        return userPassword;
    }

    bool getNeedCheckIn()
    {
        return needCheckIn;
    }

private slots:
    void on_authButton_clicked();

private:
    Ui::AuthDialog *ui;
    QString userName = "";
    QString userPassword = "";
    bool needCheckIn = false;
};

#endif // AUTHDIALOG_H

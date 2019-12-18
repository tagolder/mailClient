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
    explicit CheckInDialog(QWidget *parent = 0);
    ~CheckInDialog();

    QString getFIO();
    QString getPhoneNumber();
    int getIndexPostalOffice();

private slots:

    void on_checkInButton_clicked();

private:
    Ui::CheckInDialog *ui;
    QString fio = "";
    QString phoneNumber = "";
    int indexPostalOffice = 0;
};

#endif // CHECKINDIALOG_H

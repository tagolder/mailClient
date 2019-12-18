#ifndef CREATEPOSTDIALOG_H
#define CREATEPOSTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QDebug>

namespace Ui {
class createPostDialog;
}

class createPostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createPostDialog(QString login, QWidget *parent = 0);
    ~createPostDialog();

private slots:
    void on_createButton_clicked();

private:
    Ui::createPostDialog *ui;
    QString login = "";
};

#endif // CREATEPOSTDIALOG_H

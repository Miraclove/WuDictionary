#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include<QMessageBox>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QString>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    bool registerUser(QString username,QString password);
    void on_pushButton_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H

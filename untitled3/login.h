#ifndef LOGIN_H
#define LOGIN_H
#include<QPropertyAnimation>
#include <QWidget>
#include<iostream>
#include<QDebug>
#include<QMenu>
#include<QAction>
#include<QMessageBox>
#include"register.h"
using namespace std;
#include"widget.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void register_clicked();

    bool loginUser(QString,QString);
    void on_pushButton_3_clicked();

private:
    QMenu *menu;
    QAction *click;
    Ui::Login *ui;
    Widget *widget;
    QPropertyAnimation *out;
    QPropertyAnimation *in;

};

#endif // LOGIN_H

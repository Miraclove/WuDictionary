#include "login.h"
#include "ui_login.h"
#include "widget.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    widget = new Widget;
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    menu = new QMenu;
    click = new QAction("注册",this);
    menu->addAction(click);
    connect(click,SIGNAL(triggered()),this,SLOT(register_clicked()));
    ui->pushButton_2->setMenu(menu);
    //退出动画
    in = new QPropertyAnimation(widget,"windowOpacity");
    in->setDuration(300);
    in->setStartValue(0);
    in->setEndValue(1);
    //进入下一页面动画
    out = new QPropertyAnimation(this,"windowOpacity");
    connect(out,&QPropertyAnimation::finished,[=]{
        this->close();
        widget->Initial(ui->lineEdit->text());
        in->start();
        widget->show();
    });
    out->setDuration(300);
    out->setStartValue(1);
    out->setEndValue(0);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(loginUser(ui->lineEdit->text(),ui->lineEdit_2->text())){
        out->start();
    }else{
        QMessageBox::warning(nullptr,"Error","用户名或密码错误!");
    }
}

void Login::on_pushButton_2_clicked()
{

}

void Login::register_clicked()
{
    Register *re = new Register;
    re->show();
}
//登录数据库查询用户名密码是否正确
bool Login::loginUser(QString username, QString password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        QSqlQuery query(db);
        QString S =QString("select * from user where name='%1' and password='%2' ").arg(username).arg(password);
        query.exec(S);
        if(query.first()){
            db.close();
            return true;
        }
    }else {
        QMessageBox::warning(nullptr,"Error","Database error!");
    }
    db.close();
    return false;
}

void Login::on_pushButton_3_clicked()
{
    this->close();
}

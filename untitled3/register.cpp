#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    this->setWindowRole("注册");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->pushButton->setDisabled(true);
}

Register::~Register()
{
    delete ui;
}

void Register::on_lineEdit_textChanged(const QString &arg1)
{

}

void Register::on_pushButton_clicked()
{
    registerUser(ui->lineEdit->text(),ui->lineEdit_2->text());
}
//在数据库中注册用户
bool Register::registerUser(QString username,QString password){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("000504");
    if(db.open()){
        QSqlQuery query(db);
        QString i = QString("insert into user(name,password) values ('%1','%2');").arg(username).arg(password);
        QString S = QString("select * from user where name='%1';").arg(username);
        if(query.exec(i)){
            QMessageBox::information(nullptr, "Success", "注册成功!", QMessageBox::Yes);
            this->close();
            db.close();
            return true;
        }else if (query.exec(S)&&query.first()) {
            QMessageBox::warning(nullptr,"Error","用户名已使用!");
        }else {
            QMessageBox::warning(nullptr,"Error","注册失败!");
        }
    }else {
        QMessageBox::warning(nullptr,"Error","数据库错误!");
    }
    db.close();
    return false;
}

void Register::on_lineEdit_3_textChanged(const QString &arg1)
{
    ui->pushButton->setDisabled(true);
    if(ui->lineEdit_2->text().length()<6){
        ui->label_5->setText("少于6位!");
    }else {
        ui->label_5->setText(" √ ");
    }
    if(ui->lineEdit_2->text()==ui->lineEdit_3->text()){
        ui->label_6->setText("密码匹配!");
        if(ui->lineEdit_2->text().length()>=6){
            ui->pushButton->setDisabled(false);
        }
    }else if(ui->lineEdit_3->text().length()>0){
        ui->label_6->setText("密码不匹配！");
    }
}

void Register::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->pushButton->setDisabled(true);
    if(ui->lineEdit_2->text().length()<6){
        ui->label_5->setText("少于6位!");
    }else {
        ui->label_5->setText(" √ ");
    }
    if(ui->lineEdit_2->text()==ui->lineEdit_3->text()){
        ui->label_6->setText("密码匹配!");
        if(ui->lineEdit_2->text().length()>=6){
            ui->pushButton->setDisabled(false);
        }
    }else if(ui->lineEdit_3->text().length()>0){
        ui->label_6->setText("密码不匹配");
    }
}

void Register::on_pushButton_2_clicked()
{
    this->close();
}

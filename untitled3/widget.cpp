#include "widget.h"
#include "ui_widget.h"
#include "login.h"
#include<algorithm>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置无边框显示
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置菜单按钮
    ui->pushButton->setFlat(true);
    ui->pushButton_2->setFlat(true);
    ui->pushButton_3->setFlat(true);
    //设置初始显示页面
    ui->stackedWidget->setCurrentIndex(0);
    //界面初始设置
    ui->listWidget->hide();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //咨询初始化
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pushButton_9->setText("国外流行一种新煮饭方式能让卡路里减半");
    ui->pushButton_10->setText("这10种食物会让你更快变老，你都吃吗？");
    QImage *image;
    image = new QImage();
    if(image->load("C:/Users/24957/Documents/untitled3/info00.jpg"));
    {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*image).scaled(131,61,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        ui->graphicsView_2->setScene(scene);
        ui->graphicsView_2->resize(131, 61);
        ui->graphicsView_2->show();
    }
    if(image->load("C:/Users/24957/Documents/untitled3/info01.jpg"));
    {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*image).scaled(131,61,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        ui->graphicsView_3->setScene(scene);
        ui->graphicsView_3->resize(131, 61);
        ui->graphicsView_3->show();
    }
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(windowclosed()));
    menu = new QMenu;
    click = new QAction("设置",this);
    menu->addAction(click);
    ui->pushButton_6->setMenu(menu);
    //给是否移动的标志初始化为false.
    m_move = false;
    //用户名和头像初始化
    userName = "administrator";
    headImage = "C:/Users/24957/Documents/untitled3/defaultheadimage.jpg";
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Initial(QString username)
{
    //设置用户个人信息

    userName=username;
    ui->label_2->setText(userName);
    //设置用户单词本
    ui->label_6->setText(userName+"的单词本");
    ifstream in("C:/Users/24957/Documents/untitled3/"+username.toStdString()+".txt");
    if(!in.is_open()){
        qDebug()<<"FileOpenError";
        return;
    }
    string str;
    string imagepath="";
    if(!in.eof()){
        in>>imagepath;
    }
    while (!in.eof()) {
        string temp1;
        string temp2;
        in>>temp1;
        in>>temp2;
        if(temp1!=""){
            UserDictionary.insert(temp1,temp2);
            qDebug()<<"导入用户"+username+"的单词：";
            cout<<"("<<temp1<<","<<temp2<<")";
        }
    }
    cout<<endl;
    //设置头像和用户名
    QImage *image;
    image = new QImage();
    if(imagepath!=""){
        headImage=QString::fromStdString(imagepath);
    }
    if(image->load(headImage))
    {

        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(*image).scaled(31,31,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        ui->graphicsView->setScene(scene);
        ui->graphicsView->resize(31, 31);
        ui->graphicsView->show();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
        if (event->button() == Qt::LeftButton)
        {
            m_move = true;
            //记录鼠标的世界坐标.
            m_startPoint = event->globalPos();
            //记录窗体的世界坐标.
            m_windowPoint = this->frameGeometry().topLeft();
        }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
        {
            //移动中的鼠标位置相对于初始位置的相对位置.
            QPoint relativePos = event->globalPos() - m_startPoint;
            //然后移动窗体即可.
            this->move(m_windowPoint + relativePos );
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        {
            //改变移动状态.
            m_move = false;
        }
}
//咨询页面按钮
void Widget::on_pushButton_clicked()
{
    ui->pushButton->setDown(true);
    ui->pushButton_2->setDown(false);
    ui->pushButton_3->setDown(false);
    //切换页面
    ui->stackedWidget->setCurrentIndex(0);

}
//查找页面按钮
void Widget::on_pushButton_2_clicked()
{
    ui->pushButton_2->setDown(true);
    ui->pushButton->setDown(false);
    ui->pushButton_3->setDown(false);
    //切换页面
    ui->stackedWidget->setCurrentIndex(1);
}
//用户单词本按钮
void Widget::on_pushButton_3_clicked()
{
    ui->pushButton_3->setDown(true);
    ui->pushButton->setDown(false);
    ui->pushButton_2->setDown(false);
    //切换页面
    ui->stackedWidget->setCurrentIndex(2);
    ui->listWidget_2->clear();
    map<string,string> Map = UserDictionary.toMap();
    map<string,string>::iterator iter;
    for(iter = Map.begin(); iter != Map.end(); iter++){
        QListWidgetItem *addItem = new QListWidgetItem(ui->listWidget_2);
        addItem->setText(QString::fromStdString(iter->first +"           "+ iter->second));
    }
}
//查找界面单词输入，对单词预测
void Widget::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->listWidget->clear();
    if(ui->lineEdit_2->text().length()>1){
        //在字典树中查找
        vector<string> temp = trie.getPreString(ui->lineEdit_2->text().toStdString());
        //添加到列表当中
        if(ui->lineEdit_2->text()!=""&&temp.size()!=0){
            for(auto&str:temp){
                QListWidgetItem *addItem = new QListWidgetItem(ui->listWidget);
                addItem->setText(QString::fromStdString(str));
            }
            ui->listWidget->show();
        }
    }
    else {
        ui->listWidget->hide();
    }

}

//对列表中的单词点击
void Widget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug()<<item->text()<<endl;
    //切换界面
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_7->setText(item->text());
    //查找单词在页面中显示，哈希查找
    ui->label_8->setText(QString::fromStdString(DictionaryMap.find(item->text().toStdString())));
    ui->listWidget->clearSelection();
}
//顶栏快速搜索按钮
void Widget::on_pushButton_4_clicked()
{
    qDebug()<<"target:"<<ui->lineEdit->text();
    ui->stackedWidget->setCurrentIndex(3);
    string temp = DictionaryMap.find(ui->lineEdit->text().toStdString());
    if(temp!=""){
        qDebug()<<"find";
        ui->label_7->setText(ui->lineEdit->text());
        ui->label_8->setText(QString::fromStdString(temp));
    }else{
        qDebug()<<"notfind";
        ui->label_7->setText("未找到该单词！");
        ui->label_8->setText("");
    }
}
//更改用户头像
void Widget::on_pushButton_5_clicked()
{
    QImage *image;
    image = new QImage();
    QString fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
    if(fileName != "")
    {
        if(image->load(fileName))
        {
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(*image).scaled(31,31,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            ui->graphicsView->setScene(scene);
            ui->graphicsView->resize(31, 31);
            ui->graphicsView->show();
        }
    }
    headImage = fileName;
    qDebug()<<"filepath:"<<headImage<<endl;
}
//窗口关闭
void Widget::windowclosed()
{
    //保存用户单词本
    ofstream out("C:/Users/24957/Documents/untitled3/"+userName.toStdString()+".txt");
    if(!out){
        qDebug()<<"FileOpenError";
        return;
    }
    out<<headImage.toStdString()<<endl;
    map<string,string> Map = UserDictionary.toMap();
    map<string,string>::iterator iter;
    for(iter = Map.begin(); iter != Map.end(); iter++){
        out<<iter->first<<" "<<iter->second<<endl;
    }
    this->close();
}

//咨询页面导入单词按钮
void Widget::on_pushButton_7_clicked()
{
    ifstream in("C:/Users/24957/Documents/untitled3/afterword.txt");
    if(!in.is_open()){
        qDebug()<<"FileOpenError";
        return;
    }
    string str;
    while (!in.eof()) {
        string temp1;
        string temp2;
        in>>temp1;
        in>>temp2;
        DictionaryMap.insert(temp1,temp2);
        cout<<"("<<temp1<<","<<temp2<<")";
        trie.insertString(temp1);
        cout<<"<"<<temp1<<">";
    }
    cout<<endl;
}
//添加到用户单词表按钮
void Widget::on_pushButton_8_clicked()
{
    UserDictionary.insert(ui->label_7->text().toStdString(),ui->label_8->text().toStdString());
    qDebug()<<"insert "<<ui->label_7->text()<<" to User Dictionary";
}



void Widget::on_pushButton_9_clicked()
{
    QDesktopServices::openUrl(QUrl("http://news.iciba.com/study/bilingual/1579925.shtml"));
}

void Widget::on_pushButton_10_clicked()
{
    QDesktopServices::openUrl(QUrl("http://news.iciba.com/study/bilingual/1579924.shtml"));
}




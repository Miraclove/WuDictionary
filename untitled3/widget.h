#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QListWidgetItem>
#include<QFile>
#include<QHBoxLayout>
#include<QSignalMapper>
#include<QDebug>
#include<QFileDialog>
#include<QMessageBox>
#include<QImage>
#include<QPixmap>
#include<QMenu>
#include<QAction>
#include<QPoint>
#include<QMouseEvent>
#include<QDesktopServices>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<QUrl>
#include<stdlib.h>
#include"hashmap.h"
#include"trie.h"
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QString userName;
    QString headImage;
    void Initial(QString username);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void windowclosed();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    QMenu *menu;
    QAction *click;
    Ui::Widget *ui;
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
    HashMap<string,string> DictionaryMap;
    HashMap<string,string> UserDictionary;
    Trie trie;
    vector<string> predictWord(string);
};

#endif // WIDGET_H

#include "widget.h"
#include <QApplication>
#include"login.h"
#include"register.h"
#include"trie.h"
#include<iostream>
#include<QTextCodec>
#include<string>
using namespace std;
#include"hashmap.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Login login;
    login.show();
    return a.exec();

}

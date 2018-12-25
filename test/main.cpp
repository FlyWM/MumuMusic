#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tchar.h>
#include <QDebug>
#include <QTextCodec>
using namespace std;
//#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // test1
    QString str = "E:\\CloudMusic\\1的.mp3";

    QTextCodec *gbk = QTextCodec::codecForName("UTF-8");
    str = gbk->toUnicode(str.toLocal8Bit());

    QByteArray arr1;
    arr1.append(str);
    QString qStr = QString::fromLocal8Bit(str.toLocal8Bit());
    string stdStr = "我是中文";
    string stdStr1;
    string stdStr2 = str.toStdString().c_str();
    stdStr1 = qStr.toLocal8Bit().toStdString();

    fstream f(stdStr1);
    cout << f.is_open() << endl;

    qDebug() << "Test1: \n" << qStr;
    printf("%s\n", stdStr1.data());
    cout << stdStr1 << endl;

    return a.exec();
}

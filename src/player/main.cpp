/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QDesktopWidget>
#include <string>
#include <qtranslator.h>
#include "MuMainWindow.h"
#include "MuStyleHelper.h"
#include "MuTestMainWidget.h"
#include "MuSmallControls.h"
#include "MuDBManager.h"

//#define Test

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName(QStringLiteral("Mumu"));
    QCoreApplication::setApplicationName(QStringLiteral("Mumu Music"));

    QTranslator translator;
    translator.load(":/i18n/zh_cn.qm");
    a.installTranslator(&translator);

    MuDBManager &dbmanager = MuDBManager::getInstance();
    dbmanager.initDB();

    MuUtils::MuStyleHelper::setStyle(":/styles/red.qss");
#if defined(Test)
    MuTestMainWidget w;
    w.show();
#else
    MuMainWindow w;
    w.show();
    w.initPos();
#endif
    return a.exec();
}

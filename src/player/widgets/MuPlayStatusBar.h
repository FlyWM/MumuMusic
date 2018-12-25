/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUPLAYSTATUSBAR_H
#define MUPLAYSTATUSBAR_H

#include <QWidget>

class MuPlayStatusBar : public QWidget
{
    Q_OBJECT
public:
    MuPlayStatusBar(QWidget *parent = nullptr);
};

#endif // MUPLAYSTATUSBAR_H

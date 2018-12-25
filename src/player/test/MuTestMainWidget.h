/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUTESTMAINWIDGET_H
#define MUTESTMAINWIDGET_H

#include <QWidget>

class MuTestCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuTestCentralWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

class MuTestMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuTestMainWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

#endif // MUTESTMAINWIDGET_H

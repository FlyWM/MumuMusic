/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUBASEWIDGET_H
#define MUBASEWIDGET_H

#include <QWidget>

class MuBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuBaseWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // MUBASEWIDGET_H

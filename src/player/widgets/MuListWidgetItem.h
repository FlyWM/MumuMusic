/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MULISTWIDGETITEM_H
#define MULISTWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>

class MuListWidgetItem : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit MuListWidgetItem(QIcon icon, const QString itemName, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MULISTWIDGETITEM_H

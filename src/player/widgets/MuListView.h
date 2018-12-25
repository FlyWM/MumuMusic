/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MULISTVIEW_H
#define MULISTVIEW_H

#include <QListView>

class QStandardItemModel;
class MuListView : public QListView
{
    Q_OBJECT
public:
    MuListView(QWidget *parent = nullptr);

    void updateData(QList<QStringList> data);

private:
    QStandardItemModel *m_pModel;
};

#endif // MULISTVIEW_H

/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUTABLEVIEWHELPER_H
#define MUTABLEVIEWHELPER_H

#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QVariant>

class MuTableViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit MuTableViewModel(QObject *parent = nullptr);

//    int rowCount(const QModelIndex &parent) const;
//    int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
//    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

class MuPushButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MuPushButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

//class MuHeaderView : public QHeaderView
//{
//    Q_OBJECT

//public:
//    explicit MuHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);

//protected:
//    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
//};


#endif // MUTABLEVIEWHELPER_H

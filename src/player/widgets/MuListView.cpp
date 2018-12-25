/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QStandardItemModel>
#include "MuListViewItemDelegate.h"
#include "MuListView.h"
#include "MuGlobal.h"

const QStringList icons = {
    ":/testImages/HotDog.jpg", ":/testImages/li.jpg", ":/testImages/logo.jpg",
    ":/testImages/PACT.jpg", ":/testImages/yang.jpg", ":/testImages/zhang.jpg",
};
const QStringList singers = {
    "MC-Hotdog", CN_STR_("Li Ronghao"), "Author",
    "PACT", CN_STR_("Yang qianhua"), CN_STR_("Zhang zhenyue"),
};
MuListView::MuListView(QWidget *parent)
    : QListView(parent)
{
    m_pModel = new QStandardItemModel(this);
    for (int i=0; i<icons.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        MuListItemData itemData;
        itemData.title = singers.at(i);
        itemData.songsNb = QString::number(i * i) + CN_STR_("");
        itemData.iconPath = icons.at(i);
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
    MuListViewItemDelegate *pItemDelegate = new MuListViewItemDelegate(this);

    this->setModel(m_pModel);
    this->setItemDelegate(pItemDelegate);
}

void MuListView::updateData(QList<QStringList> data)
{
    m_pModel->clear();
    if (data.isEmpty())
        return;

    for (auto &itemData : data) {
        if (itemData.isEmpty() || itemData.size() < 3)
            continue;

        QStandardItem *pItem = new QStandardItem;
        MuListItemData listItemData;
        listItemData.title = itemData.at(0);
        listItemData.songsNb = itemData.at(1);
        listItemData.iconPath = itemData.at(2);
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        m_pModel->appendRow(pItem);
    }
}

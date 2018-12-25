/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QHBoxLayout>
#include <QLabel>
#include "MuListWidgetItem.h"

MuListWidgetItem::MuListWidgetItem(QIcon icon, const QString itemName, QWidget *parent)
    : QWidget(parent)
{
    QLabel *pIconLabel1 = new QLabel(this);
    QLabel *pNameLabel = new QLabel(this);
    QLabel *pIconLabel2 = new QLabel(this);
    pIconLabel1->setPixmap(QPixmap(icon.name()));
    pNameLabel->setText(itemName);
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->addWidget(pIconLabel1);
    pMainLayout->addWidget(pNameLabel);
    pMainLayout->addWidget(pIconLabel2);
}

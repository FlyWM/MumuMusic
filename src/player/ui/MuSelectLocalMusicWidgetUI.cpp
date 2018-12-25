/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QDebug>
#include "MuSelectLocalMusicWidgetUI.h"
#include "ui_MuSelectLocalMusicWidgetUI.h"

MuSelectLocalMusicWidgetUI::MuSelectLocalMusicWidgetUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuSelectLocalMusicWidgetUI)
{
    ui->setupUi(this);
}

MuSelectLocalMusicWidgetUI::~MuSelectLocalMusicWidgetUI()
{
    delete ui;
}

void MuSelectLocalMusicWidgetUI::addItem(const QString &item)
{
    if (item.isEmpty())
        return;

    QCheckBox *pCheckBox = new QCheckBox(this);
    pCheckBox->setCheckable(true);
    pCheckBox->setChecked(true);
    pCheckBox->setText(item);
    pCheckBox->setObjectName("ntvSelectedPathItem");
    ui->scrollVerticalLayout->addWidget(pCheckBox);
}

QStringList MuSelectLocalMusicWidgetUI::getItemsContent() const
{
    QList<QCheckBox *> cbs = this->findChildren<QCheckBox *>();
    QStringList items;
    for (auto &checkBox : cbs) {
        if (checkBox->isChecked())
            items.append(checkBox->text());
    }

    return items;
}

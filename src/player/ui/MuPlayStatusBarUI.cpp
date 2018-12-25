/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "muplaystatusbarui.h"
#include "ui_muplaystatusbarui.h"
#include "MuStyleHelper.h"

MuBaseSlider::MuBaseSlider(QWidget *parent) :
    QSlider(parent)
{

}

void MuBaseSlider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());
}


MuVoiceSlider::MuVoiceSlider(QWidget *parent) :
    MuBaseSlider(parent)
{
    setProperty("mouseEnterPro", false);
    setProperty("valRangePro", "mute");
    setStyle(QApplication::style());    
}

void MuVoiceSlider::enterEvent(QEvent *ev)
{
    Q_UNUSED(ev)

    setProperty("mouseEnterPro", true);
    setStyle(QApplication::style());
}

void MuVoiceSlider::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev)

    setProperty("mouseEnterPro", false);
    setStyle(QApplication::style());
}


MuPlayStatusBarUI::MuPlayStatusBarUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuPlayStatusBarUI),
    m_curPlayOrderIndex(0)
{
    ui->setupUi(this);
    ui->voiceBtn->setProperty("valRangePro", "mute");
    connect(ui->voiceSlider, &MuVoiceSlider::valueChanged, [=](int val) {
        if (val ==0) {
            ui->voiceBtn->setProperty("valRangePro", "mute");
        } else if (val > 0 && val < ui->voiceSlider->maximum()/3) {
            ui->voiceBtn->setProperty("valRangePro", "low");
        } else if (val >= ui->voiceSlider->maximum()/3 && val <= ui->voiceSlider->maximum()*2/3) {
            ui->voiceBtn->setProperty("valRangePro", "medium");
        } else if (val > ui->voiceSlider->maximum()*2/3) {
            ui->voiceBtn->setProperty("valRangePro", "high");
        }
        ui->voiceBtn->setStyle(QApplication::style());
    });

    ui->playOrderBtn->setProperty("playOrderPro", m_playOrderPro.at(m_curPlayOrderIndex));
    ui->playOrderBtn->setStyle(QApplication::style());
    connect(ui->playOrderBtn, &QPushButton::clicked, [=]() {
        ++ m_curPlayOrderIndex;
        m_curPlayOrderIndex = m_curPlayOrderIndex % m_playOrderPro.size();
        ui->playOrderBtn->setProperty("playOrderPro", m_playOrderPro.at(m_curPlayOrderIndex));
        ui->playOrderBtn->setStyle(QApplication::style());
    });

    ui->openListBtn->setText("114");
    ui->openListBtn->setContentsMargins(0, 0, 10, 0);
    ui->preSongBtn->setFixedSize(MuUtils::MuStyleHelper::preSongBtnSize());
    ui->playBtn->setFixedSize(MuUtils::MuStyleHelper::playBtnSize());
    ui->nextSongBtn->setFixedSize(MuUtils::MuStyleHelper::preSongBtnSize());
    MuUtils::MuStyleHelper::playBarButtonAdjustRadius(ui->preSongBtn, ui->playBtn, ui->nextSongBtn);
}

MuPlayStatusBarUI::~MuPlayStatusBarUI()
{
    delete ui;
}

void MuPlayStatusBarUI::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}




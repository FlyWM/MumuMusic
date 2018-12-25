/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include "MuToolbox.h"
#include "MuTestMainWidget.h"
#include "MuSmallControls.h"
#include <qdrawutil.h>
#include <QPainter>
#include <QLayout>

MuTestMainWidget::MuTestMainWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 600);
    setWindowFlag(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);

//    MuTestCentralWidget *widget = new MuTestCentralWidget;
//    QHBoxLayout *layout = new QHBoxLayout(this);
//    layout->addWidget(widget);
}

void MuTestMainWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QColor("red"));
    painter.setBrush(QBrush(QColor("red")));
    QMargins margin(8, 8, 8, 8);
    QMargins margin1(20, 20, 20, 20);
    QPixmap pixMap(":/images/client-shadow.png");
    QRect rect();
//    qDrawBorderPixmap(&painter, this->rect(), margin, pixMap);
    qDrawBorderPixmap(&painter, this->rect(), margin, pixMap, QRect(0, 0, 34, 160), margin1);
}

MuTestCentralWidget::MuTestCentralWidget(QWidget *parent)
{

}

void MuTestCentralWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QColor("red"));
    QMargins margin(8, 8, 8, 8);
    QPixmap pixMap(":/images/client-shadow.png");
    QRect rect();
    qDrawBorderPixmap(&painter, this->rect(), margin, pixMap);
}

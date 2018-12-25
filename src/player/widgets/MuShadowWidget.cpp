/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include "mushadowwidget.h"
#include <QLayout>
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QPainter>

MuGraphicsDropShadowEffectWidget::MuGraphicsDropShadowEffectWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(150, 150);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainWidget = new QWidget(this);
    m_pMainWidget->setStyleSheet(QStringLiteral(" background-color: green; border-radius: 10px;"));
    m_pMainLayout->addWidget(m_pMainWidget);
//    m_pMainLayout->setContentsMargins(5, 5, 5, 5);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(QStringLiteral("#888888")));
    shadow->setBlurRadius(30);
    m_pMainWidget->setGraphicsEffect(shadow);
    m_pMainLayout->setMargin(24);
}

void MuGraphicsDropShadowEffectWidget::setMainWidget(QWidget *widget)
{
    if (widget == nullptr) return;

    m_pMainWidget->deleteLater();
    m_pMainWidget = widget;
    m_pMainWidget->setStyleSheet(QStringLiteral(" background-color: green; "));
}

void MuGraphicsDropShadowEffectWidget::setShadowSize(int size)
{
    Q_UNUSED(size)
}

void MuGraphicsDropShadowEffectWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

//    QPainter painter(this);

//    QStyleOption opt;
//    opt.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

#include <QStyleOption>
#include <QPainter>
#include "MuBaseWidget.h"

MuBaseWidget::MuBaseWidget(QWidget *parent)
    : QWidget(parent)
{

}

void MuBaseWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

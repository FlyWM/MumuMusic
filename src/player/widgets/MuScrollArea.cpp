/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include "MuScrollArea.h"

MuScrollArea::MuScrollArea(QWidget *parent)
    : QScrollArea(parent)
    , m_scrollEnabled(false)
{
    installEventFilter(this);
}

bool MuScrollArea::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::Wheel && !m_scrollEnabled) {
        return true;
    } else if (e->type() == QEvent::Resize) {
        QResizeEvent *re = dynamic_cast<QResizeEvent *>(e);
        if (re != nullptr) {
//            qDebug() << re->size();
        }
    }
    return QScrollArea::eventFilter(o, e);
}

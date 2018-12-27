/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QFile>
#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QSizePolicy>
#include <QListWidgetItem>
#include <QDebug>
#include "mustylehelper.h"

double MuUtils::MuStyleHelper::m_preRate;
double MuUtils::MuStyleHelper::m_scaleFromPreRate;
QSize MuUtils::MuStyleHelper::m_switchSongBtnSize;
QSize MuUtils::MuStyleHelper::m_playSongBtnSize;

MuUtils::MuStyleHelper::MuStyleHelper()
{

}

void MuUtils::MuStyleHelper::setStyle(const QString &qssFile)
{
    QFile qss(qssFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

int MuUtils::MuStyleHelper::MuSmartScaleUI(int spec)
{
    double rate = 0;

    QList<QScreen *> screens = QApplication::screens();
    if (screens.size() > 0) {
        QScreen *screen = screens[0];
        double dpi = screen->logicalDotsPerInch();
        //
        rate = dpi / 96.0;

        if (rate < 1.1) {
            rate = 1.0;
        } else if (rate < 1.4) {
            rate = 1.25;
        } else if (rate < 1.6) {
            rate = 1.5;
        } else if (rate < 1.8) {
            rate = 1.75;
        } else {
            rate = 2.0;
        }
    }
    m_preRate = rate;
    return int(spec * rate);
}

double MuUtils::MuStyleHelper::rate()
{
    double rate = 0;
    QList<QScreen *> screens = QApplication::screens();
    if (screens.size() > 0) {
        QScreen *screen = screens[0];
        double dpi = screen->logicalDotsPerInch();
        //
        rate = dpi / 96.0;

        if (rate < 1.1) {
            rate = 1.0;
        } else if (rate < 1.4) {
            rate = 1.25;
        } else if (rate < 1.6) {
            rate = 1.5;
        } else if (rate < 1.8) {
            rate = 1.75;
        } else {
            rate = 2.0;
        }
    }
    return rate;
}


void MuUtils::MuStyleHelper::setPreRate(const double &preRate)
{
    m_preRate = preRate;
    qDebug() << "preRate: " << preRate;
}

void MuUtils::MuStyleHelper::setScaleFromPreRate(const double &scaleFromPreRate)
{
    m_scaleFromPreRate = scaleFromPreRate;
    qDebug() << "scaleFromPreRate: " << scaleFromPreRate;
}

double MuUtils::MuStyleHelper::preRate()
{
    return m_preRate;
}

double MuUtils::MuStyleHelper::scaleFromPreRate()
{
    return m_scaleFromPreRate;
}

void MuUtils::MuStyleHelper::scaleChildren(QObject &o)
{
    double scaleFromPreRate = rate() / m_preRate;
    for (int i=0; i<o.children().size(); ++i) {
        QWidget *pWidget = qobject_cast<QWidget *>(o.children().at(i));
        if (pWidget != nullptr) {
            if (pWidget->minimumWidth() == pWidget->maximumWidth())
                pWidget->setFixedWidth(pWidget->width()*scaleFromPreRate);
            if (pWidget->minimumHeight() == pWidget->maximumHeight())
                pWidget->setFixedHeight(pWidget->height()*scaleFromPreRate);

            if (pWidget->objectName() == "musicMangeListWidget") {
                QListWidget *pList = qobject_cast<QListWidget *>(pWidget);
                if (pList != nullptr) {
                    for (int i=0; i<pList->count(); ++i) {
                        pList->item(i)->setSizeHint(mangeListItemSize());
                    }
                }
                pList->setFixedHeight(mangeListItemSize().height() * pList->count() + 5);
            }

            scaleChildren(*(o.children().at(i)));
        } /*else {
            QListWidgetItem *pItem = reinterpret_cast<QListWidgetItem *>(o.children().at(i));
            qDebug() << "ITEM: " << pItem << pItem->sizeHint() << o.children().at(i)->objectName();
        }*/
    }
}

QSize MuUtils::MuStyleHelper::mainWindowSize()
{
    QSize size;
#ifdef Q_OS_WIN32
    size.setWidth(MuSmartScaleUI(1022));
    size.setHeight(MuSmartScaleUI(670));
#elif defined Q_OS_LINUX
    size.setWidth(MuSmartScaleUI(1022 + 15*2));
    size.setHeight(MuSmartScaleUI(670 + 15*2));
#endif

    return size;
}

int MuUtils::MuStyleHelper::titileHeight()
{
    return MuSmartScaleUI(50);
}

QSize MuUtils::MuStyleHelper::titleBarIconSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(24));
    size.setHeight(MuSmartScaleUI(24));

    return size;
}

QSize MuUtils::MuStyleHelper::titleBarButtonSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(22));
    size.setHeight(MuSmartScaleUI(18));

    return size;
}

QSize MuUtils::MuStyleHelper::mangeListItemSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(188));
    size.setHeight(MuSmartScaleUI(32));
    return size;
}

QSize MuUtils::MuStyleHelper::mangeListItemIconSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(16));
    size.setHeight(MuSmartScaleUI(16));
    return size;
}

QSize MuUtils::MuStyleHelper::mangeListItemCreateBtnSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(20));
    size.setHeight(MuSmartScaleUI(20));
    return size;
}

QSize MuUtils::MuStyleHelper::mangeListItemOpenListBtnSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(20));
    size.setHeight(MuSmartScaleUI(20));
    return size;
}

int MuUtils::MuStyleHelper::mangeWidgetWidth()
{
    return MuSmartScaleUI(200);
}

int MuUtils::MuStyleHelper::playStatusBarHeight()
{
    return MuSmartScaleUI(48);
}

int MuUtils::MuStyleHelper::rightButtonMenuIconSize()
{
    return MuSmartScaleUI(20);
}

int MuUtils::MuStyleHelper::rightButtonMenuWidth()
{
#ifdef Q_OS_WIN32
    return MuSmartScaleUI(230);
#elif defined Q_OS_LINUX
    return MuSmartScaleUI(230 + 15 * 2);
#endif
}

int MuUtils::MuStyleHelper::dialogBottomHeight()
{
    return MuSmartScaleUI(60);
}

int MuUtils::MuStyleHelper::dialogTitleHeight()
{
    return MuSmartScaleUI(50);
}

QSize MuUtils::MuStyleHelper::searchaBoxSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(172));
    size.setHeight(MuSmartScaleUI(24));
    return size;
}

QSize MuUtils::MuStyleHelper::localMatchButtonSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(90));
    size.setHeight(MuSmartScaleUI(24));
    return size;
}

QSize MuUtils::MuStyleHelper::localTabButtonSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(28));
    size.setHeight(MuSmartScaleUI(24));
    return size;
}

QMargins MuUtils::MuStyleHelper::localTitleLayoutMargins()
{
    QMargins margins(MuSmartScaleUI(32), MuSmartScaleUI(0), MuSmartScaleUI(32), MuSmartScaleUI(6));
    return margins;
}

QSize MuUtils::MuStyleHelper::localSelectNativeFolderButtonSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(192));
    size.setHeight(MuSmartScaleUI(56));
    return size;
}

int MuUtils::MuStyleHelper::localThumbWidgetWidth()
{
    return MuSmartScaleUI(185);
}

QSize MuUtils::MuStyleHelper::localSearchNtvMusicBoxSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(170));
    size.setHeight(MuSmartScaleUI(25));
    return size;
}

QSize MuUtils::MuStyleHelper::localAddMusicDialogSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(300));
    size.setHeight(MuSmartScaleUI(310));
    return size;
}

int MuUtils::MuStyleHelper::localRightMargin()
{
    return MuSmartScaleUI(32);
}

int MuUtils::MuStyleHelper::localTitleBarHeight()
{
    return MuSmartScaleUI(55);
}

int MuUtils::MuStyleHelper::tableViewHeaderHeight()
{
    return MuSmartScaleUI(30);
}

int MuUtils::MuStyleHelper::tableViewItemHeight()
{
    return MuSmartScaleUI(30);
}

QSize MuUtils::MuStyleHelper::preSongBtnSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(30));
    size.setHeight(MuSmartScaleUI(30));
    m_switchSongBtnSize = size;
    return size;
}

QSize MuUtils::MuStyleHelper::playBtnSize()
{
    QSize size;
    size.setWidth(MuSmartScaleUI(34));
    size.setHeight(MuSmartScaleUI(34));
    m_playSongBtnSize = size;
    return size;
}

void MuUtils::MuStyleHelper::playBarButtonAdjustRadius(QPushButton *preBtn, QPushButton *playBtn, QPushButton *nextBtn)
{
    if (preBtn == nullptr || playBtn == nullptr || nextBtn == nullptr)
        return;

    preBtn->setStyleSheet(QString(" QPushButton { \
                                        background-color: #e83c3c; \
                                        border: none; \
                                        border-radius: %1px; \
                                        padding: %2px;\
                                        image: url(:/images/preSontBtn48_White.png);\
                                    }                         \
                                    QPushButton:hover { \
                                        background-color: #c62f2f; \
                                    } ").arg(preBtn->width()/2).arg(MuSmartScaleUI(7)));
    playBtn->setStyleSheet(QString(" QPushButton { \
                                        background-color: #e83c3c; \
                                        border: none; \
                                        border-radius: %1px; \
                                        padding: %2px;\
                                        image: url(:/images/playBtn48_White.png);\
                                    }                         \
                                    QPushButton:hover { \
                                        background-color: #c62f2f; \
                                    } \
                                    QPushButton:checked { \
                                        image: url(:/images/pauseBtn48_White.png);\
                                    }").arg(playBtn->width()/2).arg(MuSmartScaleUI(6)));

    nextBtn->setStyleSheet(QString(" QPushButton { \
                                        background-color: #e83c3c; \
                                        border: none; \
                                        border-radius: %1px; \
                                        padding: %2px;\
                                        image: url(:/images/nextSongBtn48_White.png);\
                                    }                         \
                                    QPushButton:hover { \
                                        background-color: #c62f2f; \
                                    } ").arg(nextBtn->width()/2).arg(MuSmartScaleUI(7)));
    }

MuUtils::MuMenuIconProxyStyle::MuMenuIconProxyStyle(QStyle *style)
    : QProxyStyle(style)
{

}

MuUtils::MuMenuIconProxyStyle::MuMenuIconProxyStyle(const QString &key)
     : QProxyStyle(key)
{

}

int MuUtils::MuMenuIconProxyStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch ( metric ) {
     case QStyle::PM_SmallIconSize:
       return MuStyleHelper::rightButtonMenuIconSize(); // here u want pixmaps size i assume
     default:
       return QProxyStyle::pixelMetric( metric, option, widget ); // return default values for the rest
    }
}

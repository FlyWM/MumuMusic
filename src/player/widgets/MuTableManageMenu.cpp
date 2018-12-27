/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QMenu>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <qdrawutil.h>
#include <QPainter>
#include <QApplication>
#include <QWidgetAction>
#include <QLabel>
#include "MuTableManageMenu.h"
#include "MuStyleHelper.h"

QQueue <MuTableRightButtonMenu *> MuTableRightButtonMenu::m_instances;
MuTableRightButtonMenu::MuTableRightButtonMenu(TableType table, int tableRowIndex, QWidget *parent)
    : MuShadowWindow<QWidget>(false, 10, parent)
    , m_tableType(table)
    , m_tableRowIndex(tableRowIndex)
{
    m_instances.push_back(this);
    deleteLastOne();
    qApp->installEventFilter(this);
    setWindowFlags((Qt::Dialog | this->windowFlags()));
    titleBar()->hide();
    setTitleBarHeight(0);
    createMainWidget();
    setFixedWidth(MuUtils::MuStyleHelper::rightButtonMenuWidth());
    setClientWidget(m_pMenu);
    setObjectName("MuTableRightButtonMenu");
    adjustSize();
}

bool MuTableRightButtonMenu::eventFilter(QObject *watched, QEvent *event)
{
    // when clicking other areas, hide the menu dialog
    if (event->type() == QEvent::MouseButtonPress &&
            watched->objectName() != m_pMenu->objectName() &&
            watched->objectName() != this->objectName() &&
            watched->objectName() != (this->objectName() + "Window")) {
        deleteThisOne();
    }

    return QObject::eventFilter(watched, event);
}

void MuTableRightButtonMenu::onActionTriggered(QAction *action)
{
    if (action == m_pDeleteFromListAc) {

    }
}

void MuTableRightButtonMenu::createMainWidget()
{
    m_pMenu = new QMenu(this);
    m_pMenu->setStyle(new MuUtils::MuMenuIconProxyStyle());
    m_pMenu->setObjectName("tableMenu");
    m_pMenu->setContentsMargins(5, 5, 5, 5);
    m_pMenu->setMinimumWidth(MuUtils::MuStyleHelper::rightButtonMenuWidth() - 20);
    m_pViewCommentsAc = new QAction(QIcon(QStringLiteral(":/images/viewComments32_515151.png")), tr("View All Comments(1234)"));
    m_pPlayAc = new QAction(QIcon(QStringLiteral(":/images/menuPlay32_515151.png")), tr("Play"));
    m_pNextSongAc = new QAction(QIcon(QStringLiteral(":/images/menuPlayNext32_515151.png")), tr("Play Next"));
    m_pAddToPlaylistAc = new QAction(QIcon(QStringLiteral(":/images/menuAddToList32_515151.png")), tr("Add To Playlist"));
    m_pShareAc = new QAction(QIcon(QStringLiteral(":/images/menuShare32_515151.png")), tr("Share"));
    m_pCopyLkAdAc = new QAction(QIcon(QStringLiteral(":/images/menuCopyLink32_515151.png")), tr("Copy Link Address"));
    m_pUpToMyCloudAc = new QAction(QIcon(QStringLiteral(":/images/menuUpload32_515151.png")), tr("Upload To My Cloud"));
    m_pOpenFolderAc = new QAction(QIcon(QStringLiteral(":/images/menuOpenFolder32_515151.png")), tr("Open Folder"));
    m_pDeleteFromListAc = new QAction(QIcon(QStringLiteral(":/images/menuDelete32_515151.png")), tr("Delete From List"));
    m_pDeleteFromDiskAc = new QAction(tr("Delete From Disk"));

    switch (m_tableType) {
    case LocalTable:
        m_pMenu->addAction(m_pViewCommentsAc);
        m_pMenu->addAction(m_pPlayAc);
        m_pMenu->addAction(m_pNextSongAc);
        m_pMenu->addSeparator();
        m_pMenu->addAction(m_pAddToPlaylistAc);
        m_pMenu->addAction(m_pShareAc);
        m_pMenu->addAction(m_pCopyLkAdAc);
        m_pMenu->addAction(m_pUpToMyCloudAc);
        m_pMenu->addAction(m_pOpenFolderAc);
        m_pMenu->addSeparator();
        m_pMenu->addAction(m_pDeleteFromListAc);
        m_pMenu->addAction(m_pDeleteFromDiskAc);
        break;
    }

    connect(m_pMenu, &QMenu::triggered, this, &MuTableRightButtonMenu::onActionTriggered);
}

void MuTableRightButtonMenu::deleteLastOne()
{
    if (m_instances.size() > 1) {
        m_instances.head()->hide();
        auto menu = m_instances.head();
        m_instances.pop_front();
        menu->deleteLater();
    }
}

void MuTableRightButtonMenu::deleteThisOne()
{
    if (m_instances.size() > 0) {
        m_instances.head()->hide();
        auto menu = m_instances.head();
        m_instances.pop_front();
        menu->deleteLater();
    }
}


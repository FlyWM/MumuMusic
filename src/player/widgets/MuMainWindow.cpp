#include <QLayout>
#include <QMoveEvent>
#include <QScrollArea>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QScreen>
#include <QApplication>
#include <QScrollBar>
#include <QLabel>
#include <QDebug>
#include "MumainWindow.h"
#include "MuMusicMangeWidget.h"
#include "MuCentralWidget.h"
#include "MuPlayStatusBar.h"
#include "MuShadowWidget.h"
#include "MuPopupWidgetButton.h"
#include "MuPlayStatusBarUI.h"
#include "MuPlayListMainWidgetUI.h"
#include "MuLocalMusicWidgetUI.h"
#include "MuStyleHelper.h"
#include "MuScrollArea.h"

QPoint MuMainWindow::m_pos;
#ifdef Q_OS_LINUX
    MuCustomWindow *MuMainWindow::m_instance;
#elif defined Q_OS_WIN32
    MuWinAeroShadowWindow *MuMainWindow::m_instance;
#endif

MuMainWindow::MuMainWindow(QWidget *parent)
#ifdef Q_OS_LINUX
    : MuCustomWindow(parent)
#elif defined Q_OS_WIN32
    : MuWinAeroShadowWindow(parent)
#endif
{
    m_instance = this;
    setWindowTitle(QStringLiteral("Mumu Music"));
    setObjectName(QStringLiteral("MainWidget"));
    setWindowIcon(QIcon(":/images/logo.png"));
    titleBar()->setObjectName("titleBar");
    titleBar()->iconLabel()->setFixedSize(MuUtils::MuStyleHelper::titleBarIconSize());
    titleBar()->minimizeButton()->setFixedSize(MuUtils::MuStyleHelper::titleBarButtonSize());
    titleBar()->maximizeButton()->setFixedSize(MuUtils::MuStyleHelper::titleBarButtonSize());
    titleBar()->closeButton()->setFixedSize(MuUtils::MuStyleHelper::titleBarButtonSize());

    QSize windowSize = MuUtils::MuStyleHelper::mainWindowSize();
    int titleSize = MuUtils::MuStyleHelper::titileHeight();
    setMinimumSize(windowSize);
    setTitleBarHeight(titleSize);
    initMainWindow();

    QList<QScreen *> screens = QApplication::screens();
    if (screens.size() > 0) {
        QScreen *pScreen = screens[0];
        connect(pScreen, &QScreen::logicalDotsPerInchChanged, this, &MuMainWindow::onLogicalDotsPerInchChanged);
    }
}

void MuMainWindow::initPos()
{
    m_pos = this->mapToGlobal(QPoint(0, 0));
}

QPoint MuMainWindow::getMainWidgetPos()
{
    return m_instance->pos();
}

QSize MuMainWindow::getMainWidgetSize()
{
    return m_instance->size();
}

void MuMainWindow::moveEvent(QMoveEvent *e)
{
    m_pos = e->pos();
}

void MuMainWindow::onLogicalDotsPerInchChanged(qreal dpi)
{
    Q_UNUSED(dpi)

    double curRate = MuUtils::MuStyleHelper::rate();
    MuUtils::MuStyleHelper::scaleChildren(*this);
    MuUtils::MuStyleHelper::setPreRate(curRate);
}

void MuMainWindow::initMainWindow()
{
    QWidget *pCentralWidget = new QWidget(this);
    pCentralWidget->setObjectName(QStringLiteral("mainCentralWidget"));

    // 左侧工具栏
    MuMusicMangeWidget *pMangeWidget = new MuMusicMangeWidget(pCentralWidget);

    // 中心显示区域
    QStackedWidget *pMainStackedWidget = new QStackedWidget(pCentralWidget);
    pMainStackedWidget->setObjectName(QStringLiteral("mainStackedWidget"));
    MuScrollArea *pLocalMusicSA = new MuScrollArea(pMainStackedWidget);
    pLocalMusicSA->setObjectName(QStringLiteral("nativeMusicScrollArea"));
    pLocalMusicSA->setWidgetResizable(true);
    pLocalMusicSA->setScrollEnabled(false);
    pLocalMusicSA->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    MuLocalMusicWidget *pLocalMusicWidget = new MuLocalMusicWidget(pMainStackedWidget);
    pLocalMusicSA->setWidget(pLocalMusicWidget);
    pLocalMusicWidget->setScrollArea(pLocalMusicSA);
    pMainStackedWidget->addWidget(pLocalMusicSA);

    MuScrollArea *playlistSA = new MuScrollArea(pMainStackedWidget);
    playlistSA->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    playlistSA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playlistSA->setScrollEnabled(true);
    playlistSA->setWidgetResizable(true);
    MuPlaylistMainWidgetUI *playlist = new MuPlaylistMainWidgetUI;
    playlistSA->setWidget(playlist);

    pMainStackedWidget->addWidget(new QWidget);
    pMainStackedWidget->addWidget(new QWidget);
    pMainStackedWidget->addWidget(playlistSA);

    connect(pMangeWidget, &MuMusicMangeWidget::ListItemPressed, pMainStackedWidget, &QStackedWidget::setCurrentIndex);
    connect(pLocalMusicWidget, &MuLocalMusicWidget::EnableScrollAreaBar, [pLocalMusicSA, pLocalMusicWidget](bool enabled, bool aboutToShowBar) {
        pLocalMusicSA->setScrollEnabled(enabled);
        if (enabled) {
            // 当设置该策略之后，滚动条并不会马上出现
            pLocalMusicSA->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        } else {
            pLocalMusicSA->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
        pLocalMusicWidget->adjustRightMargin(aboutToShowBar);
    });

    // 播放控制栏
    MuPlayStatusBarUI *pPlayStatusBar = new MuPlayStatusBarUI(pCentralWidget);
    pPlayStatusBar->setObjectName(QStringLiteral("playStatusBar"));
    pPlayStatusBar->setFixedHeight(MuUtils::MuStyleHelper::playStatusBarHeight());
    pMangeWidget->setFixedWidth(MuUtils::MuStyleHelper::mangeWidgetWidth());

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->addWidget(pMangeWidget);
    pLayout->addWidget(pMainStackedWidget);
    pLayout->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *pMainLayout = new QVBoxLayout(pCentralWidget);
    pMainLayout->addLayout(pLayout);
    pMainLayout->addWidget(pPlayStatusBar);
    pMainLayout->setContentsMargins(0, 0, 0, 0);
    pMainLayout->setSpacing(0);
    setClientWidget(pCentralWidget);
}

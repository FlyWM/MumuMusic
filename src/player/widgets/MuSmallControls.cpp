/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QLayout>
#include <QPushButton>
#include <QAction>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QMoveEvent>
#include <QProgressBar>
#include <QDebug>
#include "musmallcontrols.h"
#include "MuStyleHelper.h"

MuPlayAddButton::MuPlayAddButton(QWidget *parent)
    : QWidget(parent)
    , m_playButton(new QPushButton(this))
    , m_addToPlayListButton(new QPushButton(this))
{
    m_playButton->setObjectName(QStringLiteral("playAllButton"));
    m_addToPlayListButton->setObjectName(QStringLiteral("addAllToListButton"));
    m_playButton->setFixedSize(MuUtils::MuStyleHelper::MuSmartScaleUI(90), MuUtils::MuStyleHelper::MuSmartScaleUI(25));
    m_addToPlayListButton->setFixedSize(MuUtils::MuStyleHelper::MuSmartScaleUI(30), MuUtils::MuStyleHelper::MuSmartScaleUI(25));
    m_playButton->setText(tr("Play All"));
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_playButton);
    pLayout->addWidget(m_addToPlayListButton);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(0);
}

MuSearchBox::MuSearchBox(QWidget *parent) :
    QLineEdit(parent)
{
    this->setObjectName(QStringLiteral("searchBoxLE"));
//    this->setFixedSize(MuUtils::MuStyleHelper::searchaBoxSize());
    QAction *pAc = new QAction(this);
    pAc = this->addAction(QIcon(QStringLiteral(":/images/searchAction32_LightGray.png")),
                               QLineEdit::TrailingPosition);
    connect(pAc, &QAction::triggered, [=]() {
        if (this->text().isEmpty())
            return;
        else {
            this->clear();
            pAc->setIcon(QIcon(QStringLiteral(":/images/searchAction32_LightGray.png")));
        }
    });

    connect(this, &QLineEdit::textChanged, [=](const QString text) {
        if (text.isEmpty()) {
            pAc->setIcon(QIcon(QStringLiteral(":/images/searchAction32_LightGray.png")));
        } else {
            pAc->setIcon(QIcon(QStringLiteral(":/images/closeBtn32_Gray.png")));
        }
    });
}

MuRollingTipWidget::MuRollingTipWidget(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet(QStringLiteral("background-color: red"));
    initUpdateWidget();
    initFinishedWidget();
    initMatchWdiget();
}

void MuRollingTipWidget::startUpdating()
{
    int posx = this->mapToGlobal(QPoint(0, 0)).x();
    int posy = this->mapToGlobal(QPoint(0, 0)).y();
    posx += (this->width() - m_pUpdatingWidget->width()) / 2;
    m_pUpdatingWidget->move(posx, posy + this->height() - m_pUpdatingWidget->height()/2);
    m_pUpdatingWidget->show();
    m_pUpTimer->start(5);
}

void MuRollingTipWidget::stopUpdate()
{
    m_pUpTimer->stop();
    m_pUpdatingWidget->hide();
}

void MuRollingTipWidget::showFinished()
{
    int posx = this->mapToGlobal(QPoint(0, 0)).x();
    int posy = this->mapToGlobal(QPoint(0, 0)).y();
    posx += (this->width() - m_pFinishedWidget->width()) / 2;
    m_pFinishedWidget->move(posx, posy + this->height() - m_pFinishedWidget->height()/2);
    m_pFinishedWidget->show();
    m_pFdTimer->start(5);
    QTimer *pTimer = new QTimer;
    connect(pTimer, &QTimer::timeout, [=] (){
        m_pFdTimer->stop();
        m_pFinishedWidget->hide();
        pTimer->stop();
    });
    pTimer->start(5000);
}

void MuRollingTipWidget::startMatching()
{
    int posx = this->mapToGlobal(QPoint(0, 0)).x();
    int posy = this->mapToGlobal(QPoint(0, 0)).y();
    posx += (this->width() - m_pMatchWidget->width()) / 2;
    m_pMatchWidget->move(posx, posy + this->height() - m_pMatchWidget->height()/2);
    m_pMatchWidget->show();
    m_pMTimer->start(5);
}

void MuRollingTipWidget::stopMatching()
{
    m_pMatchWidget->hide();
}

void MuRollingTipWidget::onTimeOut(QTimer *timer, QWidget *widget)
{
    if (timer == nullptr || widget == nullptr)
        return;

    int parentBottomY = this->mapToGlobal(QPoint(0, height())).y();
    int posx = this->mapToGlobal(QPoint(0, 0)).x();
    int posy = parentBottomY - widget->height();
    posx += (this->width() - widget->width()) / 2;
    int py = widget->y();
    // do not stop the timer
    if (py <= posy) {
        py = posy;
    }

    if ((py >= (parentBottomY - widget->height()*4/5))
            && (py <= (parentBottomY))) {
        py -= 1;
    }

    else if ((py < (parentBottomY - widget->height()*4/5))
             && (py >= (parentBottomY - widget->height()))) {
        timer->start(20);
        py -= 1;
    }
    else if (py > (parentBottomY + widget->height()/2)) {
        py = parentBottomY - widget->height()/2;
    }

    widget->move(posx, py);
}

void MuRollingTipWidget::initUpdateWidget()
{
    m_pUpTimer = new QTimer(this);
    m_pUpdatingWidget = new QWidget(this);
    m_pUpdatingWidget->setWindowFlags((Qt::Dialog | Qt::FramelessWindowHint));
    m_pUpdatingWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pUpdatingWidget->hide();
//    m_pUpdatingWidget->setFixedHeight(40);

    m_pUdIconLabel = new QLabel(this);
    m_pUdTipLabel = new QLabel(this); // 105,105,105
    QMovie *pUdGif = new QMovie(this);
    pUdGif->setFileName(QStringLiteral(":/gif/updating.gif"));
    m_pUdIconLabel->setMovie(pUdGif);
    m_pUdTipLabel->setText(tr("Updating the native music list..."));
    m_pUdTipLabel->setStyleSheet(QStringLiteral("color: #696969;"));
    pUdGif->start();
    QHBoxLayout *pUdLayout = new QHBoxLayout(m_pUpdatingWidget);
    pUdLayout->addWidget(m_pUdIconLabel, 0, Qt::AlignBottom);
    pUdLayout->addWidget(m_pUdTipLabel, 0, Qt::AlignBottom);
    pUdLayout->setContentsMargins(0, 0, 0, 0);

    connect(m_pUpTimer, &QTimer::timeout, [=]() {
        onTimeOut(m_pUpTimer, m_pUpdatingWidget);
    });
}

void MuRollingTipWidget::initFinishedWidget()
{
    m_pFinishedWidget = new QWidget(this);
    m_pFinishedWidget->setWindowFlags((Qt::Dialog | Qt::FramelessWindowHint));
    m_pFinishedWidget->setAttribute(Qt::WA_TranslucentBackground);
//    m_pFinishedWidget->setFixedHeight(40);

    m_pFdTimer = new QTimer(this);
    m_pFdIconLabel = new QLabel(this);
    m_pFdTipLabel = new QLabel(this);
    m_pFdIconLabel->setFixedSize(20, 20);
    m_pFdIconLabel->setStyleSheet(QStringLiteral("image: url(:/images/checked16_c62f2f.png); padding-top: 6px;"));
    m_pFdTipLabel->setText(tr("Update finished"));
    m_pFdTipLabel->setStyleSheet(QStringLiteral("color: #696969;"));
    QHBoxLayout *pLayout = new QHBoxLayout(m_pFinishedWidget);
    pLayout->addWidget(m_pFdIconLabel, 0, Qt::AlignBottom);
    pLayout->addWidget(m_pFdTipLabel, 0, Qt::AlignBottom);
    pLayout->setContentsMargins(0, 0, 0, 0);
    m_pFinishedWidget->hide();

    connect(m_pFdTimer, &QTimer::timeout, [=]() {
        onTimeOut(m_pFdTimer, m_pFinishedWidget);
    });
}

void MuRollingTipWidget::initMatchWdiget()
{
    m_pMTimer = new QTimer(this);
    m_pMatchWidget = new QWidget(this);
    m_pMatchWidget->setWindowFlags((Qt::Dialog | Qt::FramelessWindowHint));
    m_pMatchWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pMatchWidget->hide();
//    m_pMatchWidget->setFixedHeight(40);
    QHBoxLayout *pUdLayout = new QHBoxLayout(m_pMatchWidget);
    m_pMIconLabel = new QLabel(this);
    m_pMTipLabel = new QLabel(this);
    QMovie *pUdGif = new QMovie(this);
    pUdGif->setFileName(QStringLiteral(":/gif/updating.gif"));
    m_pMIconLabel->setMovie(pUdGif);
    m_pMTipLabel->setText(tr("Matching..."));
    m_pMTipLabel->setStyleSheet(QStringLiteral("color: #696969;"));
    pUdGif->start();
    m_pMProgress = new QLabel("0/0", this);
    m_pMProgBar = new QProgressBar(this);
    m_pMProgBar->setObjectName(QStringLiteral("matchNtvMusicProgressBar"));
    m_pMProgBar->setFixedHeight(7);
    pUdLayout->addWidget(m_pMIconLabel, 0, Qt::AlignBottom);
    pUdLayout->addWidget(m_pMTipLabel, 0, Qt::AlignBottom);
    pUdLayout->addWidget(m_pMProgress, 0, Qt::AlignBottom);
    pUdLayout->addWidget(m_pMProgBar, 0, Qt::AlignVCenter);
    pUdLayout->setContentsMargins(0, 0, 0, 0);

    connect(m_pMTimer, &QTimer::timeout, [=]() {
        onTimeOut(m_pMTimer, m_pMatchWidget);
    });
}


/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QApplication>
#include <QDebug>
#include "mutoolbox.h"
#include "mulistwidgetitem.h"
#include "mucreateplaylistdlgui.h"
#include "mupopupwidgetbutton.h"
#include "mushadowwidget.h"
#include "MuStyleHelper.h"

MuEventFilter::MuEventFilter(QObject *parent)
    : QObject(parent)
{

}

bool MuEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::HoverEnter) {
        emit mouseEnter();
        return true;
    } else if (event->type() == QEvent::HoverLeave) {
        emit mouseLeave();
        return true;
    }
    return QObject::eventFilter(watched, event);
}

MuListItemWidget::MuListItemWidget(const QString icon1, const QString icon2,
                                   const QString itemName, QWidget *parent)
    : QWidget(parent),
      m_bSelected(false)
{
    setFixedSize(MuUtils::MuStyleHelper::mangeListItemSize());
    setObjectName(QStringLiteral("listItemWidget"));
    m_pIconLabel = new QLabel(this);
    m_pNameLabel = new QLabel(this);
    m_pPlayStatusLabel = new QLabel(this);
    m_pPlayStatusLabel->setFixedSize(18, 18);
    m_pIconLabel->setFixedSize(MuUtils::MuStyleHelper::mangeListItemIconSize());
    m_pIconLabel->setScaledContents(true);
    m_pIconLabel->setPixmap(QPixmap(icon1));
    m_pNameLabel->setText(itemName);
    m_pNameLabel->setObjectName(QStringLiteral("toolboxNameLabel"));
    m_pPlayStatusLabel->setFixedSize(25, 25);

    QHBoxLayout *pItemLayout = new QHBoxLayout(this);
    pItemLayout->addSpacing(20);
    pItemLayout->addWidget(m_pIconLabel);
    pItemLayout->addWidget(m_pNameLabel);
    pItemLayout->addStretch();
    pItemLayout->addWidget(m_pPlayStatusLabel);
    pItemLayout->setContentsMargins(0, 0, 0, 0);
    pItemLayout->setSpacing(10);

    connect(this, &MuListItemWidget::mouseEnter, [=]() {
        m_pIconLabel->setPixmap(QPixmap(icon2));
        if (m_bSelected) {
            m_pNameLabel->setStyleSheet(QStringLiteral("color: black; background-color: #e6e7ea;"));
        } else {
            m_pNameLabel->setStyleSheet(QStringLiteral("color: black; background-color: #f5f5f7;"));
        }
    });
    connect(this, &MuListItemWidget::mouseLeave, [=]() {
        m_pIconLabel->setPixmap(QPixmap(icon1));
        m_pNameLabel->setStyleSheet(QStringLiteral("color: #696969; background-color: #f5f5f7;"));
    });
}

void MuListItemWidget::setSelected(bool selected)
{
    if (selected) {
        m_bSelected = true;
        emit mouseEnter();
    } else {
        m_bSelected = false;
        emit mouseLeave();
    }
}

void MuListItemWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    emit mouseEnter();
}

void MuListItemWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    if (!m_bSelected)
        emit mouseLeave();
}

void MuListItemWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}

MuOpenPlayListWidget::MuOpenPlayListWidget(const QString title, bool canCreatePlayList, QWidget *parent)
    : QWidget(parent),
      m_pCreatePlayListBtn(nullptr)
{
    MuEventFilter *pEnterEventFilter = new MuEventFilter(this);
    m_pTitleBtn = new QPushButton(title, this);
    m_pTitleBtn->installEventFilter(pEnterEventFilter);

    m_pOpenListsBtn = new QPushButton(this);
    m_pTitleBtn->setObjectName(QStringLiteral("playListTitleButton"));
    m_pOpenListsBtn->setObjectName(QStringLiteral("openListButton"));
    m_pOpenListsBtn->setFixedSize(MuUtils::MuStyleHelper::mangeListItemOpenListBtnSize());
    m_pOpenListsBtn->setProperty("mouseEnterPro", false);
    m_pOpenListsBtn->setStyle(QApplication::style());
    m_pOpenListsBtn->setCheckable(true);
    m_pOpenListsBtn->setChecked(true);
    connect(pEnterEventFilter, &MuEventFilter::mouseEnter, [=]() {
        m_pOpenListsBtn->setProperty("mouseEnterPro", true);
        m_pOpenListsBtn->setStyle(QApplication::style());
    });
    connect(pEnterEventFilter, &MuEventFilter::mouseLeave, [=]() {
        m_pOpenListsBtn->setProperty("mouseEnterPro", false);
        m_pOpenListsBtn->setStyle(QApplication::style());
    });
    connect(m_pTitleBtn, &QPushButton::clicked, [=]() {
        m_pOpenListsBtn->setChecked(!m_pOpenListsBtn->isChecked());
    });

    if (canCreatePlayList) {
        MuCreatePlaylistDlgUI *pDlg = new MuCreatePlaylistDlgUI(this);
        m_pCreatePlayListBtn = new MuPopupWidgetButton(PWB::Horizontal, this);
        m_pCreatePlayListBtn->button()->setFixedSize(MuUtils::MuStyleHelper::mangeListItemCreateBtnSize());
        m_pCreatePlayListBtn->button()->setObjectName(QStringLiteral("createPlayListButton"));
        m_pCreatePlayListBtn->setMainWidget(pDlg);
        connect(pDlg, &MuCreatePlaylistDlgUI::HideWidget, m_pCreatePlayListBtn, &MuPopupWidgetButton::hideWidget);
    }
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->addWidget(m_pTitleBtn, 1);
    pMainLayout->addWidget(m_pCreatePlayListBtn);
    pMainLayout->addWidget(m_pOpenListsBtn);
    pMainLayout->setSpacing(2);
    pMainLayout->setContentsMargins(10, 0, 10, 0); //,,25

    connect(m_pOpenListsBtn, &QPushButton::toggled, [=](bool checked) {
        if (checked) {
            emit showList();
        } else {
            emit hideList();
        }
    });
}


QHash<QListWidgetItem *, MuListItemWidget *> MuToolBox:: m_pListWidgets;
QList<QListWidgetItem *> MuToolBox::m_pListItems;
MuToolBox::MuToolBox(const QString boxTitle, bool isPlayList, QWidget *parent)
    : QWidget(parent),
      m_shrinkable(false),
      m_pMainLayout(new QVBoxLayout(this)),
      m_pListWidget(new QListWidget(this)),
      m_pTitleWidget(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pListWidget->setObjectName(QStringLiteral("musicMangeListWidget"));
    m_pListWidget->setMouseTracking(true);
    m_pListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if (!isPlayList) {
        QLabel *pBoxTitleLabel = new QLabel(boxTitle, this);
        pBoxTitleLabel->setMargin(10);
        pBoxTitleLabel->setObjectName(QStringLiteral("boxTitleLabel"));
        m_pTitleWidget = pBoxTitleLabel;

    } else {
        m_pTitleWidget = new MuOpenPlayListWidget(boxTitle, true, this);
        connect((MuOpenPlayListWidget *)m_pTitleWidget, &MuOpenPlayListWidget::showList, m_pListWidget, &QListWidget::show);
        connect((MuOpenPlayListWidget *)m_pTitleWidget, &MuOpenPlayListWidget::hideList, m_pListWidget, &QListWidget::hide);
    }

    m_pMainLayout->addWidget(m_pTitleWidget);
    m_pMainLayout->addWidget(m_pListWidget);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(0);

    connect(m_pListWidget, &QListWidget::itemPressed, [=](QListWidgetItem *item) {
        if (m_pListWidgets.contains(item)) {
            if (m_pListItems.contains(item))
                emit ItemPressed(m_pListItems.indexOf(item));
            m_pListWidgets.value(item)->setSelected(true);
            foreach (auto key, m_pListWidgets.keys()) {
                if (key != item) {
                    m_pListWidgets.value(key)->setSelected(false);
                    key->setSelected(false);
                }
            }
        }
    });
    setFixedWidth(MuUtils::MuStyleHelper::mangeWidgetWidth());
}

void MuToolBox::setShrinkable(bool shrinkable)
{
    m_shrinkable = shrinkable;
}

void MuToolBox::addItem(const QString itemName, const QString itemIcon1, const QString itemIcon2)
{
    QListWidgetItem *pItem = new QListWidgetItem(m_pListWidget);

    MuListItemWidget *pItemWidget = new MuListItemWidget(itemIcon1, itemIcon2, itemName);
    QSize itemSizeHint = MuUtils::MuStyleHelper::mangeListItemSize();

    pItem->setSizeHint(itemSizeHint);
    m_pListWidget->addItem(pItem);
    m_pListWidget->setItemWidget(pItem, pItemWidget);
    m_pListWidget->setMouseTracking(true);
    m_pListWidget->setFixedHeight(itemSizeHint.height() * m_pListWidget->count() + 5);
    m_pListWidgets.insert(pItem, pItemWidget);
    m_pListItems.append(pItem);
}

int MuToolBox::titleWidgetWidth() const
{
    return m_pTitleWidget->width();
}

int MuToolBox::listWidgetWidth() const
{
    return m_pListWidget->width();
}








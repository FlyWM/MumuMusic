#include <QLayout>
#include <QStyleOption>
#include <QPainter>
#include <QScrollArea>
#include <QDebug>
#include "mumusicmangewidget.h"
#include "mutoolbox.h"
#include "mubasewidget.h"


MuMusicMangeWidget::MuMusicMangeWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("mangeWidget"));
    QVBoxLayout *pMainLayout = new QVBoxLayout(this);
    pMainLayout->addWidget(createMangeScrollArea());
    pMainLayout->setContentsMargins(0, 0, 0, 0);
}

void MuMusicMangeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QWidget *MuMusicMangeWidget::createMangeScrollArea()
{
    QScrollArea *pScrollArea = new QScrollArea(this);
    pScrollArea->setObjectName(QStringLiteral("musicMangeScrollArea"));
    pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QWidget *pWidget = new QWidget(this);
    pWidget->setObjectName(QStringLiteral("musicMangeScrollAreaWidget"));

    MuToolBox *pMyMusicBox = new MuToolBox(tr("My Music"), false, this);
    pMyMusicBox->addItem(tr("Local Music"), QStringLiteral(":/images/nativeMusic32_LightGray.png"), QStringLiteral(":/images/nativeMusic32_Black.png"));
    pMyMusicBox->addItem(tr("Download manager"), QStringLiteral(":/images/download32_Gray.png"), QStringLiteral(":/images/download32_Black.png"));
    pMyMusicBox->addItem(tr("My Collection"), QStringLiteral(":/images/myCollect32_Gray.png"), QStringLiteral(":/images/myCollect32_Black.png"));
    MuToolBox *pPlayListBox = new MuToolBox(tr("Playlist"), true, this);
    pPlayListBox->addItem(tr("My Favorite"), QStringLiteral(":/images/favoriteSongsList32_Gray.png"), QStringLiteral(":/images/favoriteSongsList32_Black.png"));

    connect(pMyMusicBox, &MuToolBox::ItemPressed, this, &MuMusicMangeWidget::ListItemPressed);
    connect(pPlayListBox, &MuToolBox::ItemPressed, this, &MuMusicMangeWidget::ListItemPressed);

    QVBoxLayout *pMainLayout = new QVBoxLayout(pWidget);
    pMainLayout->addWidget(pMyMusicBox);
    pMainLayout->addWidget(pPlayListBox);

    pMainLayout->setContentsMargins(0, 10, 15, 0);
    pMainLayout->setSpacing(0);
    pMainLayout->addStretch();

    pScrollArea->setWidget(pWidget);

    return pScrollArea;
}

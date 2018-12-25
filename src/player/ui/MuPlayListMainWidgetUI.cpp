/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QButtonGroup>
#include <QAction>
#include <QStandardItemModel>
#include <QPainter>
#include <QScrollBar>
#include <QResizeEvent>
#include <QDebug>
#include "muglobal.h"
#include "mutableviewhelper.h"
#include "muplaylistmainwidgetui.h"
#include "ui_muplaylistmainwidgetui.h"
#include "utils/muimagehandler.h"

MuPlaylistMainWidgetUI::MuPlaylistMainWidgetUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuPlaylistMainWidgetUI),
    m_pAc(nullptr)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QButtonGroup *pBtnGroup = new QButtonGroup(this);
    pBtnGroup->addButton(ui->songsListBtn);
    pBtnGroup->addButton(ui->criticismBtn);
    pBtnGroup->addButton(ui->collectorsBtn);
    pBtnGroup->setExclusive(true);

    QPixmap userIcon = MuImageHandler::PixmapToRound(QPixmap(":/images/logo.jpg"), ui->userIconLb->width()/2);
    ui->userIconLb->setPixmap(userIcon);
    ui->stackedWidget->setCurrentIndex(0);
    initTableWidget();

    m_pAc = ui->searchBoxLE->addAction(QIcon(":/images/searchAction32_LightGray.png"),
                               QLineEdit::TrailingPosition);
    connect(m_pAc, &QAction::triggered, [=]() {
        if (ui->searchBoxLE->text().isEmpty())
            return;
        else {
            ui->searchBoxLE->clear();
            m_pAc->setIcon(QIcon(":/images/searchAction32_LightGray.png"));
        }
    });

    connect(ui->searchBoxLE, &QLineEdit::textChanged, [=](const QString text) {
        if (text.isEmpty()) {
            m_pAc->setIcon(QIcon(":/images/searchAction32_LightGray.png"));
        } else {
            m_pAc->setIcon(QIcon(":/images/closeBtn32_Gray.png"));
        }
    });
}

MuPlaylistMainWidgetUI::~MuPlaylistMainWidgetUI()
{
    delete ui;
}

void MuPlaylistMainWidgetUI::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    ui->songsListTableView->headerView()->setHeaderWidth(ui->stackedWidget->widget(0)->width());
}

void MuPlaylistMainWidgetUI::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
    ui->songsListTableView->headerView()->setHeaderWidth(ui->stackedWidget->widget(0)->width());
}

void MuPlaylistMainWidgetUI::initTableWidget()
{
//    const QStringList headers = { " ", tr("Operation"), tr("MusicTitle"), tr("Artist"), tr("Album"), tr("Duration"), };
//    ui->songsListTableView->setHorizontalHeaderLabels(headers);
//    ui->songsListTableView->headerView()->resizeSection(0, 65);
//    ui->songsListTableView->headerView()->setSectionResizeMode(0, QHeaderView::Fixed);
//    ui->songsListTableView->headerView()->resizeSection(1, 65);
//    ui->songsListTableView->headerView()->setSectionResizeMode(1, QHeaderView::Fixed);
//    ui->songsListTableView->headerView()->setMinimumSectionSize(100);
//    ui->songsListTableView->headerView()->setHeaderWidth(this->width());
//    ui->songsListTableView->headerView()->setSectionScale("0, 0, 3, 1, 1, 1");
//    ui->songsListTableView->headerView()->setSectionMinSize(0, 65);
//    ui->songsListTableView->headerView()->setSectionMinSize(1, 65);
//    ui->songsListTableView->headerView()->setSectionMinSize(2, 250);
//    ui->songsListTableView->headerView()->setSectionMinSize(3, 100);
//    ui->songsListTableView->headerView()->setSectionMinSize(4, 100);
//    ui->songsListTableView->headerView()->setSectionMinSize(5, 100);
//    ui->songsListTableView->setColumnWidth(3, 250);
}

void MuPlaylistMainWidgetUI::on_songsListBtn_clicked()
{

}

/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMovie>
#include <QDebug>
#include <QDir>
#include <QtConcurrent>
#include <QThread>
#include <QTime>
#include <QLineEdit>
#include <QScrollBar>
#include <QResizeEvent>
#include <QTableView>
#include "MuLocalMusicWidgetUI.h"
#include "ui_MuLocalMusicWidgetUI.h"
#include "MuDialogUI.h"
#include "MuSelectLocalMusicWidgetUI.h"
#include "MuStyleHelper.h"
#include "MuGlobal.h"
#include "MuMedia.h"
#include "MuConversionTool.h"
#include "MuTableView.h"
#include "MuDBManager.h"
#include "MuLocalMusicManager.h"

MuLocalMusicWidget::MuLocalMusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuLocalMusicWidget),
    m_pScrollArea(nullptr),
    m_nLocalSongsNb(0)
{
    qRegisterMetaType<QList<QStringList>>("QList<QStringList>");
    ui->setupUi(this);
    ui->localUpdatingWidget->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
    m_pBtnGroup = new QButtonGroup(this);
    m_pBtnGroup->addButton(ui->localListBtn, 0);
    m_pBtnGroup->addButton(ui->localArtistBtn, 1);
    m_pBtnGroup->addButton(ui->localAlbumBtn, 2);
    m_pBtnGroup->addButton(ui->localFolderBtn, 3);
    QSize buttonSize = MuUtils::MuStyleHelper::localTabButtonSize();
    ui->localListBtn->setFixedSize(buttonSize);
    ui->localArtistBtn->setFixedSize(buttonSize);
    ui->localAlbumBtn->setFixedSize(buttonSize);
    ui->localFolderBtn->setFixedSize(buttonSize);

    ui->vSpaceWidget->setFixedHeight(MuUtils::MuStyleHelper::MuSmartScaleUI(100));
    ui->localTitleBarWidget->setFixedHeight(MuUtils::MuStyleHelper::localTitleBarHeight());
    ui->localTitleLayout->setContentsMargins(MuUtils::MuStyleHelper::localTitleLayoutMargins());
    ui->localSelectMusicFolderBtn->setFixedSize(MuUtils::MuStyleHelper::localSelectNativeFolderButtonSize());

    int rightLeftMargin = MuUtils::MuStyleHelper::localRightMargin();
    ui->localTitleLayout->setContentsMargins(rightLeftMargin, 0, rightLeftMargin, 5);



    m_pDlg = new MuDialogUI(this);
    m_pDlg->setCenralWidgetFixedSize(MuUtils::MuStyleHelper::localAddMusicDialogSize());
    m_pDlg->setWindowTitle(tr("Select local music folder"));
    m_pDlg->setButtonsText(tr("Ok"), tr("Add Folder"));
    m_pSelectMainWidget = new MuSelectLocalMusicWidgetUI(this);
    m_pDlg->setMainWidget(m_pSelectMainWidget);

    ui->localMusicDetailWidget->setObjectName("localMusicTableAreaWidget");

    connect(m_pDlg, &MuDialogUI::Button2Clicked, this, &MuLocalMusicWidget::onAddFolderBtnClicked);
    connect(m_pDlg, &MuDialogUI::Button1Clicked, this, &MuLocalMusicWidget::onOkBtnClicked);
    connect(ui->localSelectFolderBtn, &QPushButton::clicked, m_pDlg, &MuDialogUI::show);
    connect(ui->localSelectMusicFolderBtn, &QPushButton::clicked, m_pDlg, &MuDialogUI::show);
    connect(ui->localMusicDetailWidget, &MuLocalMusicDetailUI::EnableScrollAreaBar, this, &MuLocalMusicWidget::EnableScrollAreaBar);
    connect(m_pBtnGroup, SIGNAL(buttonToggled(int, bool)), SLOT(onGroupButtonToggled(int, bool)));
    connect(ui->localMusicDetailWidget, &MuLocalMusicDetailUI::TableRowCount, [=](int rowCnt) {
        ui->localSongsNbLb->setText(QString::number(rowCnt) + tr("songs,"));
        if (rowCnt > 0) {
            m_nLocalSongsNb = rowCnt;
            m_pBtnGroup->button(0)->setChecked(true);
        }
    });

    connect(&m_lmm, &MuLocalMusicManager::UpdateDone, this, &MuLocalMusicWidget::onUpdateDone);

    initTableView();
}

MuLocalMusicWidget::~MuLocalMusicWidget()
{
    delete ui;
}

void MuLocalMusicWidget::setScrollArea(QScrollArea *scrollArea)
{
    m_pScrollArea = scrollArea;
    if (scrollArea != nullptr)
        ui->localMusicDetailWidget->setScrollViewPortHeight(scrollArea->maximumViewportSize().height());
}

void MuLocalMusicWidget::adjustRightMargin(bool aboutToShowBar)
{
    if (m_pScrollArea != nullptr) {
        int scrollBarWidth = m_pScrollArea->verticalScrollBar()->width();
        int rightMargin = MuUtils::MuStyleHelper::localRightMargin();
        QMargins margins = ui->localTitleLayout->contentsMargins();
        if (m_curButton == Mu::ListButton) {
            // 当设置setVerticalScrollBarPolicy之后，isVisible可能不会马上改变
            if (aboutToShowBar || m_pScrollArea->verticalScrollBar()->isVisible())
                margins.setRight(rightMargin - scrollBarWidth);
            else
                margins.setRight(rightMargin);
        } else {
            margins.setRight(rightMargin);
        }
        ui->localTitleLayout->setContentsMargins(margins);
    }
}

void MuLocalMusicWidget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
}

void MuLocalMusicWidget::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
}

void MuLocalMusicWidget::onAddFolderBtnClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                tr("Select Folder"),
                                QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation));
    if (dir.isEmpty())
        return;

    if (dir.size() == 3 && dir.indexOf(":/") == 1) {
        dir.remove(dir.size() - 1, 1);
    }

    m_pSelectMainWidget->addItem(dir);
}

void MuLocalMusicWidget::onOkBtnClicked()
{
    QStringList paths = m_pSelectMainWidget->getItemsContent();
    // show updating gif
    ui->localUpdatingWidget->setVisible(true);
    ui->localUpdatingWidget->startUpdating();
    m_pDlg->close();

    m_lmm.updateLocalMusic(paths);
}

void MuLocalMusicWidget::onGroupButtonToggled(int index, bool checked)
{
    if (m_nLocalSongsNb == 0)
        return;

    if (checked) {
        ui->stackedWidget->setCurrentIndex(1);
        m_curButton = static_cast<Mu::LocalMusicButton>(index);
        ui->localMusicDetailWidget->setCurLocalButton(m_curButton);

        if (m_curButton == Mu::ListButton) {
            ui->localMusicDetailWidget->matchButton()->show();
            ui->localMusicDetailWidget->thumbWidget()->hide();
            ui->localMusicDetailWidget->searchLocalMusicBox()->show();
            ui->localMusicDetailWidget->tableView()->setTableType(MuTableView::LocalList);
        } else if (m_curButton == Mu::ArtistButton) {
            ui->localMusicDetailWidget->thumbWidget()->show();
            ui->localMusicDetailWidget->matchButton()->hide();
            ui->localMusicDetailWidget->searchLocalMusicBox()->hide();
            ui->localMusicDetailWidget->tableView()->setTableType(MuTableView::LocalArtist);
        } else {
            ui->localMusicDetailWidget->thumbWidget()->show();
            ui->localMusicDetailWidget->matchButton()->hide();
            ui->localMusicDetailWidget->searchLocalMusicBox()->hide();
        }
    }
}

void MuLocalMusicWidget::onUpdateDone()
{
    MuTableView *pTable = ui->localMusicDetailWidget->tableView();

    // update table data from the database
    pTable->updateData();

    // show the finished gif
    ui->localUpdatingWidget->stopUpdate();
    ui->localUpdatingWidget->showFinished();

    // set the value of song number label
    m_nLocalSongsNb = pTable->talbeRowCount();
    ui->localSongsNbLb->setText(QString::number(m_nLocalSongsNb) + tr("Songs,"));

    m_pBtnGroup->button(0)->setChecked(true);
}

void MuLocalMusicWidget::initTableView()
{
    const QStringList headers = { " ",  tr("MusicTitle"), tr("Artist"), tr("Album"), tr("Duration"), tr("Size") };
    MuTableView *pTable = ui->localMusicDetailWidget->tableView();
//    pTable->setModelTable(MuTableView::LocalMusicTable);
    pTable->setTableType(MuTableView::LocalList);
    pTable->setHorizontalHeaderLabels(headers);
    pTable->headerView()->resizeSection(0, 65);

    // before call this function, the table must not be empty
    // otherwise, error: "ASSERT: 'visual != -1'"
    pTable->headerView()->setSectionResizeMode(0, QHeaderView::Fixed);
    pTable->headerView()->setMinimumSectionSize(100);
    pTable->headerView()->setHeaderWidth(this->width());
    pTable->headerView()->setSectionScale("0, 3, 1, 1, 1, 1");
    pTable->headerView()->setSectionMinSize(0, 65);
    pTable->headerView()->setSectionMinSize(1, 250);
    pTable->headerView()->setSectionMinSize(2, 100);
    pTable->headerView()->setSectionMinSize(3, 100);
    pTable->headerView()->setSectionMinSize(4, 100);
    pTable->headerView()->setSectionMinSize(5, 100);
    pTable->setColumnWidth(3, 250);
    pTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

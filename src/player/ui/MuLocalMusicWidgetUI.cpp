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

#if 0
QStringList MuFindNativeMusciFile::m_filters;
QStringList MuFindNativeMusciFile::m_musciFiles;
QStringList MuFindNativeMusciFile::m_paths;
#endif

MuFindNativeMusciFile::MuFindNativeMusciFile(QObject *parent) :
    QObject(parent)
{
}

void MuFindNativeMusciFile::setFilePathsAndFilters(const QStringList paths, const QStringList filters)
{
    m_paths = paths;
    m_filters = filters;
}

void MuFindNativeMusciFile::startFind()
{
    if (m_paths.isEmpty()) {
        emit Finished();
        return;
    }

    QStringList musicFiles;
    for (auto &file : m_paths) {
        musicFiles.append(findFiles(file, m_filters));
    }
    QList<QStringList> data;
    for (auto &file : musicFiles) {
        MuMedia m(MuConversionTool::qstring2stdString(file));
		
        if (m.isValid()) {
            QStringList str;
            str << file << QString::fromStdString(m.audioDir())
                << QString::fromStdString(m.audioTitle()) << QString::fromStdString(m.audioAlbum())
                << QString::fromStdString(m.audioArtist()) << MuConversionTool::mcsToStrFormatTime(m.duration())
                << "" << QString::number(m.bitRate())
                << MuConversionTool::bytesToGBMBKB(m.fileSize()) << QString("0");
            data.append(str);
            MuDBManager::getInstance().insertData(MuDBManager::LocalMusicTrack, str);
        }
    }

    emit FoundFiles(data);
    emit Finished();

    //    QStringList names = QtConcurrent::mappedReduced(m_paths, findMusicFiles, reduce);
}

QStringList MuFindNativeMusciFile::findFiles(const QString &startDir, QStringList filters)
{
//    qDebug() << startDir;
    QStringList names;
    QDir dir(startDir);

    foreach (QString file, dir.entryList(filters, QDir::Files))
        names += startDir + '/' + file;

    foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        names += findFiles(startDir + '/' + subdir, filters);

    return names;
}

#if 0
QStringList MuFindNativeMusciFile::findMusicFiles(const QString &path)
{
    qDebug() << QThread::currentThreadId();
    QStringList names;
    QDir dir(path);
    foreach (QString file, dir.entryList(m_filters, QDir::Files))
        names += path + '/' + file;

    foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        names += findMusicFiles(path + '/' + subdir);

    return names;
}

void MuFindNativeMusciFile::reduce(QStringList &musicFiles, const QStringList &res)
{
    musicFiles.append(res);
}
#endif


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
    QButtonGroup *pBtnGroup = new QButtonGroup(this);
    pBtnGroup->addButton(ui->localListBtn, 0);
    pBtnGroup->addButton(ui->localArtistBtn, 1);
    pBtnGroup->addButton(ui->localAlbumBtn, 2);
    pBtnGroup->addButton(ui->localFolderBtn, 3);
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
    connect(pBtnGroup, SIGNAL(buttonClicked(int)), SLOT(onGroupButtonClicked(int)));
    connect(ui->localMusicDetailWidget, &MuLocalMusicDetailUI::TableRowCount, [=](int rowCnt) {
        ui->localSongsNbLb->setText(QString::number(rowCnt) + tr("songs,"));
        if (rowCnt > 0) {
            m_nLocalSongsNb = rowCnt;
            pBtnGroup->button(0)->setChecked(true);
            emit pBtnGroup->buttonClicked(0);
        }
    });

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
//    qDebug() << "e->size: " << e->size();
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
    ui->localUpdatingWidget->setVisible(true);
    ui->localUpdatingWidget->startUpdating();

    m_pDlg->close();

    MuFindNativeMusciFile *pFindFile = new MuFindNativeMusciFile();
    QThread *pThread = new QThread();
    pFindFile->moveToThread(pThread);
    pFindFile->setFilePathsAndFilters(paths, QStringList() << "*.mp3" << "*.wma" << "*.aac");

    connect(pThread, &QThread::started, pFindFile, &MuFindNativeMusciFile::startFind);
    connect(pFindFile, &MuFindNativeMusciFile::Finished, pFindFile, &MuFindNativeMusciFile::deleteLater);
    connect(pFindFile, &MuFindNativeMusciFile::Finished, pThread, &QThread::quit);
    connect(pThread, &QThread::finished, pThread, &QThread::deleteLater);
    connect(pFindFile, &MuFindNativeMusciFile::FoundFiles, this, &MuLocalMusicWidget::onFoundFiles);

    pThread->start();
}

void MuLocalMusicWidget::onFoundFiles(const QList<QStringList> &data)
{
//    ui->localMusicDetailWidget->updateTable(data);
    ui->localMusicDetailWidget->tableView()->updateData();
    ui->localUpdatingWidget->stopUpdate();
    ui->localUpdatingWidget->showFinished();
    m_nLocalSongsNb += data.size();
    ui->localSongsNbLb->setText(QString::number(m_nLocalSongsNb) + tr("Songs,"));
}

void MuLocalMusicWidget::onGroupButtonClicked(int index)
{
    if (m_nLocalSongsNb == 0)
        return;

    ui->stackedWidget->setCurrentIndex(1);
    m_curButton = static_cast<Mu::LocalMusicButton>(index);
    ui->localMusicDetailWidget->setCurLocalButton(m_curButton);

    if (m_curButton == Mu::ListButton) {
        ui->localMusicDetailWidget->matchButton()->show();
        ui->localMusicDetailWidget->thumbWidget()->hide();
        ui->localMusicDetailWidget->searchLocalMusicBox()->show();
    } else {
        ui->localMusicDetailWidget->thumbWidget()->show();
        ui->localMusicDetailWidget->matchButton()->hide();
        ui->localMusicDetailWidget->searchLocalMusicBox()->hide();
    }
}

void MuLocalMusicWidget::initTableView()
{
    const QStringList headers = { " ",  tr("MusicTitle"), tr("Artist"), tr("Album"), tr("Duration"), tr("Size") };
    MuTableView *pTable = ui->localMusicDetailWidget->tableView();
    pTable->setModelTable(MuTableView::LocalMusicTable);
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

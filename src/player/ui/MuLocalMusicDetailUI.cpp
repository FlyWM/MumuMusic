/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QDebug>
#include <QScrollBar>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "MuLocalMusicDetailUI.h"
#include "ui_MuLocalMusicDetailUI.h"
#include "MuStyleHelper.h"
#include "MuGlobal.h"
#include "MuTableView.h"
#include "MuMainWindow.h"

MuLocalTableViewWidget::MuLocalTableViewWidget(QWidget *parent) :
    QWidget(parent)
{

}

MuLocalTableViewWidget::~MuLocalTableViewWidget()
{

}

void MuLocalTableViewWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    emit WidthChanged(this->width());
}


MuLocalMusicDetailUI::MuLocalMusicDetailUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuLocalMusicDetailUI),
    m_curButton(Mu::NullButton)
{
    ui->setupUi(this);
    ui->localThumbWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->localThumbWidget->setMinimumWidth(MuUtils::MuStyleHelper::localThumbWidgetWidth());
    ui->localThumbSearchBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->localThumbSearchBox->setFixedHeight(MuUtils::MuStyleHelper::localSearchNtvMusicBoxSize().height());
    ui->localThumbSearchBox->setPlaceholderText(tr("Search For Artist"));
    ui->localTableScrollArea->setWidgetResizable(true);

    m_pTable = ui->localScrollAreaWidgetContents->tableView();

    connect(ui->localMusicTableViewArea, &MuLocalTableViewWidget::WidthChanged, [=](const int width) {
        m_pTable->headerView()->setHeaderWidth(width);
        adjustHeight();
    });
    connect(m_pTable, &MuTableView::TableDataChanged, this, &MuLocalMusicDetailUI::adjustHeight);
    connect(ui->localScrollAreaWidgetContents, &MuLocalMusicTableAreaUI::TableRowCount, this, &MuLocalMusicDetailUI::TableRowCount);
}

MuLocalMusicDetailUI::~MuLocalMusicDetailUI()
{
    delete ui;
}

void MuLocalMusicDetailUI::setCurLocalButton(Mu::LocalMusicButton button)
{
    m_curButton = button;
    adjustHeight();
}

void MuLocalMusicDetailUI::setScrollViewPortHeight(int height)
{
    m_scrollViePortHeight = height;
}

QWidget *MuLocalMusicDetailUI::thumbWidget()
{
    return ui->localThumbWidget;
}

QPushButton *MuLocalMusicDetailUI::matchButton()
{
    return ui->localScrollAreaWidgetContents->matchButton();
}

QLineEdit *MuLocalMusicDetailUI::searchLocalMusicBox()
{
    return ui->localScrollAreaWidgetContents->searchLocalMusicBox();
}

MuTableView *MuLocalMusicDetailUI::tableView() const
{
    return ui->localScrollAreaWidgetContents->tableView();
}

void MuLocalMusicDetailUI::updateTable(const QList<QStringList> &data)
{
    m_pTable->updateData(data);
}

void MuLocalMusicDetailUI::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
//    qDebug() << "resizeEvent: " << ui->ntvMusicTalbeViewArea->width();
//    ui->ntvMusicTableView->headerView()->setHeaderWidth(ui->ntvMusicTalbeViewArea->width());
}

void MuLocalMusicDetailUI::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)
//    qDebug() << "showEvent: " << ui->ntvMusicTalbeViewArea->width();
//    ui->ntvMusicTableView->headerView()->setHeaderWidth(ui->ntvMusicTalbeViewArea->width());
}

void MuLocalMusicDetailUI::on_localMatchBtn_toggled(bool checked)
{
    if (checked)
        ui->localScrollAreaWidgetContents->matchButton()->setText(tr("Stop Matching"));
    else
        ui->localScrollAreaWidgetContents->matchButton()->setText(tr("Match Music"));
}

/**
 * @brief MuLocalMusicDetailUI::adjustHeight
 *  \note QScrollArea的高度一直在变化，所以无法作为标准，采用可视范围的高度作为标准
 */
void MuLocalMusicDetailUI::adjustHeight()
{
    // 30: topMarin + bottomMarin
    int tableAndButtonHeight = m_pTable->rowHeight(0) * m_pTable->model()->rowCount() \
                      + m_pTable->headerView()->height() + 30 + MuUtils::MuStyleHelper::localMatchButtonSize().height();
    int tableHeight = m_pTable->rowHeight(0) * m_pTable->model()->rowCount() \
            + m_pTable->headerView()->height();

    //  --------------------------------
    //  |     |playall     ↑           |
    //  |     |------------↑-----------
    //  |list |            ↑           |
    //  |     |            ↑           |
    //  |     | tableAreaViewPortHeight|
    //  |     |            ↓           |
    //  |     |            ↓           |
    //  --------------------------------
    // 5: layout spacing
    // 不把包括localTitileBar
    int tableAreaViewPortHeight = MuMainWindow::getMainWidgetSize().height() - MuUtils::MuStyleHelper::titileHeight() - \
            MuUtils::MuStyleHelper::localTitleBarHeight() - MuUtils::MuStyleHelper::playStatusBarHeight() - 5;

    if (m_curButton == Mu::ListButton) {
        // listButton页面中的滚动条；
        // \warning! 与其它界面的滚动条不是同一个
        bool aboutToShowBar = false;
        if (tableAndButtonHeight > tableAreaViewPortHeight)
            aboutToShowBar = true;

        if (aboutToShowBar) {
            ui->localTableScrollArea->setFixedHeight(tableAndButtonHeight);
            m_pTable->setFixedHeight(tableHeight);
        } else {
            m_pTable->setFixedHeight(tableAreaViewPortHeight);
            ui->localTableScrollArea->setFixedHeight(tableAreaViewPortHeight);
        }
        ui->localTableScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->localTableScrollArea->setScrollEnabled(false);
        emit EnableScrollAreaBar(true, aboutToShowBar);
    } else if (m_curButton == Mu::ArtistButton
               || m_curButton == Mu::AlbumButton
               || m_curButton == Mu::FolderButton) {
        int temp = tableAreaViewPortHeight - 30 - MuUtils::MuStyleHelper::localMatchButtonSize().height();
        tableHeight = tableHeight > temp ? tableHeight : temp;
        if (tableHeight > temp) {
            ui->localTableScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->localTableScrollArea->setScrollEnabled(true);
        } else {
            tableHeight = temp;
            ui->localTableScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->localTableScrollArea->setScrollEnabled(false);
        }
        m_pTable->setFixedHeight(tableHeight);
        ui->localTableScrollArea->setFixedHeight(tableAreaViewPortHeight);

        emit EnableScrollAreaBar(false);
    }
}



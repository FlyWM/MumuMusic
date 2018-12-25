#include "MuStyleHelper.h"
#include "MuLocalMusicTableAreaUI.h"
#include "ui_MuLocalMusicTableAreaUI.h"

MuLocalMusicTableAreaUI::MuLocalMusicTableAreaUI(QWidget *parent) :
    MuBaseWidget(parent),
    ui(new Ui::MuLocalMusicTableAreaUI)
{
    ui->setupUi(this);
    ui->localMatchBtn->setFixedSize(MuUtils::MuStyleHelper::localMatchButtonSize());
    ui->localSearchLocalMusicBox->setFixedSize(MuUtils::MuStyleHelper::localSearchNtvMusicBoxSize());
    ui->localSearchLocalMusicBox->setPlaceholderText(tr("Search For Local Music"));
    ui->localMusicTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->localMusicTableView, &MuTableView::TableRowCount, this, &MuLocalMusicTableAreaUI::TableRowCount);
}

MuLocalMusicTableAreaUI::~MuLocalMusicTableAreaUI()
{
    delete ui;
}

MuTableView *MuLocalMusicTableAreaUI::tableView() const
{
    return ui->localMusicTableView;
}

QPushButton *MuLocalMusicTableAreaUI::matchButton() const
{
    return ui->localMatchBtn;
}

QLineEdit *MuLocalMusicTableAreaUI::searchLocalMusicBox() const
{
    return ui->localSearchLocalMusicBox;
}

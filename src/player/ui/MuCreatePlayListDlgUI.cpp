#include "mucreateplaylistdlgui.h"
#include "ui_mucreateplaylistdlgui.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#ifdef Q_CC_MSVC
#pragma comment(lib, "user32.lib")
#endif

MuCreatePlaylistDlgUI::MuCreatePlaylistDlgUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuCreatePlaylistDlgUI)
{
    ui->setupUi(this);
    connect(ui->titleLE, &QLineEdit::textChanged, [=](const QString text) {
        if (text.isEmpty()) {
            ui->createBtn->setChecked(false);
        } else {
            ui->createBtn->setChecked(true);
        }
        qDebug() << ui->createBtn->isChecked();
    });
    connect(ui->cancelBtn, &QPushButton::clicked, this, &MuCreatePlaylistDlgUI::HideWidget);
}

MuCreatePlaylistDlgUI::~MuCreatePlaylistDlgUI()
{
    delete ui;
}

void MuCreatePlaylistDlgUI::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

#include <QGraphicsDropShadowEffect>
#include <QLayout>
#include <QMouseEvent>
#include <QDebug>
#include "MuDialogUI.h"
#include "ui_MuDialogUI.h"
#include "mumainwindow.h"
#include "MuStyleHelper.h"

MuDialogCloseButton::MuDialogCloseButton(QWidget *parent) :
    QPushButton(parent)
{

}

void MuDialogCloseButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    setCursor(Qt::PointingHandCursor);
}

void MuDialogCloseButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    setCursor(Qt::SizeAllCursor);
}

MuDialogTitleWidget::MuDialogTitleWidget(QWidget *parent) :
    MuBaseWidget(parent)
{
    installEventFilter(this);
}

bool MuDialogTitleWidget::eventFilter(QObject *watched, QEvent *event)
{
    QWidget *parent = qobject_cast<QWidget *>(this->topLevelWidget());
    if (parent == nullptr)
        return QWidget::eventFilter(watched, event);

    QPoint mapPoint = this->mapTo(parent, QPoint(0, 0));

    switch (event->type()) {
    case QEvent::Enter: {
        setCursor(Qt::SizeAllCursor);
        break;
    }
    case QEvent::Leave: {
        setCursor(Qt::ArrowCursor);
        break;
    }
    case QEvent::MouseButtonPress: {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        m_startPoint = e->pos() + mapPoint;
        break;
    }
    case QEvent::MouseMove: {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if (e == nullptr)
            return false;

        QPoint dstPoint = e->globalPos() - m_startPoint;
        // MuDialog's margin is 10
        QPoint mainWindowPos = MuMainWindow::getMainWidgetPos() - QPoint(10, 10);
        QSize mainWindowSize = MuMainWindow::getMainWidgetSize() + QSize(10, 10);
        if (dstPoint.x() < mainWindowPos.x())
            dstPoint.setX(mainWindowPos.x());
        if (dstPoint.y() < mainWindowPos.y())
            dstPoint.setY(mainWindowPos.y());
        if ((dstPoint.x()+parent->width()) > (mainWindowPos.x()+mainWindowSize.width()))
            dstPoint.setX(mainWindowPos.x()+mainWindowSize.width()-parent->width()+10);
        if ((dstPoint.y()+parent->height()) > (mainWindowPos.y()+mainWindowSize.height()))
            dstPoint.setY(mainWindowPos.y()+mainWindowSize.height()-parent->height()+10);

        parent->move(dstPoint);
        break;
    }
    }
    return QWidget::eventFilter(watched, event);
}

MuDialogUI::MuDialogUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuDialogUI),
    m_bMousePressed(false)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal, true);
    setWindowFlags((Qt::Dialog | Qt::FramelessWindowHint | this->windowFlags()));
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *pShadow = new QGraphicsDropShadowEffect(this);
    pShadow->setOffset(0, 0);
    pShadow->setColor(QColor("#cccccc"));
    pShadow->setBlurRadius(10);
    ui->dlgCentralWidget->setGraphicsEffect(pShadow);

    m_pMainWidget = new QWidget(this);

    m_pMainWidgetLayout = new QVBoxLayout(ui->dlgMainWidget);
    m_pMainWidgetLayout->addWidget(m_pMainWidget);
    m_pMainWidgetLayout->setContentsMargins(0, 0, 0, 0);

    ui->dlgTitleWidget->setFixedHeight(MuUtils::MuStyleHelper::dialogTitleHeight());
    ui->dlgBottomWidget->setFixedHeight(MuUtils::MuStyleHelper::dialogBottomHeight());

    connect(ui->dlgButton1, &QPushButton::clicked, this, &MuDialogUI::Button1Clicked);
    connect(ui->dlgButton2, &QPushButton::clicked, this, &MuDialogUI::Button2Clicked);
}

MuDialogUI::~MuDialogUI()
{
    delete ui;
}

void MuDialogUI::setModal(bool modal)
{
    setAttribute(Qt::WA_ShowModal, modal);
}

void MuDialogUI::setCenralWidgetFixedSize(const QSize size)
{
    QSize frameSize;
    frameSize.setWidth(size.width()+20);
    frameSize.setHeight(size.height()+20);
    this->setFixedSize(frameSize);
}

void MuDialogUI::setBottomVisible(bool visible)
{
    if (visible)
        ui->dlgBottomWidget->show();
    else
        ui->dlgBottomWidget->hide();
}

void MuDialogUI::setButtonsText(const QString &text1, const QString &text2)
{
    ui->dlgButton1->setText(text1);
    ui->dlgButton2->setText(text2);
}

void MuDialogUI::setMainWidget(QWidget *widget)
{
    if (widget == nullptr)
        return;

    m_pMainWidgetLayout->removeWidget(m_pMainWidget);
    m_pMainWidget->deleteLater();
    m_pMainWidget = widget;
    m_pMainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (ui->dlgBottomWidget->isHidden())
        resize(10*2+widget->width(), ui->dlgTitleWidget->height()+widget->height());
    else
        resize(10*2+widget->width(), ui->dlgTitleWidget->height()+widget->height()+ui->dlgBottomWidget->height());
    m_pMainWidgetLayout->addWidget(m_pMainWidget);
}

void MuDialogUI::hideTitle()
{
    ui->dlgTitleWidget->hide();
}

void MuDialogUI::hideBottom()
{
    ui->dlgBottomWidget->hide();
}

bool MuDialogUI::event(QEvent *event)
{
    if (event->type() == QEvent::WindowTitleChange) {
        ui->dlgTitleLb->setText(this->windowTitle());
    }
    return QWidget::event(event);
}

void MuDialogUI::on_dlgCloseBtn_clicked()
{
    this->close();
}





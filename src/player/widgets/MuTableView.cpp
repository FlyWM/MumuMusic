/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QtMath>
#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QLayout>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "MuGlobal.h"
#include "MuTableView.h"
#include "MuStyleHelper.h"
#include "MuDialogUI.h"
#include "MuTableManageMenu.h"

MuHeaderViewEventFilter::MuHeaderViewEventFilter(QObject *parent) :
    QObject(parent)
{

}

bool MuHeaderViewEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    QWidget *pWidget = qobject_cast<QWidget *>(watched);
    if (pWidget->cursor().shape() == Qt::SplitHCursor) {
        if (event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove) {
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}

MuHeaderView::MuHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent),
    m_nHeaderWidth(0),
    m_nPressedX(0),
    m_bPressed(false),
    m_bReachedMaxWidth(false),
    m_nCurPessedSectionIndex(-1)
{
    setFixedHeight(MuUtils::MuStyleHelper::tableViewHeaderHeight());
    setSectionsClickable(true);
    setStretchLastSection(false);
    setSortIndicatorShown(false);
    // 自定义属性，只有当Hover = true时，才会触发qss的hover
    setProperty("HoverAndSort", QStringLiteral("true, 0"));

    connect(this, &MuHeaderView::sectionClicked, this, &MuHeaderView::onSectionClicked);
}

void MuHeaderView::setHeaderWidth(const int width)
{
    m_nHeaderWidth = width;
    setSectionScale(m_strScale);
}

void MuHeaderView::setSectionMinSize(int logicalIndex, int size)
{
    m_sectionMinSize[logicalIndex] = size;
}

void MuHeaderView::setSectionScale(QString scale)
{
    QStringList strlScale = scale.split(",");
    if (strlScale.isEmpty() || strlScale.size() != count())
        return;

    m_strScale = scale;

    int resizableWidth = m_nHeaderWidth;
    for (int i=0; i<count(); ++i) {
        if (sectionResizeMode(i) == QHeaderView::Fixed ||
                sectionResizeMode(i) == QHeaderView::Custom) {
            resizableWidth -= sectionSize(i);
        }
    }

    if (resizableWidth < 0) {
        return;
    }

    QList<int> nLScale, nLSize;
    int sum = 0, sectionSum = 0;
    foreach (QString str, strlScale) {
        nLScale.append(str.toInt());
        sum += str.toInt();
    }
    foreach (int scale, nLScale) {
        if (scale == 0)
            nLSize.append(0);
        else
            nLSize.append(((double)scale / sum) * resizableWidth);
        sectionSum += nLSize.last();
    }
    int dif = resizableWidth - sectionSum;
    if (dif > 0) {
        int j = 0;
        int len = nLSize.size();
        for (int i=1; i<dif+1; ++i) {
            while (nLSize.at(j%len) == 0)
                ++ j;
            ++ nLSize[j];
            ++ j;
            -- dif;
        }
    }
    for (int i=0; i<count(); ++i) {
        if (nLSize.at(i) != 0)
            resizeSection(i, nLSize.at(i));
    }
}


void MuHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    return QHeaderView::paintSection(painter, rect, logicalIndex);
}

void MuHeaderView::mouseMoveEvent(QMouseEvent *e)
{
    emit MouseEnter();
    // 鼠标在拖动section时，没有背景色
    if (this->cursor().shape() == Qt::SplitHCursor) {
        setProperty("HoverAndSort", QString("false,%1").arg(property("HoverAndSort").toString().split(",").last()));
        setStyle(QApplication::style());
    } else {
        setProperty("HoverAndSort", QString("true,%1").arg(property("HoverAndSort").toString().split(",").last()));
        setStyle(QApplication::style());
    }
    // 如果鼠标悬停到不可操作的section时设置CanHover=false;
    // 悬停在不同的section可能会显示不同的图标，因为sortOder可能会不同
    int curLen = 0;
    for (int i=0; i<count(); ++i) {
        if (e->pos().x() > curLen && e->pos().x() < (curLen+sectionSize(i))) {
            if (sectionResizeMode(i) == QHeaderView::Fixed || sectionResizeMode(i) == QHeaderView::Custom) {
                setProperty("HoverAndSort", QString("false,%1").arg(property("HoverAndSort").toString().split(",").last()));
                setStyle(QApplication::style());
                break;
            } else {
                setProperty("HoverAndSort", QString("true,%1").arg(QString::number(m_sectioinSortOrder.value(i))));
                setStyle(QApplication::style());
            }
        }
        curLen += sectionSize(i);
    }

    if (m_bPressed) {
        bool allReachedMin = false;

        if (m_nCurPessedSectionIndex == count()-1)
            return;

        // 向左拖动
        if (e->pos().x() - m_nPressedX < 0) {
            for (int i=0; i<m_nCurPessedSectionIndex+1; ++i) {
                qDebug() << sectionSize(i) << m_sectionMinSize[i] << i << m_sectionMinSize << m_nCurPessedSectionIndex;
                if (sectionSize(i) <= m_sectionMinSize[i]) {
                    allReachedMin = true;
                } else {
                    allReachedMin = false;
                    break;
                }
            }

            // \note
            // 正在拖动的section之前的所有section都达到了最小值,section大小不再变化，
            // 此时更新m_nPressedX的值，以便继续反方向拖动时能够正常变化大小
            if (allReachedMin) {
                m_nPressedX = 0;
                for (int i=0; i<m_nCurPessedSectionIndex+1; ++i) {
                    m_nPressedX += sectionSize(i);
                }
                return;
            }
        }

        // 向右拖动
        if (e->pos().x() - m_nPressedX > 0) {
            for (int i=m_nCurPessedSectionIndex+1; i<count(); ++i) {
                if (sectionSize(i) <= m_sectionMinSize[i]) {
                    allReachedMin = true;
                } else {
                    allReachedMin = false;
                    break;
                }
            }
            if (allReachedMin) {
                m_nPressedX = 0;
                for (int i=m_nCurPessedSectionIndex+1; i<count(); ++i) {
                    m_nPressedX += sectionSize(i);
                }
                return;
            }
        }
    }

    return QHeaderView::mouseMoveEvent(e);
}

void MuHeaderView::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_nPressedX = e->pos().x();
    bool findIndex = false;
    int tempLen = 0;
    // 找到拖动的是第几个section
    for (int i=0; i<count(); ++i) {
        tempLen += sectionSize(i);
        if (qAbs(tempLen-m_nPressedX) < 5) {
            m_nCurPessedSectionIndex = i;
            findIndex = true;
            break;
        }
    }
    if (!findIndex)
        m_nCurPessedSectionIndex = -1;

    return QHeaderView::mousePressEvent(e);
}

void MuHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    return QHeaderView::mouseReleaseEvent(e);
}

void MuHeaderView::onSectionClicked(const int logicalIndex)
{
    if (sectionResizeMode(logicalIndex) == QHeaderView::Fixed ||
            sectionResizeMode(logicalIndex) == QHeaderView::Custom)
        return;

    emit EnableSort(true);

    if (m_sectioinSortOrder.isEmpty()) {
        for (int i=0; i<count(); ++i) {
            m_sectioinSortOrder.insert(i, 0);
        }
    }

    m_sectioinSortOrder[logicalIndex] = (m_sectioinSortOrder.value(logicalIndex)+1) % 3;
    QString proStr = property("HoverAndSort").toString();
    proStr.replace(proStr.length()-1, 1, QString::number(m_sectioinSortOrder.value(logicalIndex)));
    setProperty("HoverAndSort", proStr);
    setStyle(QApplication::style());

    if (m_sectioinSortOrder.value(logicalIndex) == 1) {
        setSortIndicator(logicalIndex, Qt::DescendingOrder);
    } else if (m_sectioinSortOrder.value(logicalIndex) == 2) {
        setSortIndicator(logicalIndex, Qt::AscendingOrder);
    }

    emit EnableSort(false);
}

bool MuTableViewItemModel::m_empty = false;
MuTableViewItemModel::MuTableViewItemModel(QObject *parent)
    : QSqlTableModel(parent)
    , m_nHoverRow(0)
    , m_bHover(false)
    , m_columnCount(0)
{

}

//int MuTableViewItemModel::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return m_data.count();
//}

//int MuTableViewItemModel::columnCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return m_columnCount;
//}

QVariant MuTableViewItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    switch (role)
    {
    case Qt::BackgroundColorRole: {
        if (row == m_nHoverRow)
            return QColor(QStringLiteral("#ebeced"));

        if ((row+1) % 2 == 0)
            return QColor(QStringLiteral("#f5f5f7"));

        break;
    }
    case Qt::TextColorRole: {
        return QColor(QStringLiteral("#3b3b3b"));
    }
    case Qt::TextAlignmentRole: {
        if (col == 0)
            return QVariant(Qt::AlignRight | Qt::AlignVCenter);
        else
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    case Qt::DisplayRole:
    {
        // 重新排序之后行号不会改变
        if (col == 0) {
            if (row >=0 && row <9)
                return "0" + QString::number(row + 1);
            else
                return QString::number(row+1);
        }
        if (m_empty)
            return QVariant();

        return QSqlTableModel::data(index, Qt::DisplayRole);
    }
    default:
        return QVariant();
    }

    return QVariant();
}

QVariant MuTableViewItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0 || m_headerLabels.isEmpty())
            return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        if (orientation == Qt::Horizontal && section<m_headerLabels.size())
            return m_headerLabels.at(section);
        else return QVariant();

    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
    return QVariant();
}

bool MuTableViewItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count);
    endInsertRows();
    return true;
}

bool MuTableViewItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);
    endRemoveRows();
    return true;
}

void MuTableViewItemModel::updateData(QList<QStringList> data)
{
    m_data = data;
    beginResetModel();
    endResetModel();
}

void MuTableViewItemModel::setHoverRow(const int row)
{
    m_nHoverRow = row;
    m_bHover = true;
}

void MuTableViewItemModel::setColumnCount(const int count)
{
    m_columnCount = count;
}

void MuTableViewItemModel::setHeaderLables(const QStringList headerLabels)
{
    m_headerLabels = headerLabels;
    for (int i=0; i<m_headerLabels.size(); ++i) {
        setHeaderData(i+1, Qt::Horizontal, m_headerLabels.at(i));
    }
}

void MuTableViewItemModel::setDisplayData(const QModelIndex &index, QVariant var)
{
    if (!index.isValid())
        return;

//    m_data[index.row()][index.column()-1] = var.toString();
    setData(index, var, Qt::DisplayRole);
    qDebug() << "item data: " << this->itemData(index).value(Qt::DisplayRole);
}


MuStyleItemDelegate::MuStyleItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void MuStyleItemDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);

    // 去掉选中时的虚线
    if (viewOption.state & QStyle::State_HasFocus) {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    // 设置右边距
    if (index.column() == 0) {
        viewOption.rect.setTopRight(QPoint(viewOption.rect.x() + 50, viewOption.rect.y()));
        QStyleOptionViewItem  rightPaddingViewOption(option);
        rightPaddingViewOption.rect.setX(viewOption.rect.x() + 50);
        rightPaddingViewOption.rect.setY(viewOption.rect.y());
        rightPaddingViewOption.rect.setWidth(15);
        rightPaddingViewOption.rect.setHeight(viewOption.rect.height());
        if (rightPaddingViewOption.state & QStyle::State_HasFocus) {
            rightPaddingViewOption.state = rightPaddingViewOption.state ^ QStyle::State_HasFocus;
        }

        QStyledItemDelegate::paint(painter, rightPaddingViewOption, index);
    }
    // 设置左边距
    else if (index.column() >= 1) {
        viewOption.rect.setTopLeft(QPoint(viewOption.rect.x() + 12, viewOption.rect.y()));
        QStyleOptionViewItem leftPaddingViewOption(option);
        leftPaddingViewOption.rect.setX(viewOption.rect.x() - 12);
        leftPaddingViewOption.rect.setY(viewOption.rect.y());
        leftPaddingViewOption.rect.setWidth(15);
        leftPaddingViewOption.rect.setHeight(viewOption.rect.height());
        if (leftPaddingViewOption.state & QStyle::State_HasFocus) {
            leftPaddingViewOption.state = leftPaddingViewOption.state ^ QStyle::State_HasFocus;
        }
        /*!
         * \note 为了正确地绘制边距区域的背景颜色，这里需要paint一次并且不希望把数据绘制上去，不然会重叠
         *       所以设置一个标志位让model的data函数返回空，绘制完成之后，重置标志位
         */
        MuTableViewItemModel::setEmptyData(true);
        QStyledItemDelegate::paint(painter, leftPaddingViewOption, index);
        MuTableViewItemModel::setEmptyData(false);
    }
    QStyledItemDelegate::paint(painter, viewOption, index);
}

bool MuStyleItemDelegate::editorEvent(QEvent *event,
                                      QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index)
{
    QRect decorationRect = option.rect;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos())) {
        if (index.column() == 1) {
            bool data = model->data(index, Qt::UserRole).toBool();
            model->setData(index, !data, Qt::UserRole);
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}


MuTableIndexWidget::MuTableIndexWidget(int buttonFlags, QModelIndex index, QWidget *parent) :
    QWidget(parent)
{
    QPushButton *pCollectBtn = new QPushButton(this);
    QPushButton *pDownloadBtn = new QPushButton(this);
    pCollectBtn->setObjectName(QStringLiteral("tableCollectBtn"));
    pDownloadBtn->setObjectName(QStringLiteral("tableDownloadBtn"));
    pCollectBtn->setCheckable(true);
    pDownloadBtn->setCheckable(true);
    pCollectBtn->setFixedSize(20, 20);
    pDownloadBtn->setFixedSize(20, 20);
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(pCollectBtn);
    pLayout->addWidget(pDownloadBtn);

    if (buttonFlags == CollectButton) {
        pDownloadBtn->hide();
    } else if (buttonFlags == DownloadButton) {
        pCollectBtn->hide();
    } else if (static_cast<WidgetType>(buttonFlags) == (CollectButton | DownloadButton)) {
    } else {
        pDownloadBtn->hide();
        pCollectBtn->hide();
    }

    connect(pCollectBtn, &QPushButton::clicked, [=]() { emit CollectBtnClicked(index); });
    connect(pDownloadBtn, &QPushButton::clicked, [=]() { emit DownloadButtonClicked(index); });
}

MuTableView::MuTableView(QWidget *parent)
    : QTableView(parent)
{
    installEventFilter(this);
    m_pHeaderView = new MuHeaderView(Qt::Horizontal, this);
    setHorizontalHeader(m_pHeaderView);
    m_pHeaderView->setCascadingSectionResizes(true);
    MuStyleItemDelegate *pDelegate = new MuStyleItemDelegate(this);
    setItemDelegate(pDelegate);
    m_pModel = new MuTableViewItemModel(this);
    setModel(m_pModel);

    setMouseTracking(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setShowGrid(false);
    setSortingEnabled(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setVisible(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(m_pHeaderView, &MuHeaderView::MouseEnter, this, &MuTableView::onHeaderViewEnter);
    connect(m_pHeaderView, &MuHeaderView::EnableSort, this, &MuTableView::onEnableSort, Qt::DirectConnection);
}

void MuTableView::setHorizontalHeaderLabels(const QStringList labels)
{
    m_pModel->setHeaderLables(labels);
    m_pModel->setColumnCount(labels.size());
    m_pModel->insertRow(0);
//    m_pModel->setTable("LocalMusicTrack");
//    m_pModel->select();
}

void MuTableView::setItemData(const QModelIndex &index, QVariant var)
{
    if (!index.isValid())
        return;

    m_pModel->setDisplayData(index, var);
}

QVariant MuTableView::getItemData(const QModelIndex &index) const
{
    if (!index.isValid())
        return QVariant();

    return m_pModel->itemData(index).value(Qt::DisplayRole);
}

void MuTableView::updateData(const QList<QStringList> &data)
{
    m_pModel->updateData(data);
    emit TableDataChanged();
}

void MuTableView::setModelTable(MuTableView::SqlTable table)
{
    switch (table) {
    case LocalMusicTable:
        m_pModel->setTable(QLatin1String("LocalMusicTable"));
        m_pModel->select();
        qDebug() << m_pModel->rowCount();
        emit TableRowCount(m_pModel->rowCount());
        break;
    }
}

void MuTableView::updateData()
{
    qDebug() << "slect" << m_pModel->select();
}

void MuTableView::onHeaderViewEnter()
{
    m_pModel->setHoverRow(-1);
    int columnCount = model()->columnCount();
    for (int i=columnCount-1; i>=0; --i) {
        update(model()->index(m_nCurHoverRow, i));
    }
    m_nCurHoverRow = -1;
}

void MuTableView::onEnableSort(bool enabled)
{
    setSortingEnabled(enabled);
}

void MuTableView::mouseMoveEvent(QMouseEvent *ev)
{
    int row = indexAt(ev->pos()).row();
    updateHoverRow(row);
}

void MuTableView::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev)
    m_pModel->setHoverRow(-1);
    int columnCount = model()->columnCount();
    for (int i=columnCount-1; i>=0; --i) {
            update(model()->index(m_nCurHoverRow, i));
    }
    m_nCurHoverRow = -1;
}

bool MuTableView::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::ContextMenu) {
        MuTableRightButtonMenu *pDlg = new MuTableRightButtonMenu(MuTableRightButtonMenu::LocalTable, this);
        pDlg->move((cursor().pos()));
        qDebug() << cursor().pos() << this->mapFromGlobal(cursor().pos());
        pDlg->show();

//        QAction *ac = new QAction(QIcon(":/images/menuPlay32_515151.png"), "testtesttesttesttesttesttest", this);
//        QMenu *menu = new QMenu;
//        menu->addAction(ac);
//        menu->exec(cursor().pos());
    }
    return QTableView::eventFilter(o, e);
}

void MuTableView::updateHoverRow(const int row)
{
    if (row == m_nCurHoverRow)
        return;

    m_pModel->setHoverRow(row);
    int columnCount= model()->columnCount();
    for (int i=columnCount-1; i>=0; --i) {
        update(model()->index(m_nCurHoverRow, i));
        update(model()->index(row, i));
    }
//    table_model->showToolTip(row);  //自定义方法用来进行QToolTip的显示
    m_nCurHoverRow = row;
}


#include <QDebug>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QTableView>
#include <QScrollBar>
#include "mutableviewhelper.h"

MuTableViewModel::MuTableViewModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

//int MuTableViewModel::rowCount(const QModelIndex &parent) const
//{
//    return 0;
//}

//int MuTableViewModel::columnCount(const QModelIndex &parent) const
//{
//    return 0;
//}

QVariant MuTableViewModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    if (role == Qt::TextAlignmentRole) {
        qDebug() << "data";
        return Qt::AlignRight;
    }
    return QVariant("test");
}

QVariant MuTableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical) {
        return QVariant();
    }
    if (role == Qt::SizeHintRole) {
    auto* p = qobject_cast<QTableView*>(this->parent());
    if (p == nullptr) return QVariant();
    // Parent total width.
    const int w = p->viewport()->size().width() -
        p->verticalScrollBar()->sizeHint().width();
    QSize qs;
    // Default height.
    qs.setHeight(p->verticalHeader()->defaultSectionSize());
    // Width per column.
    switch (section) {
      case 0:
        qs.setWidth(w * 0.45);
        return QVariant(qs);
      case 1:
        qs.setWidth(w * 0.45);
        return QVariant(qs);
      // ... others
      default: ;
    }
    return QVariant();
    }
    if (role == Qt::DisplayRole) {
    // header titles.
    }
}


MuPushButtonDelegate::MuPushButtonDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void MuPushButtonDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
//    QStyleOptionViewItem viewOption(option);
//    initStyleOption(&viewOption, index);
//    if (option.state.testFlag(QStyle::State_HasFocus))
//           viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

//    //添加鼠标滑过的背景色
//    if(option.state & QStyle::State_MouseOver){
//        painter->fillRect(viewOption.rect, QColor(180, 200, 220));
//    }

//    QStyledItemDelegate::paint(painter, viewOption, index);

    QStyleOptionViewItem  view_option(option);
    if (view_option.state & QStyle::State_HasFocus) {
        view_option.state = view_option.state ^ QStyle::State_HasFocus;
    }

    //添加鼠标滑过的背景色
    if(option.state & QStyle::State_MouseOver){
        painter->fillRect(view_option.rect, QColor(180, 200, 220));
    }

    QStyledItemDelegate::paint(painter, view_option, index);


//    if (index.column() == 1)
//    {
//        bool data = index.model()->data(index, Qt::UserRole).toBool();

//        QStyleOptionButton checkBoxStyle;
//        checkBoxStyle.state = data ? QStyle::State_On : QStyle::State_Off;
//        checkBoxStyle.state |= QStyle::State_Enabled;
//        checkBoxStyle.iconSize = QSize(20, 20);
//        checkBoxStyle.rect = option.rect;

//        QPushButton checkBox;
//        QApplication::style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &checkBoxStyle, painter, &checkBox);
//   }
}


//MuHeaderView::MuHeaderView(Qt::Orientation orientation, QWidget *parent) :
//    QHeaderView(orientation, parent)
//{
////    setHighlightSections(true);
//    setMouseTracking(true);
//    setSectionsClickable(true);
//}

//void MuHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
//{
//    qDebug() << "paintSection";
//    QRect ct(rect.x()+30, 0, 20, 30);
//    painter->save();
//    QHeaderView::paintSection(painter, rect, logicalIndex);
//    painter->restore();

////    if (logicalIndex == 1)
////    {
////        QStyleOptionButton option;
////        option.initFrom(this);

//////        if (m_bChecked)
//////            option.state |= QStyle::State_Sunken;

//////        if (m_bTristate && m_bNoChange)
//////            option.state |= QStyle::State_NoChange;
//////        else
//////            option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off;
////        option.state = QStyle::State_On;
////        if (testAttribute(Qt::WA_Hover) && underMouse()) {
//////            if (m_bMoving)
////                option.state |= QStyle::State_MouseOver;
//////            else
//////                option.state &= ~QStyle::State_MouseOver;
////        }

////        QPushButton checkBox;
////        option.iconSize = QSize(20, 20);
////        option.rect = rect;
//////        style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &option, painter, &checkBox);
////        style()->drawItemPixmap(painter, rect, Qt::AlignRight | Qt::AlignVCenter, QPixmap(":/images/addPlaylist32_Gray.png"));
////        //style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
//////        style()->drawItemText(painter, rect, Qt::AlignLeft | Qt::AlignVCenter, this->palette(), true, "test");
////    }
//}



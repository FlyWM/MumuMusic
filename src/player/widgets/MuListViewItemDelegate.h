#ifndef MULISTVIEWITEMDELEGATE_H
#define MULISTVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>

class MuListViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MuListViewItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // MULISTVIEWITEMDELEGATE_H

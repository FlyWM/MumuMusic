/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUTABLEVIEW_H
#define MUTABLEVIEW_H

#include <QTableView>
#include <QStyledItemDelegate>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QSqlTableModel>

class MuHeaderViewEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit MuHeaderViewEventFilter(QObject *parent = nullptr);

    virtual bool eventFilter(QObject *watched, QEvent *event);
};

class MuHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    explicit MuHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);

    enum SortOrder
    {
        Default, // 0: 添加歌曲的顺序
        Ascending, // 1: AAA-ZZZ
        Descending, // 2: ZZZ-AAA
    };

    void setHeaderWidth(const int width);
    /**
     * @brief setSectionMinSize 设置每一个section的最小大小
     * @param logicalIndex section索引
     * @param size 大小
     */
    void setSectionMinSize(int logicalIndex, int size);

    /**
     * @brief setSectionScale Fixed 或者 Custom section 必须为0
     * @param scale eg: "0,1,2,1"
     */
    void setSectionScale(QString scale);

signals:
    void MouseEnter();
    void EnableSort(bool enabled);


protected:
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    /**
     * @brief mouseMoveEvent HeaderView宽度固定，不产生ScrollBar
     * @param e QMouseEvent *
     */
    virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void onSectionClicked(const int logicalIndex);

private:
    int m_nHeaderWidth;
    bool m_bPressed;
    bool m_bReachedMaxWidth;
    int m_nPressedX;
    int m_nCurPessedSectionIndex;
    QString m_strScale;
    QHash<int, int> m_sectionMinSize;
    QHash<int, int> m_sectioinSortOrder;
};


class MuTableViewItemModel : public QSqlTableModel
{
    Q_OBJECT
public:

public:
    MuTableViewItemModel(QObject *parent = nullptr);

//    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                        int role = Qt::DisplayRole) const;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void updateData(QList<QStringList> data);
    void setHoverRow(const int row);
    void setColumnCount(const int count);
    void setHeaderLables(const QStringList headerLabels);
    void setDisplayData(const QModelIndex &index, QVariant var);

    static void setEmptyData(bool empty) { m_empty = empty; }

private:
    QList<QStringList> m_data;
    QStringList m_headerLabels = { "1", "2", "3", "4", "5", "6"};
    int m_columnCount;
    int m_nHoverRow;
    bool m_bHover;
    static bool m_empty;
};


class MuStyleItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MuStyleItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

class MuTableIndexWidget : public QWidget
{
    Q_OBJECT

public:
    enum WidgetType
    {
        CollectButton = 0x0001,
        DownloadButton = 0x0002,
    };
    explicit MuTableIndexWidget(int buttonFlags, QModelIndex index, QWidget *parent = nullptr);

signals:
    void CollectBtnClicked(QModelIndex index);
    void DownloadButtonClicked(QModelIndex index);
};

class QStandardItemModel;
class QSqlTableModel;
class MuTableView : public QTableView
{
    Q_OBJECT

public:
    enum SqlTable
    {
        LocalMusicTable,
    };

public:
    MuTableView(QWidget *parent = nullptr);

    void setHeaderMaxWidth(const int width);
    void setHorizontalHeaderLabels(const QStringList labels);

    MuHeaderView *headerView () { return m_pHeaderView; }
    void setItemData(const QModelIndex &index, QVariant var);
    QVariant getItemData(const QModelIndex &index) const;

//    MuTableViewItemModel *model() const;

    void updateData(const QList<QStringList> &data);

    void setModelTable(SqlTable table);

    void updateData();

signals:
    void TableDataChanged();
    void TableRowCount(int cnt);

private slots:
    void onHeaderViewEnter();
    void onEnableSort(bool enabled);

protected:
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void leaveEvent(QEvent *ev);
    bool eventFilter(QObject *o, QEvent *e);

private:
    /**
     * @brief updateHoverRow 鼠标划过时更新整行的颜色
     * @param row 划过时的行
     */
    void updateHoverRow(const int row);

private:
    MuHeaderView *m_pHeaderView;
    MuTableViewItemModel *m_pModel;
    int m_nCurHoverRow;
};

#endif // MUTABLEVIEW_H

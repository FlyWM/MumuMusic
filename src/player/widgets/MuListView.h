#ifndef MULISTVIEW_H
#define MULISTVIEW_H

#include <QListView>

class QStandardItemModel;
class MuListView : public QListView
{
    Q_OBJECT
public:
    MuListView(QWidget *parent = nullptr);

    void updateData(QList<QStringList> data);

private:
    QStandardItemModel *m_pModel;
};

#endif // MULISTVIEW_H

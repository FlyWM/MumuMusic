#ifndef MULISTWIDGETITEM_H
#define MULISTWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>

class MuListWidgetItem : public QWidget, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit MuListWidgetItem(QIcon icon, const QString itemName, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MULISTWIDGETITEM_H

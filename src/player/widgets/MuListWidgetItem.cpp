#include <QHBoxLayout>
#include <QLabel>
#include "MuListWidgetItem.h"

MuListWidgetItem::MuListWidgetItem(QIcon icon, const QString itemName, QWidget *parent)
    : QWidget(parent)
{
    QLabel *pIconLabel1 = new QLabel(this);
    QLabel *pNameLabel = new QLabel(this);
    QLabel *pIconLabel2 = new QLabel(this);
    pIconLabel1->setPixmap(QPixmap(icon.name()));
    pNameLabel->setText(itemName);
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->addWidget(pIconLabel1);
    pMainLayout->addWidget(pNameLabel);
    pMainLayout->addWidget(pIconLabel2);
}

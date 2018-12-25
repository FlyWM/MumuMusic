#ifndef MUBASEWIDGET_H
#define MUBASEWIDGET_H

#include <QWidget>

class MuBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuBaseWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // MUBASEWIDGET_H

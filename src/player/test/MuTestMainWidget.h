#ifndef MUTESTMAINWIDGET_H
#define MUTESTMAINWIDGET_H

#include <QWidget>

class MuTestCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuTestCentralWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

class MuTestMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuTestMainWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

#endif // MUTESTMAINWIDGET_H

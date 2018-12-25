/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUDIALOGUI_H
#define MUDIALOGUI_H

#include <QWidget>
#include <QPushButton>
#include "MuBaseWidget.h"

class MuDialogCloseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MuDialogCloseButton(QWidget *parent = 0);

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
};

class MuDialogTitleWidget : public MuBaseWidget
{
    Q_OBJECT

public:
    explicit MuDialogTitleWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QPoint m_startPoint;
};

namespace Ui {
class MuDialogUI;
}
class QVBoxLayout;
class MuDialogUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuDialogUI(QWidget *parent = 0);
    ~MuDialogUI();

    void setModal(bool modal);
    void setCenralWidgetFixedSize(const QSize size);
    void setBottomVisible(bool visible);
    void setButtonsText(const QString &text1, const QString &text2);
    void setMainWidget(QWidget *widget);

    void hideTitle();
    void hideBottom();

protected:

signals:
    void Button1Clicked();
    void Button2Clicked();

protected:
    virtual bool event(QEvent *event);

private slots:
    void on_dlgCloseBtn_clicked();

private:
    Ui::MuDialogUI *ui;
    QWidget *m_pMainWidget;
    QVBoxLayout *m_pMainWidgetLayout;
    bool m_bMousePressed;
    QPoint m_startPoint;
};

#endif // MUDIALOGUI_H

/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUSHADOWWIDGET_H
#define MUSHADOWWIDGET_H

#include <QWidget>

class QVBoxLayout;
class MuGraphicsDropShadowEffectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MuGraphicsDropShadowEffectWidget(QWidget *parent = nullptr);

    void setMainWidget(QWidget *widget);
    void setShadowSize(int size);

protected:
    virtual void paintEvent(QPaintEvent *e);

private:
    QWidget *m_pMainWidget;
    QVBoxLayout *m_pMainLayout;
};

#endif // MUSHADOWWIDGET_H

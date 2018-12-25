/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUPLAYSTATUSBARUI_H
#define MUPLAYSTATUSBARUI_H

#include <QWidget>
#include <QSlider>

class MuBaseSlider : public QSlider
{
    Q_OBJECT

public:
    explicit MuBaseSlider(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *ev);
};

class MuVoiceSlider : public MuBaseSlider
{
    Q_OBJECT

public:
    explicit MuVoiceSlider(QWidget *parent = nullptr);

protected:
    virtual void enterEvent(QEvent *ev);
    virtual void leaveEvent(QEvent *ev);
};

namespace Ui {
class MuPlayStatusBarUI;
}

class MuPlayStatusBarUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuPlayStatusBarUI(QWidget *parent = 0);
    ~MuPlayStatusBarUI();

protected:
    virtual void paintEvent(QPaintEvent *ev);

private:
    Ui::MuPlayStatusBarUI *ui;

    const QStringList m_playOrderPro = { "listRepeat", "singleRepeat", "randomPlay", "oderPlay" };
    int m_curPlayOrderIndex;
};

#endif // MUPLAYSTATUSBARUI_H

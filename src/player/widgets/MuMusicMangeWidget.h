/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUMUSICMANGEWIDGET_H
#define MUMUSICMANGEWIDGET_H

#include <QWidget>

/**
 * @brief The MuMusicMangeWidget class
 *  the left widget that manages the songs
 */
class MuMusicMangeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuMusicMangeWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QWidget *createMangeScrollArea();

signals:
    void ListItemPressed(const int index);

public slots:
};

#endif // MUMUSICMANGEWIDGET_H

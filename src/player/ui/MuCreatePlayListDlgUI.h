/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUCREATEPLAYLISTDLGUI_H
#define MUCREATEPLAYLISTDLGUI_H

#include <QWidget>

namespace Ui {
class MuCreatePlaylistDlgUI;
}

class MuCreatePlaylistDlgUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuCreatePlaylistDlgUI(QWidget *parent = 0);
    ~MuCreatePlaylistDlgUI();

protected:
    virtual void paintEvent(QPaintEvent *e);

signals:
    void HideWidget();

private:
    Ui::MuCreatePlaylistDlgUI *ui;
};

#endif // MUCREATEPLAYLISTDLGUI_H

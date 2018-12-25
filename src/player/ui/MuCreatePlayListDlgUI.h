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

#ifndef MUPLAYLISTMAINWIDGETUI_H
#define MUPLAYLISTMAINWIDGETUI_H

#include <QWidget>
#include <QHeaderView>


namespace Ui {
class MuPlaylistMainWidgetUI;
}

class MuPlaylistMainWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuPlaylistMainWidgetUI(QWidget *parent = 0);
    ~MuPlaylistMainWidgetUI();

protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void showEvent(QShowEvent *e);

private slots:
    void on_songsListBtn_clicked();

private:
    void initTableWidget();

private:
    Ui::MuPlaylistMainWidgetUI *ui;
    QAction *m_pAc;
};

#endif // MUPLAYLISTMAINWIDGETUI_H

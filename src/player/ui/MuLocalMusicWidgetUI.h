/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MULOCALMUSICWIDGET_H
#define MULOCALMUSICWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include "MuBaseWidget.h"
#include "MuGlobal.h"
#include "MuLocalMusicManager.h"

namespace Ui {
class MuLocalMusicWidget;
}
class MuSelectLocalMusicWidgetUI;
class MuDialogUI;
class QButtonGroup;
class MuLocalMusicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MuLocalMusicWidget(QWidget *parent = nullptr);
    ~MuLocalMusicWidget();

    void setScrollArea(QScrollArea *scrollArea);
    /**
     * @brief adjustRightMargin
     *  \note 需要考虑的问题是：如果有滚动条，设置的right-margin是从滚动条左侧边缘开始计算的，而不是widget的边缘，
     *        为了使到widget边缘的大小不变，当出现滚动条和没有滚动条时分别设置不同的right-margin大小。
     */
    void adjustRightMargin(bool aboutToShowBar = false);

protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void showEvent(QShowEvent *e);

signals:
    void EnableScrollAreaBar(bool enabled, bool aboutToShowBar = false);
    void LocalSongsIsNotEmpty();

private slots:
    void onAddFolderBtnClicked();
    void onOkBtnClicked();
    void onGroupButtonToggled(int index, bool checked);

    /**
     * @brief onUpdateDone select music folder and update completed
     */
    void onUpdateDone();

private:
    void initTableView();

private:

private:
    Ui::MuLocalMusicWidget *ui;
    MuSelectLocalMusicWidgetUI *m_pSelectMainWidget;
    QButtonGroup *m_pBtnGroup;
    MuDialogUI *m_pDlg;
    QScrollArea *m_pScrollArea;
    int m_nLocalSongsNb;
    Mu::LocalMusicButton m_curButton;
    MuLocalMusicManager &m_lmm = MuLocalMusicManager::getInstance();
};

#endif // MULOCALMUSICWIDGET_H

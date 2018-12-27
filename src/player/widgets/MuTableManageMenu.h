/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUTABLEMANAGEMENU_H
#define MUTABLEMANAGEMENU_H

#include <QMenu>
#include <QQueue>
#include "MuDialogUI.h"
#include "MuShadowWindow.h"

/**
 * @brief The MuTableRightButtonMenu class
 *  音乐列表右键弹出菜单
 */
class MuTableRightButtonMenu : public MuShadowWindow<QWidget>
{
    Q_OBJECT

public:
    enum TableType
    {
        LocalTable,
        PlayListTable,
    };

    MuTableRightButtonMenu(TableType table, int tableRowIndex, QWidget *parent = nullptr);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void onActionTriggered(QAction *action);

private:
    void createMainWidget();
    void deleteLastOne();
    void deleteThisOne();

private:
    TableType m_tableType;
    int m_tableRowIndex;
    QAction *m_pViewCommentsAc;
    QAction *m_pPlayAc;
    QAction *m_pNextSongAc;
    QAction *m_pAddToPlaylistAc;
    QAction *m_pShareAc;
    QAction *m_pCopyLkAdAc;
    QAction *m_pUpToMyCloudAc;
    QAction *m_pOpenFolderAc;
    QAction *m_pDeleteFromListAc;
    QAction *m_pDeleteFromDiskAc;

    QMenu *m_pMenu;

private:
    static QQueue <MuTableRightButtonMenu *> m_instances;
};

#endif // MUTABLEMANAGEMENU_H

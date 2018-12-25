#ifndef MUTABLEMANAGEMENU_H
#define MUTABLEMANAGEMENU_H

#include <QMenu>
#include "MuDialogUI.h"
#include "MuShadowWindow.h"

class MuTableRightButtonMenu : public MuShadowWindow<QWidget>
{
    Q_OBJECT

public:
    MuTableRightButtonMenu(QWidget *parent = nullptr);

private:
    void createMainWidget();

private:
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
};

//class MuTableRightButtonMenu : public QMenu
//{
//    Q_OBJECT

//public:
//    MuTableRightButtonMenu(QWidget *parent = nullptr);
//};

class QAction;
class QWidgetAction;
class MuTableManageMenu : public QMenu
{
    Q_OBJECT

public:
    enum TableType
    {
        LocalTable,
        PlayListTable,
    };

public:
    MuTableManageMenu(TableType table, QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *e);

protected:

private:
    void createMainWidget();

private:
    TableType m_tableType;
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
};

#endif // MUTABLEMANAGEMENU_H

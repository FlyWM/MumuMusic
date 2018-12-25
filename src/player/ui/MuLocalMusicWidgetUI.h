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

class MuFindNativeMusciFile : public QObject
{
    Q_OBJECT
public:
    MuFindNativeMusciFile(QObject *parent = nullptr);

    void setFilePathsAndFilters(const QStringList paths, const QStringList filters);

signals:
    void Finished();
    void FoundFiles(const QList<QStringList> &data);

public slots:
    void startFind();


private:
#if 0
    static QStringList findMusicFiles(const QString &path);
    static void reduce(QStringList &musicFiles, const QStringList &res);
#endif
    QStringList findFiles(const QString &startDir, QStringList filters);

private:
#if 0
    static QStringList m_paths;
    static QStringList m_filters;
    static QStringList m_musciFiles;
#endif
    QStringList m_paths;
    QStringList m_filters;
};

namespace Ui {
class MuLocalMusicWidget;
}
class MuSelectLocalMusicWidgetUI;
class MuDialogUI;
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
    /**
     * @brief onFoundFiles 更新本地音乐列表
     * @param data 表的数据
     */
    void onFoundFiles(const QList<QStringList> &data);
    void onGroupButtonClicked(int index);

private:
    void initTableView();

private:

private:
    Ui::MuLocalMusicWidget *ui;
    MuSelectLocalMusicWidgetUI *m_pSelectMainWidget;
    MuDialogUI *m_pDlg;
    QScrollArea *m_pScrollArea;
    int m_nLocalSongsNb;
    Mu::LocalMusicButton m_curButton;
};

#endif // MULOCALMUSICWIDGET_H

/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MULOCALMUSICDETAILUI_H
#define MULOCALMUSICDETAILUI_H

#include <QWidget>
#include <QScrollArea>
#include "MuGlobal.h"

class MuLocalTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MuLocalTableViewWidget(QWidget *parent = nullptr);
    ~MuLocalTableViewWidget();

signals:
    void WidthChanged(const int width);

protected:
    virtual void resizeEvent(QResizeEvent *event);
};


namespace Ui {
class MuLocalMusicDetailUI;
}

class QPushButton;
class QLineEdit;
class MuTableView;
class MuLocalMusicDetailUI : public QWidget
{
    Q_OBJECT

public:
    explicit MuLocalMusicDetailUI(QWidget *parent = nullptr);
    ~MuLocalMusicDetailUI();

    void setCurLocalButton(Mu::LocalMusicButton button);
    void setScrollViewPortHeight(int height);

    QWidget *thumbWidget();
    QPushButton *matchButton();
    QLineEdit *searchLocalMusicBox();
    MuTableView *tableView() const;
    void updateTable(const QList<QStringList> &data);
    /**
     * @brief updateListView
     * @param data <(pic,singer, nb),(pic,singer, nb),(pic,singer, nb)>
     */
    void updateListView(const QList<QStringList> &data);

signals:
    /**
     * @brief EnableScrollAreaBar 通知本地音乐界面的列表页面，是否可以显示滚动条
     * @param enabled 是否可以显示滚动条
     *  \note
     *  当enabled为true时不一定会显示滚动条，只有当数据足够多时才显示
     * @param aboutToShowBar 是否需要显示滚动条
     */
    void EnableScrollAreaBar(bool enabled, bool aboutToShowBar = false);

    void TableRowCount(int count);

protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void showEvent(QShowEvent *e);

private slots:
    void on_localMatchBtn_toggled(bool checked);
    void adjustHeight();

private:

private:
    Ui::MuLocalMusicDetailUI *ui;
    Mu::LocalMusicButton m_curButton;
    int m_scrollViePortHeight;
    MuTableView *m_pTable;
};

#endif // MULOCALMUSICDETAILUI_H

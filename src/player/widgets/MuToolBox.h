/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUTOOLBOX_H
#define MUTOOLBOX_H

#include <QWidget>

class MuEventFilter : public QObject
{
    Q_OBJECT
public:
    MuEventFilter(QObject *parent = nullptr);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:
    void mouseEnter();
    void mouseLeave();
};

class QLabel;
/**
 * @brief The MuListItemWidget class
 *  play list item
 */
class MuListItemWidget : public QWidget
{
    Q_OBJECT
public:
    MuListItemWidget(const QString icon1, const QString icon2,
                     const QString itemName, QWidget *parent = nullptr);

    void setSelected(bool selected);

signals:
    void mouseEnter();
    void mouseLeave();

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    QLabel *m_pIconLabel;
    QLabel *m_pNameLabel;
    QLabel *m_pPlayStatusLabel;
    bool m_bSelected;
};

class QPushButton;
class MuPopupWidgetButton;
class MuOpenPlayListWidget : public QWidget
{
    Q_OBJECT

public:
    MuOpenPlayListWidget(const QString title, bool canCreatePlayList, QWidget *parent = nullptr);  

signals:
    void showList();
    void hideList();

private:
    QPushButton *m_pTitleBtn;
    MuPopupWidgetButton *m_pCreatePlayListBtn;
    QPushButton *m_pOpenListsBtn;
};

class QVBoxLayout;
class QListWidget;
class QListWidgetItem;
class MuToolBox : public QWidget
{
    Q_OBJECT
public:
    explicit MuToolBox(const QString boxTitle, bool isPlayList = false, QWidget *parent = nullptr);

    void setShrinkable(bool shrinkable);
    void addItem(const QString itemName, const QString itemIcon1, const QString itemIcon2 = "");

    int titleWidgetWidth() const;
    int listWidgetWidth() const;

signals:
    void ItemPressed(const int index);

private slots:

private:
    bool m_shrinkable;
    QVBoxLayout *m_pMainLayout;
    QListWidget *m_pListWidget;
    QWidget *m_pTitleWidget;
    static QHash<QListWidgetItem *, MuListItemWidget *> m_pListWidgets;
    static QList<QListWidgetItem *> m_pListItems;
};

#endif // MUTOOLBOX_H

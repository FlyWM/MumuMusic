#ifndef MUSMALLCONTROLS_H
#define MUSMALLCONTROLS_H

#include <QWidget>
#include <QLineEdit>

/**
 * @brief The MuPlayAddButton class
 *  play all or add all to playlist button
 */
class QPushButton;
class MuPlayAddButton : public QWidget
{
    Q_OBJECT
public:
    explicit MuPlayAddButton(QWidget *parent = nullptr);

signals:

public slots:

private:
    QPushButton *m_playButton;
    QPushButton *m_addToPlayListButton;
};

class MuSearchBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit MuSearchBox(QWidget *parent = nullptr);
};

class QLabel;
class QTimer;
class QProgressBar;
class MuRollingTipWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MuRollingTipWidget(QWidget *parent = nullptr);

    void startUpdating();
    void stopUpdate();
    void showFinished();
    void startMatching();
    void stopMatching();

private slots:
    void onTimeOut(QTimer *timer, QWidget *widget);

private:
    /**
     * @brief initUpdateWidget
     *  更新本地音乐提示
     */
    void initUpdateWidget();
    /**
     * @brief initFinishedWidget
     *  更新完成或匹配完成提示
     */
    void initFinishedWidget();
    /**
     * @brief initMatchWdiget
     *  匹配进度提示
     */
    void initMatchWdiget();

private:
    QWidget *m_pUpdatingWidget;
    QTimer *m_pUpTimer;
    QLabel *m_pUdIconLabel;
    QLabel *m_pUdTipLabel;

    QWidget *m_pFinishedWidget;
    QTimer *m_pFdTimer;
    QLabel *m_pFdIconLabel;
    QLabel *m_pFdTipLabel;

    QWidget *m_pMatchWidget;
    QTimer *m_pMTimer;
    QLabel *m_pMIconLabel;
    QLabel *m_pMTipLabel;
    QLabel *m_pMProgress;
    QProgressBar *m_pMProgBar;


};

#endif // MUSMALLCONTROLS_H

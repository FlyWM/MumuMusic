#ifndef MUMAINWINDOW_H
#define MUMAINWINDOW_H

#include "MuCustomWindow.h"

class MuScrollArea;
class MuLocalMusicWidget;
class MuMainWindow :
#ifdef Q_OS_LINUX
        public MuCustomWindow
#elif defined Q_OS_WIN32
        public MuWinAeroShadowWindow
#endif
{
    Q_OBJECT
public:
    MuMainWindow(QWidget *parent = nullptr);

    void initPos();
    static QPoint getMainWidgetPos();
    static QSize getMainWidgetSize();

protected:
    virtual void moveEvent(QMoveEvent *e);

private slots:
    void onLogicalDotsPerInchChanged(qreal dpi);

private:
    void initMainWindow();
    static QPoint m_pos;
#ifdef Q_OS_LINUX
    static MuCustomWindow *m_instance;
#elif defined Q_OS_WIN32
    static MuWinAeroShadowWindow *m_instance;
#endif
};

#endif // MUMAINWINDOW_H

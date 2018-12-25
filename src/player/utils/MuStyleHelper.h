#ifndef MUSTYLEHELPER_H
#define MUSTYLEHELPER_H

#include <QString>
#include <QObject>
#include <QMargins>
#include <QPushButton>

namespace MuUtils {
class MuStyleHelper : public QObject
{
public:
    MuStyleHelper();

    static void setStyle(const QString &qssFile);

    static int MuSmartScaleUI(int spec);
    static double rate();
    static void setPreRate(const double &preRate);
    static void setScaleFromPreRate(const double &scaleFromPreRate);
    static double preRate();
    static double scaleFromPreRate();
    static void scaleChildren(QObject &o);

    static QSize mainWindowSize();
    static int titileHeight();
    static QSize titleBarIconSize();
    static QSize titleBarButtonSize();
    static QSize mangeListItemSize();
    static QSize mangeListItemIconSize();
    static QSize mangeListItemCreateBtnSize();
    static QSize mangeListItemOpenListBtnSize();
    static int mangeWidgetWidth();
    static int playStatusBarHeight();

    // dialog
    static int dialogTitleHeight();
    static int dialogBottomHeight();

    // local music widget
    static QSize searchaBoxSize();
    static QSize localMatchButtonSize();
    static QSize localTabButtonSize();
    static QMargins localTitleLayoutMargins();
    static QSize localSelectNativeFolderButtonSize();
    static int localThumbWidgetWidth();
    static QSize localSearchNtvMusicBoxSize();
    static QSize localAddMusicDialogSize();
    static int localRightMargin();
    static int localTitleBarHeight();

    static int tableViewHeaderHeight();

    // play status bar
    static QSize preSongBtnSize();
    static QSize playBtnSize();
    static void playBarButtonAdjustRadius(QPushButton *preBtn, QPushButton *playBtn, QPushButton *nextBtn);

private:
    static double m_preRate;
    static double m_scaleFromPreRate;

    static QSize m_switchSongBtnSize;
    static QSize m_playSongBtnSize;
};
}


#endif // MUSTYLEHELPER_H

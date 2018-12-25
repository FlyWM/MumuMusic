/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUGLOBAL_H
#define MUGLOBAL_H

#ifdef Q_CC_MSVC
    #define CN_STR_(str) QString::fromLocal8Bit(str)
#endif

#include <QMetaType>

typedef struct {
    QString iconPath;
    QString title;
    QString songsNb;
} MuListItemData;
Q_DECLARE_METATYPE(MuListItemData)

namespace Mu {
enum LocalMusicButton {
    NullButton = -1,
    ListButton,
    ArtistButton,
    AlbumButton,
    FolderButton
};
}


#endif // MUGLOBAL_H

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

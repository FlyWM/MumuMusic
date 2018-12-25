/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUIMAGEHANDLER_H
#define MUIMAGEHANDLER_H

#include <QObject>

class MuImageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MuImageHandler(QObject *parent = nullptr);

    static QPixmap PixmapToRound(QPixmap &src, int radius);

signals:

public slots:
};

#endif // MUIMAGEHANDLER_H

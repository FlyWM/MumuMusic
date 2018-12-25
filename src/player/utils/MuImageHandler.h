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

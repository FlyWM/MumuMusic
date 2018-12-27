#ifndef MULOCALMUSICMANAGER_H
#define MULOCALMUSICMANAGER_H

#include <QObject>

class MuLocalMusicManagerPrivate;
class MuLocalMusicManager : public QObject
{
    Q_OBJECT

public:
    static MuLocalMusicManager &getInstance() {
        static MuLocalMusicManager instance;
        return instance;
    }

    void updateLocalMusic(const QStringList paths) {
        emit UpdateLocalMusic(paths);
    }

signals:
    void UpdateLocalMusic(const QStringList paths);
    void UpdateDone();

public slots:

private:

private:
    MuLocalMusicManagerPrivate *d;

private:
    explicit MuLocalMusicManager(QObject *parent = nullptr);
    MuLocalMusicManager(const MuLocalMusicManager &);
    MuLocalMusicManager &operator = (const MuLocalMusicManager&);
};

#endif // MULOCALMUSICMANAGER_H

#ifndef MULOCALMUSICMANAGER_P_H
#define MULOCALMUSICMANAGER_P_H

#include <QObject>

class MuLocalMusicManagerPrivate : public QObject
{
    Q_OBJECT

public:
    MuLocalMusicManagerPrivate(QObject *parent = nullptr);

public slots:
    void onUpdateLocalMusic(const QStringList paths);

signals:
    void Finished();
    void UpdateDone();

private:
    QStringList findFiles(const QString &startDir, QStringList filters);
};

#endif // MULOCALMUSICMANAGER_P_H

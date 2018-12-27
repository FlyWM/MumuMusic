#include <QThread>
#include <QDir>
#include <QTime>
#include <QDebug>
#include "MuLocalMusicManager.h"
#include "MuLocalMusicManager_p.h"
#include "MuMedia.h"
#include "MuDBManager.h"
#include "MuConversionTool.h"

MuLocalMusicManagerPrivate::MuLocalMusicManagerPrivate(QObject *parent)
    : QObject(parent)
{

}

void MuLocalMusicManagerPrivate::onUpdateLocalMusic(const QStringList paths)
{
    if (paths.isEmpty()) {
        emit Finished();
        return;
    }

    QStringList musicFiles;
    QStringList filters;
    filters << "*.mp3" << "*.wma" << "*.aac";
    for (auto &file : paths) {
        musicFiles.append(findFiles(file, filters));
    }
    QList<QStringList> data;
    for (auto &file : musicFiles) {
        MuMedia m(MuConversionTool::qstring2stdString(file));
        if (m.isValid()) {
            QStringList str;
            str << file << QString::fromStdString(m.audioDir())
                << QString::fromStdString(m.audioTitle())
                << QString::fromStdString(m.audioAlbum())
                << QString::fromStdString(m.audioArtist())
                << MuConversionTool::mcsToStrFormatTime(m.duration())
                << "" << QString::number(m.bitRate())
                << MuConversionTool::bytesToGBMBKB(m.fileSize()) << QString("0");
            data.append(str);
        }
    }
    MuDBManager::getInstance().insertData(MuDBManager::LocalMusicTrack, data);
    emit UpdateDone();
}

QStringList MuLocalMusicManagerPrivate::findFiles(const QString &startDir, QStringList filters)
{
    QStringList names;
    QDir dir(startDir);

    foreach (QString file, dir.entryList(filters, QDir::Files))
        names += startDir + '/' + file;

    foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        names += findFiles(startDir + '/' + subdir, filters);

    return names;
}

MuLocalMusicManager::MuLocalMusicManager(QObject *parent)
    : QObject(parent) 
{
    d = new MuLocalMusicManagerPrivate;
    QThread *pThread = new QThread;
    d->moveToThread(pThread);

    connect(this, &MuLocalMusicManager::UpdateLocalMusic, d, &MuLocalMusicManagerPrivate::onUpdateLocalMusic);
    connect(d, &MuLocalMusicManagerPrivate::UpdateDone, this, &MuLocalMusicManager::UpdateDone);

    pThread->start();
}



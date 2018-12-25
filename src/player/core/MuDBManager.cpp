/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QSqlDatabase>
#include <QHash>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "MuDBManager.h"

class MuDataBase : public QObject
{
public:
    MuDataBase(QObject *parent = nullptr);

    void initDB();
    void insertData(MuDBManager::DBTable table, const QStringList &data);

private:
    void initTables();

    inline QString sql_insertLocalTrack(const QStringList &data) {
        if (data.size() != 10)
            return QString();
        return QString("INSERT INTO LocalMusicTrack(file, dir, title, album, artist, duration," \
                       "timestamp, bitrate, filesize, ignored) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', %7, %8, '%9', %10);") \
                .arg(data.at(0)).arg(data.at(1)).arg(data.at(2)).arg(data.at(3)).arg(data.at(4)).arg(data.at(5)).arg(0)\
                .arg(data.at(7)).arg(data.at(8)).arg(data.at(9));
    }

private:
    QHash<QString, QSqlDatabase> dbs;
    QSqlDatabase db;
};

#define SQL_CHECK_TABLE(str)  \
    QString("SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME = '%1'").arg(str)

// 11
#define SQL_CREATE_TABLE_LocalMusicTrack  \
    QLatin1String("CREATE TABLE LocalMusicTrack(file TEXT, dir TEXT, title TEXT, album TEXT,artist TEXT, duration TEXT," \
                  "timestamp INTEGER, bitrate INTEGER, filesize TEXT, ignored INTEGER DEFAULT 0)")
#define SQL_CREATE_TABLE_LocalMusicTable  \
    QLatin1String("CREATE TABLE LocalMusicTable(linenb TEXT DEFAULT '', title TEXT, artist TEXT, album TEXT, duration REAL, filesize INTEGER)")

#define SQL_CREATE_TRIGGER_ON_LocalMusicTrack \
    QLatin1String("CREATE TRIGGER displayTable AFTER INSERT ON LocalMusicTrack" \
                   " BEGIN  INSERT INTO LocalMusicTable(title, artist, album, duration, filesize) " \
                   " VALUES (new.title, new.artist, new.album, new.duration, new.filesize); END")

MuDataBase::MuDataBase(QObject *parent)
    : QObject(parent)
{

}

void MuDataBase::initDB()
{
    if (db.isOpen())
        return;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MuData.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        qDebug() << "db serror: " << db.lastError();
        return;
    }
    initTables();
}

void MuDataBase::insertData(MuDBManager::DBTable table, const QStringList &data)
{
    QSqlQuery query;
    switch (table) {
    case MuDBManager::LocalMusicTrack:
        if (!db.isOpen()) return;
        qDebug() << query.exec(sql_insertLocalTrack(data));
        break;
    default:
        break;
    }
}

/**
 * @brief MuDataBase::initTables
 *  LocalMusicTrack
 */
void MuDataBase::initTables()
{
    QSqlQuery query;
    int nRecordCounts = 0;
    query.exec(SQL_CHECK_TABLE("LocalMusicTrack"));
    query.next();
    nRecordCounts = query.value(0).toInt();
    if (nRecordCounts <= 0) {
        query.exec(SQL_CREATE_TABLE_LocalMusicTrack);
    }

    query.exec(SQL_CHECK_TABLE("LocalMusicTable"));
    query.next();
    nRecordCounts = query.value(0).toInt();
    if (nRecordCounts <= 0) {
        qDebug() << "Create: " << query.exec(SQL_CREATE_TABLE_LocalMusicTable);
        qDebug() << "Trigger: " << query.exec(SQL_CREATE_TRIGGER_ON_LocalMusicTrack);
        qDebug() << query.lastError();
    }
}

MuDBManager::MuDBManager(QObject *parent)
    : QObject(parent)
    , db(new MuDataBase(this))
{

}

void MuDBManager::initDB()
{
    db->initDB();
}

void MuDBManager::insertData(DBTable table, const QStringList &data)
{
    switch (table) {
    case LocalMusicTrack:
        if (data.size() != 10)
            return;
        db->insertData(table, data);
        break;
    default:
        break;
    }
}


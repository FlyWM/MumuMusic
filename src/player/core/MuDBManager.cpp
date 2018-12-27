/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#include <QSqlDatabase>
#include <QApplication>
#include <QHash>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <QDebug>
#include "MuDBManager.h"

// LocalMusicTrack
// 记录本地所有音乐文件

// LocalMusicTable
// 用来显示到本地音乐列表

// 如果LocalMusicTrack表中的ignored字段为0，那么将显示到本地音乐列表
// 否则将不会显示。用户通过右键菜单->从列表删除操作将ignored置1。
// 建立在LocalMusicTrack的Trigger将会自动更新LocalMusicTable的数据


class MuDataBase : public QObject
{
public:
    MuDataBase(QObject *parent = nullptr);

    void initDB();
    void insertData(MuDBManager::DBTable table, const QList<QStringList> &data);
    void ignoreRow(MuDBManager::DBTable table, const int &row);

private:
    void initTables();

    inline QString sql_insertLocalTrack(const QStringList &data) {
        if (data.size() != 10)
            return QString();
        return QString("INSERT INTO LocalMusicTrack(file, dir, title, album, artist, duration," \
                       "timestamp, bitrate, filesize, ignored) VALUES (\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", %7, %8, \"%9\", %10);") \
                .arg(data.at(0)).arg(data.at(1)).arg(data.at(2)).arg(data.at(3)).arg(data.at(4)).arg(data.at(5)).arg(0)\
                .arg(data.at(7)).arg(data.at(8)).arg(data.at(9));
    }
    // check fields - file, dir
    inline QString sql_checkValueExists(const QStringList &data) {
        if (data.size() != 10)
            return QString();
        return QString("SELECT COUNT(*) FROM LocalMusicTrack WHERE file = \"%1\" AND dir = \"%2\"").arg(data.at(0)).arg(data.at(1));
    }
    inline QString sql_ignoreRowLocalTrack() {

    }

private:
    QHash<QString, QSqlDatabase> dbs;
    QSqlDatabase db;
};

#define SQL_TABLE_NAME QApplication::applicationDirPath() + "/MuData.db"

#define SQL_CHECK_TABLE(str)  \
    QString("SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME = '%1'").arg(str)

// 11
#define SQL_CREATE_TABLE_LocalMusicTrack  \
    QLatin1String("CREATE TABLE LocalMusicTrack(file TEXT, dir TEXT, title TEXT, album TEXT,artist TEXT, duration TEXT," \
                  "timestamp INTEGER, bitrate INTEGER, filesize TEXT, ignored INTEGER DEFAULT 0)")
#define SQL_CREATE_INDEX_LocalMusicTrack(field) \
    QLatin1String("CREATE INDEX "#field"_index on LocalMusicTrack ("#field");")

#define SQL_CREATE_TABLE_LocalMusicTable  \
    QLatin1String("CREATE TABLE LocalMusicTable(dir TEXT DEFAULT '', title TEXT, artist TEXT, album TEXT, duration REAL, filesize INTEGER)")

// create trigger on table LocalMusicTrack
// when insert a new record to LocalMusicTrack,
// at the monment, insert it to LocalMusicTable
#define SQL_CREATE_TRIGGER_ON_LocalMusicTrack \
    QLatin1String("CREATE TRIGGER display_trigger AFTER INSERT ON LocalMusicTrack" \
                  " BEGIN  INSERT INTO LocalMusicTable(dir, title, artist, album, duration, filesize) " \
                  " VALUES (new.dir, new.title, new.artist, new.album, new.duration, new.filesize); END")

#define SQL_CREATE_TRIGGER_ON_LocalMusicTable \
    QLatin1String("CREATE TRIGGER ignore_trigger AFTER DELETE ON LocalMusicTable" \
                  " BEGIN UPDATE LocalMusicTrack ")


MuDataBase::MuDataBase(QObject *parent)
    : QObject(parent)
{

}

void MuDataBase::initDB()
{
    if (db.isOpen())
        return;

    qDebug() << QApplication::applicationDirPath() + "/MuData.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(SQL_TABLE_NAME);
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

void MuDataBase::insertData(MuDBManager::DBTable table, const QList<QStringList> &data)
{
    QSqlQuery query;
    QTime time;
    switch (table) {
    case MuDBManager::LocalMusicTrack: {
        if (!db.isOpen()) return;
        time.start();
        bool success = false;
        // start transaction
        db.transaction();
        for (auto &row : data) {
            // do not insert the repetitive record
            query.exec(sql_checkValueExists(row));
            query.next();
            int nRecordCounts = query.value(0).toInt();
            if (nRecordCounts > 0)
                continue;

            success = query.exec(sql_insertLocalTrack(row));
            if (!success) {
                db.rollback();
                return;
            }
        }
        db.commit();
        break;
    }
    }
}

void MuDataBase::ignoreRow(MuDBManager::DBTable table, const int &row)
{
    QSqlQuery query;
    switch (table) {
    case MuDBManager::LocalMusicTrack:
        if (!db.isOpen()) return;
//        qDebug() << query.exec(sql_insertLocalTrack(data));
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
        if (query.exec(SQL_CREATE_TABLE_LocalMusicTrack)) {
            qDebug() << "create index: " << query.exec(SQL_CREATE_INDEX_LocalMusicTrack(file));
            qDebug() << "create index: " << query.exec(SQL_CREATE_INDEX_LocalMusicTrack(dir));
        }
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

void MuDBManager::insertData(DBTable table, const QList<QStringList> &data)
{
    switch (table) {
    case LocalMusicTrack:
        if (data.isEmpty())
            return;
        db->insertData(table, data);
        break;
    default:
        break;
    }
}

void MuDBManager::deleteRow(MuDBManager::DBTable table, const int &row)
{
    switch (table) {
    case LocalMusicTrack:
        if (row < 0)
            return;
        db->ignoreRow(table, row);
        break;
    default:
        break;
    }
}

QStringList MuDBManager::getAllArtists() const
{
    return QStringList();
}


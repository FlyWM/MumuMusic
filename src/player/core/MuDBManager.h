/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUDBMANAGER_H
#define MUDBMANAGER_H

#include <QObject>

class MuDBSql
{
public:
    static QLatin1String sql_ListTable() {
        return QLatin1String("SELECT dir, title, artist, album, duration, filesize FROM LocalMusicTrack where ignored = 0;");
    }
    static QLatin1String sql_ArtistTable() {
        return QLatin1String();
    }
};


class MuDataBase;
class MuDBManager : public QObject
{
    Q_OBJECT

public:
    enum DBTable
    {
        LocalMusicTrack,
    };

public:
    static MuDBManager &getInstance() {
        static MuDBManager dbmanger;
        return dbmanger;
    }

    void initDB();
    void insertData(DBTable table, const QList<QStringList> &data);
    void deleteRow(DBTable table, const int &row);

    QStringList getAllArtists() const;

private:
    explicit MuDBManager(QObject *parent = nullptr);
    MuDBManager(const MuDBManager&);
    MuDBManager &operator =(const MuDBManager&);

    MuDataBase *db;
};

#endif // MUDBMANAGER_H

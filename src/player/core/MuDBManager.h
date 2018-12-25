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
    void insertData(DBTable table, const QStringList &data);


private:
    explicit MuDBManager(QObject *parent = nullptr);
    MuDBManager(const MuDBManager&);
    MuDBManager &operator =(const MuDBManager&);

    MuDataBase *db;
};

#endif // MUDBMANAGER_H

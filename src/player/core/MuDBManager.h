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

/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef MUCONVERSIONTOOL_H
#define MUCONVERSIONTOOL_H

#include <QObject>
#include <iostream>

class MuConversionTool : public QObject
{
    Q_OBJECT
public:
    explicit MuConversionTool(QObject *parent = nullptr);

    static QString mcsToStrFormatTime(qint64 ms);
    static QString bytesToGBMBKB(qint64 size);
    static std::string qstring2stdString(const QString &str);
};

#endif // MUCONVERSIONTOOL_H

#include "muconversiontool.h"

// 定义GB、MB、KB的计算常量
static const int GB = 1024 * 1024 * 1024;
static const int MB = 1024 * 1024;
static const int KB = 1024;

MuConversionTool::MuConversionTool(QObject *parent)
    : QObject(parent)
{

}

QString MuConversionTool::mcsToStrFormatTime(qint64 ms)
{
    QString str, strH, strM, strS;
    int tns, thh, tmm, tss;
    tns  = ms / 1000000;
    thh  = tns / 3600;
    tmm  = (tns % 3600) / 60;
    tss  = (tns % 60);
    if (tmm>=0 && tmm<10)
        strM = QString("0%1").arg(tmm);
    else
        strM = QString::number(tmm);
    if (tss>=0 && tss<10)
        strS = QString("0%1").arg(tss);
    else
        strS = QString::number(tss);
    if (thh > 0) {
        if (thh < 10) {
            strH = QString("0%1").arg(thh);
            str = QString("%1:%2:%3").arg(strH).arg(strM).arg(strS);
        } else
            str = QString("%1:%2:%3").arg(thh).arg(strM).arg(strS);
    } else {
        str = QString("%1:%2").arg(strM).arg(strS);
    }
    return str;
}

QString MuConversionTool::bytesToGBMBKB(qint64 size)
{
    if (size / GB >= 1)
        return QString("%1 GB").arg(QString::number(size / (float)GB, 'f', 2));
    else if (size / MB >= 1)
        return QString("%1 MB").arg(QString::number(size / (float)MB, 'f', 2));
    else if (size / KB >= 1)
        return QString("%1 KB").arg(QString::number(size / (float)KB, 'f', 2));
    else
        return QString("%1 Bytes").arg(size);
}

std::string MuConversionTool::qstring2stdString(const QString &str)
{
#pragma execution_character_set("utf-8")
    return str.toLocal8Bit().toStdString();
}

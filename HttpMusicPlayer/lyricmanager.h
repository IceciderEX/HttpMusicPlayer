#ifndef __LYRICMANAGER_H__
#define __LYRICMANAGER_H__

// -------------------------------------------------------
// lyricmanager.h
// 创建者：Wanganmin
// 创建时间：2023/12/22
// 功能描述：用于实现对歌词的相关操作，包括读取，更新等等
// --------------------------------------------------------

#include <QStringList>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <QRegularExpression>
#include <QTime>
#include <QVector>
#include <QDebug>

class LyricManager 
{
public:
    LyricManager();
    ~LyricManager() = default;

    QVector<QString> updateLyrics(qint64 currentPosition);
    bool readLyricsFile(QString lyricsPath);
    void clearLyric();
    void setfilePath(const QString& path);
    void setDefaultLyrics();

private:
    int m_currentIndex;    // 当前歌词的索引
    QString m_filePath;    // 歌词文件路径
    QMap<qint64, QString> m_timeToLyrics;
};

#endif

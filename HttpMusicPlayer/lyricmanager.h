#ifndef __LYRICMANAGER_H__
#define __LYRICMANAGER_H__

// -------------------------------------------------------
// lyricmanager.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/22
// ��������������ʵ�ֶԸ�ʵ���ز�����������ȡ�����µȵ�
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
    int m_currentIndex;    // ��ǰ��ʵ�����
    QString m_filePath;    // ����ļ�·��
    QMap<qint64, QString> m_timeToLyrics;
};

#endif

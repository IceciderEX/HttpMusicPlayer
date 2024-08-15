#include "lyricmanager.h"

LyricManager::LyricManager() 
{
    m_filePath = "";
    readLyricsFile(m_filePath);
    m_currentIndex = 0;
}

void LyricManager::setfilePath(const QString& path)
{
    m_filePath = path;
}

// 清除当前的歌词信息
void LyricManager::clearLyric() 
{
    m_filePath = "";
    m_timeToLyrics.clear();
    m_currentIndex = 0;
}

// 设置默认的歌词，用于单独音频文件歌词的显示
void LyricManager::setDefaultLyrics() 
{
    m_timeToLyrics[0] = QStringLiteral("本歌曲没有提供歌词文件");
}

// 读取lyricsPath路径的歌词文件
bool LyricManager::readLyricsFile(QString lyricsPath)
{
    QFile file(lyricsPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QByteArray fileData = file.readAll();
        QString line = QString::fromUtf8(fileData);  // 使用\r\n拆分文本行
        QList<QString> lines = line.split("\\r\\n");
        foreach(const QString& eachLine, lines) 
        {
            // 歌词的正则表达式
            QRegularExpression regex("\\[(\\d{2}:\\d{2}\\.\\d{2})\\](.+)");
            QRegularExpressionMatch match = regex.match(eachLine);
            if (match.hasMatch()) 
            {
                QString timeStr = match.captured(1);
                QString lyricText = match.captured(2);
                QTime time = QTime::fromString(timeStr, "mm:ss.z");
                int milliseconds = time.minute() * 60000 + time.second() * 1000 + time.msec();
                m_timeToLyrics.insert(milliseconds, lyricText);
            }
        }
    }
    return true;
}

// 返回播放进度currentPosition对应的歌词
QVector<QString> LyricManager::updateLyrics(qint64 currentPosition) 
{
    QVector<QString> matchedLyrics;
    QString beforeLyric;
    QString curLyric;
    QString nextLyric;
    if (!m_timeToLyrics.empty()) 
    {
        // 找到最接近当前位置的歌词为下一句歌词（如果存在）
        auto it = m_timeToLyrics.lowerBound(currentPosition);
        if (it != m_timeToLyrics.end()) 
            nextLyric = it.value();
        if (it != m_timeToLyrics.begin())
            --it;
        curLyric = it.value(); // 现在的歌词
        if (it != m_timeToLyrics.begin()) 
        {
            --it; 
            beforeLyric = it.value(); // 前一句歌词
        }
        matchedLyrics.push_back(beforeLyric);
        matchedLyrics.push_back(curLyric);
        matchedLyrics.push_back(nextLyric);
    }
    else 
    {
        qDebug() << "m_timeToLyrics is empty";
    }
    return matchedLyrics;
}


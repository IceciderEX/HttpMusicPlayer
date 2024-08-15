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

// �����ǰ�ĸ����Ϣ
void LyricManager::clearLyric() 
{
    m_filePath = "";
    m_timeToLyrics.clear();
    m_currentIndex = 0;
}

// ����Ĭ�ϵĸ�ʣ����ڵ�����Ƶ�ļ���ʵ���ʾ
void LyricManager::setDefaultLyrics() 
{
    m_timeToLyrics[0] = QStringLiteral("������û���ṩ����ļ�");
}

// ��ȡlyricsPath·���ĸ���ļ�
bool LyricManager::readLyricsFile(QString lyricsPath)
{
    QFile file(lyricsPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QByteArray fileData = file.readAll();
        QString line = QString::fromUtf8(fileData);  // ʹ��\r\n����ı���
        QList<QString> lines = line.split("\\r\\n");
        foreach(const QString& eachLine, lines) 
        {
            // ��ʵ�������ʽ
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

// ���ز��Ž���currentPosition��Ӧ�ĸ��
QVector<QString> LyricManager::updateLyrics(qint64 currentPosition) 
{
    QVector<QString> matchedLyrics;
    QString beforeLyric;
    QString curLyric;
    QString nextLyric;
    if (!m_timeToLyrics.empty()) 
    {
        // �ҵ���ӽ���ǰλ�õĸ��Ϊ��һ���ʣ�������ڣ�
        auto it = m_timeToLyrics.lowerBound(currentPosition);
        if (it != m_timeToLyrics.end()) 
            nextLyric = it.value();
        if (it != m_timeToLyrics.begin())
            --it;
        curLyric = it.value(); // ���ڵĸ��
        if (it != m_timeToLyrics.begin()) 
        {
            --it; 
            beforeLyric = it.value(); // ǰһ����
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


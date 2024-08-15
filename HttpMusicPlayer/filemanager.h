#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

// -------------------------------------------------------
// filemanager.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/23
// ��������������json�ļ��Ķ�ȡ�������������ļ������أ����������Ϣ�ȵ��ļ�����
// --------------------------------------------------------

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHash>

#include "common.h"
#include "song.h"

class FileManager : public QObject 
{
    Q_OBJECT

private:
    SongPaths m_songPaths;
    SongNames m_songNames;
    QHash<QString, QVector<QString>> m_musicToSinger; // ����Gitee�ֿ��и��������������Ĺ�ϣ��
    QStringList m_searchOptions; // �û������ĺ�ѡ��
    QNetworkAccessManager* m_manager; // ����HTTP����ķ�����response�Ľ���

public:
    explicit FileManager(QObject* parent = nullptr);
    ~FileManager() = default;
    // Getter 
    QString getJsonPath() const;
    QString getMusicPath() const;
    QString getLyricPath() const;
    QString getImagePath() const;
    QStringList getSearchOptions() const;
    // Setter
    void setJsonPath(const QString& path);

    void fetchGiteeRepoFolders();
    void updateSearchOptions();
    QString userChooseJsonPath();
    QString userChooseSimpleMusicPath();
    void saveNetJson(QByteArray& data);
    bool fileExists(const QString& filePath);
    QVector<Song> processLocalJsonSongs(QVector<Song>& v);
    Song processSimpleFiles(bool autoImport, QString path);
    void downloadFiles(QStringList urlList, QString savePath, QStringList nameList);
    QVector<Song> getNetMusic(QString music, QString singer, QString url, QVector<Song>& v);
    void processNetUrl(QByteArray& data, QString path, QString mp3FileName, QString lyricFileName, QString imgFileName);

signals:

public slots:
    QVector<Song> readMusicJson(QVector<Song>& v, QByteArray& data, bool fromNetwork, QString searchMusicName, QString searchSingerName);
};

#endif

#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

// -------------------------------------------------------
// filemanager.h
// 创建者：Wanganmin
// 创建时间：2023/12/23
// 功能描述：用于json文件的读取，网络歌曲相关文件的下载，管理歌曲信息等等文件功能
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
    QHash<QString, QVector<QString>> m_musicToSinger; // 保存Gitee仓库中歌曲名到歌手名的哈希表
    QStringList m_searchOptions; // 用户搜索的候选项
    QNetworkAccessManager* m_manager; // 用于HTTP请求的发送与response的接收

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

#include "filemanager.h"

FileManager::FileManager(QObject* parent) : QObject(parent) 
{
    m_manager = new QNetworkAccessManager();
}

// �õ�����Gitee�ֿ������еĸ����������Ӧ�ĸ�������
void FileManager::fetchGiteeRepoFolders() 
{
    QNetworkAccessManager manager;
    QUrl url(NET_SONG_FOLDER);
    QNetworkRequest request(url);
    // ͨ����ȡGiteeҳ���html�ļ�ʵ��
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) 
    {
        QString htmlContent = QString(reply->readAll());
        // ������ʽƥ��ֿ����ļ������ƣ���Ϊ�������ƣ�
        QRegularExpression regex("<span class='simplified-path'></span>([^<]+)");
        QRegularExpressionMatchIterator musicMatches = regex.globalMatch(htmlContent);
        while (musicMatches.hasNext())
        {
            QRegularExpressionMatch match = musicMatches.next();
            QString folderName = match.captured(1);
            folderName.remove('\n');

            m_musicToSinger.insert(folderName, QVector<QString>());
            QString singerUrl = NET_SONG_FOLDER + folderName.toUtf8().toPercentEncoding();
            QUrl url(singerUrl);
            QNetworkRequest request(singerUrl);
            QNetworkReply* singerReply = manager.get(request);
            QEventLoop loop;
            QObject::connect(singerReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            if (singerReply->error() == QNetworkReply::NoError) 
            {
                htmlContent = QString(singerReply->readAll());
                // ������ʽƥ��ֿ����ļ������ƣ���Ϊ�������ƣ�
                QRegularExpressionMatchIterator singerMatches = regex.globalMatch(htmlContent);
                while (singerMatches.hasNext()) 
                {
                    match = singerMatches.next();
                    QString singerName = match.captured(1);
                    singerName.remove('\n');
                    m_musicToSinger[folderName].append(singerName);
                }
            }
            singerReply->deleteLater();
        }
    }
    reply->deleteLater();
    updateSearchOptions();
}

// ��Gitee�ֿ��¸����������Ӧ�ĸ���������Ϊ�����ĺ�ѡ������û���������
void FileManager::updateSearchOptions()
{
    for (auto i = m_musicToSinger.constBegin(); i != m_musicToSinger.constEnd(); ++i)
    {
        QString music = i.key();
        QVector<QString> singers = i.value();
        for each (QString singer in singers)
            m_searchOptions.push_back(music + "-" + singer);
    }
}

// ���û�ѡ��һ��json�ļ�
QString FileManager::userChooseJsonPath() 
{
    QList<QFile> fileList;
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        tr("Choosing Json file"),
        QDir::currentPath(),    // Ĭ�ϴ򿪵�·��
        tr("JSON file (*.json);")  
    );
    if (!filePath.isEmpty())
        m_songPaths.jsonPath = filePath;
    return filePath;
}

// ���û�ѡ��һ��������Ƶ�ļ�
QString FileManager::userChooseSimpleMusicPath()
{
    QList<QFile> fileList;
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        tr("Choosing Json file"), 
        QDir::currentPath(),    // Ĭ�ϴ򿪵�·��
        tr("Audio Files (*.mp3 *.wav *.flac *.aac);") 
    );
    if (!filePath.isEmpty())
        m_songPaths.jsonPath = filePath;
    return filePath;
}

// �ж��ļ��Ƿ����
bool FileManager::fileExists(const QString& filePath) 
{
    QFile file(filePath);
    return file.exists();
}

// ��ȡjson�ļ���Ӧ�ĸ���ļ��������ļ���ר��ͼƬ�ļ������ӵ��б�v��
QVector<Song> FileManager::readMusicJson(QVector<Song>& v, QByteArray& data, bool fromNetwork, QString searchMusicName, QString searchSingerName)
{
    QJsonDocument jsonDoc;
    if (fromNetwork)
    {
        jsonDoc = QJsonDocument::fromJson(data);
    }
    else
    {
        // ��ȡ music.json �ļ�
        QFile file(m_songPaths.jsonPath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "Failed to open music.json file:" << file.errorString();
        QByteArray jsonData = file.readAll();
        jsonDoc = QJsonDocument::fromJson(jsonData);
    }
    if (jsonDoc.isNull())
        qDebug() << "Failed to parse JSON from music.json file. JSON file maybe null";

    // ��ȡ�����б�
    QJsonObject rootObject = jsonDoc.object();
    QJsonArray musicList = rootObject.value("list").toArray();
    QVector<Song> allAddedSongs;
    // ���������б�������ظ����ļ��� QFile �����б�
    foreach(const QJsonValue & musicValue, musicList) 
    {
        // �õ������ļ�������
        QJsonObject musicObject = musicValue.toObject();
        QString path = musicObject.value("path").toString() + "/";

        QString mp3FileName = musicObject.value("mp3").toString();
        QString lyricFileName = musicObject.value("lyric").toString();
        QString imgFileName = musicObject.value("img").toString();
        QString musicName = musicObject.value("musicName").toString();  // �����������͸�����
        m_songNames.albumName = musicObject.value("albumName").toString();
        m_songPaths.lyricPath = RESOURCE_PATH_NO_SLASH + path + lyricFileName;
        m_songPaths.musicPath = RESOURCE_PATH_NO_SLASH + path + mp3FileName;
        m_songPaths.albumImgPath = RESOURCE_PATH_NO_SLASH + path + imgFileName;
        // �����Ӧ��Դ�����ڣ��򲻵���
        if (!fromNetwork)
        {
            if (!fileExists(m_songPaths.lyricPath) || !fileExists(m_songPaths.lyricPath) || !fileExists(m_songPaths.lyricPath)) 
            {
                qDebug() << "File missing";
                continue;
            }
        }
        // ����������͸�����
        QStringList artistAndTitle = musicName.split(" - ");
        if (artistAndTitle.size() == 2) 
        {
            m_songNames.singerName = artistAndTitle[0];
            m_songNames.musicName = artistAndTitle[1];
        }
        // ������������������Ҫ���ض�Ӧ�������ļ�
        if (fromNetwork) 
        {
            if (m_songNames.musicName != searchMusicName || m_songNames.singerName != searchSingerName) continue;
            processNetUrl(data, path, mp3FileName, lyricFileName, imgFileName);
        }
        // ���ӵ������б���
        SongPaths paths = { m_songPaths.jsonPath, m_songPaths.musicPath, m_songPaths.lyricPath, m_songPaths.albumImgPath };
        SongNames names = { m_songNames.singerName, m_songNames.albumName, m_songNames.musicName };
        Song storeSong(names, paths);
        v.push_back(storeSong);
        allAddedSongs.push_back(storeSong);
    }
    return allAddedSongs;
}

// ͨ��url�������������Ӧ�������ļ�����ʣ�ͼƬ��������
QVector<Song> FileManager::getNetMusic(QString music, QString singer, QString url, QVector<Song>& v)
{
    // ������������
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    QVector<Song> addedSongs;
    QNetworkReply* reply = m_manager->get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    // �Զ�ȡ����json�ļ����д���
    if (reply->error() == QNetworkReply::NoError) 
    {
        QByteArray responseData = reply->readAll();
        addedSongs = FileManager::readMusicJson(v, responseData, true, music, singer);
    }
    reply->deleteLater();
    return addedSongs;
}

void FileManager::processNetUrl(QByteArray& data, QString path, QString mp3FileName, QString lyricFileName, QString imgFileName)
{
    saveNetJson(data);
    // �õ�������Դ�ļ�������url
    QString mp3FileUrl = NET_SONG_REPO_NO_SLASH + QUrl::toPercentEncoding(path + mp3FileName);
    mp3FileUrl.replace("%2F", "/");
    QString lyricFileUrl = NET_SONG_REPO_NO_SLASH + (path + lyricFileName).toUtf8().toPercentEncoding();
    lyricFileUrl.replace("%2F", "/");
    QString imgFileUrl = NET_SONG_REPO_NO_SLASH + (path + imgFileName).toUtf8().toPercentEncoding();
    imgFileUrl.replace("%2F", "/");
    // ���ض�Ӧ��������Դ�ļ�
    QStringList urlList;
    urlList << mp3FileUrl << lyricFileUrl << imgFileUrl;
    QStringList nameList;
    nameList << mp3FileName << lyricFileName << imgFileName;
    downloadFiles(urlList, RESOURCE_PATH_NO_SLASH + path, nameList);
}

// �����ֿ߲������ظ����Ķ�Ӧ������Դ�ļ�
void FileManager::downloadFiles(QStringList urlList, QString savePath, QStringList nameList) 
{
    for (int i = 0; i < RESOURCE_NUM; ++i) 
    {
        QNetworkRequest request;
        request.setUrl(QUrl(urlList[i]));
        QNetworkReply* reply = m_manager->get(request);
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if (reply->error() == QNetworkReply::NoError) 
        {
            QByteArray responseData = reply->readAll();
            // ������Ҫ���������ļ���Ŀ¼
            QDir saveDir(savePath);
            if (!saveDir.exists()) {
                saveDir.mkpath(".");
            }

            QString filePath = savePath + nameList[i];
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) 
            {
                file.write(responseData);
                file.close();
                qDebug() << "File saved to:" << filePath;
            }
            else 
            {
                qDebug() << "Failed to open file:" << file.errorString();
            }
        }
        reply->deleteLater();
    }
}

// �����ֿ߲��б���music.json������
void FileManager::saveNetJson(QByteArray& data)
{
    QDir saveDir(RESOURCE_PATH + m_songNames.albumName);
    if (!saveDir.exists()) 
        saveDir.mkpath(".");
    QString filePath = RESOURCE_PATH + m_songNames.albumName + "/music.json";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) 
    {
        file.write(data);
        file.close();
        qDebug() << "File saved to:" << filePath;
    }
    else
    {
        qDebug() << "Failed to open fileg:" << file.errorString();
    }
}

// �����û�ʹ��json�ļ�����Ĺ���
QVector<Song> FileManager::processLocalJsonSongs(QVector<Song>& v)
{
    userChooseJsonPath();
    QByteArray data;
    return readMusicJson(v, data, false, "", "");
}

// �����û�ʹ�õ�����Ƶ�ļ�����Ĺ���
Song FileManager::processSimpleFiles(bool autoImport, QString path)
{
    QString filePath;
    if (!autoImport)
        filePath = userChooseSimpleMusicPath();
    else
        filePath = path;
    if (!filePath.isEmpty())
    {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.baseName();
        SongNames names = { "", "", fileName };
        SongPaths paths = { "", filePath, "", "" };
        Song localSong(names, paths);
        return localSong;
    }
    else
    {
        return Song();
    }
}

// Getter
QString FileManager::getJsonPath() const
{
    return m_songPaths.jsonPath;
}

QString FileManager::getMusicPath() const
{
    return m_songPaths.musicPath;
}

QString FileManager::getLyricPath() const
{
    return m_songPaths.lyricPath;
}

QString FileManager::getImagePath() const
{
    return m_songPaths.albumImgPath;
}

QStringList FileManager::getSearchOptions() const
{
    return m_searchOptions;
}

// Setter
void FileManager::setJsonPath(const QString& path)
{
    m_songPaths.jsonPath = path;
}
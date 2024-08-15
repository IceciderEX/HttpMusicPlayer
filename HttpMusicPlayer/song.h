#ifndef __SONG_H__
#define __SONG_H__

// -------------------------------------------------------
// song.h
// 创建者：Wanganmin
// 创建时间：2023/12/22
// 功能描述：定义了表示每首歌曲的相关信息的Song类
// --------------------------------------------------------

#include <QString>
#include <QTime>
#include <QVector>

#include "common.h"

class Song
{
public:
    Song() = default;
    Song(const SongNames& names, const SongPaths& paths);
    ~Song() = default;
    // getters
    QString getSingerName() const;
    QString getMusicName() const;
    QString getAlbumName() const;
    QString getAlbumImgPath() const;
    QString getMp3Path() const;
    QString getLyricPath() const;
    // setters
    void setNames(const SongNames& names);
    void setPaths(const SongPaths& paths);
    static Song findSong(const QVector<Song>& songs, const SongNames& names);

private:
    SongNames m_names; // 歌曲名字信息
    SongPaths m_paths; // 歌曲路径信息
};

#endif
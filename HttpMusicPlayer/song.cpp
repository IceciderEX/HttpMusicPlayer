#include "song.h"

Song::Song(const SongNames& names, const SongPaths& paths)
    : m_names(names), m_paths(paths)
{
}

// 在QVector存放的songs中通过名字查找歌曲，未找到返回一个空的歌曲对象
Song Song::findSong(const QVector<Song>& songs, const SongNames& names)
{
    for (const Song& song : songs)
    {
        if (song.m_names.musicName == names.musicName &&
            song.m_names.albumName == names.albumName &&
            song.m_names.singerName == names.singerName)
        {
            return song;
        }
    }
    // 返回一个空的歌曲对象表示未找到
    return Song(SongNames{ "", "", "" }, SongPaths{ "", "", "" });
}

// getters
QString Song::getSingerName() const
{
    return m_names.singerName;
}

QString Song::getMusicName() const
{
    return m_names.musicName;
}

QString Song::getAlbumName() const
{
    return m_names.albumName;
}

QString Song::getAlbumImgPath() const 
{
    return m_paths.albumImgPath;
}

QString Song::getMp3Path() const
{
    return m_paths.musicPath;
}

QString Song::getLyricPath() const 
{
    return m_paths.lyricPath;
}

// setters
void Song::setNames(const SongNames& names)
{
    m_names = names;
}

void Song::setPaths(const SongPaths& paths)
{
    m_paths = paths;
}

#ifndef __SONG_H__
#define __SONG_H__

// -------------------------------------------------------
// song.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/22
// ���������������˱�ʾÿ�׸����������Ϣ��Song��
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
    SongNames m_names; // ����������Ϣ
    SongPaths m_paths; // ����·����Ϣ
};

#endif
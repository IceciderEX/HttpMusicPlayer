#include "musicmodel.h"

MusicModel::MusicModel(QObject* parent)
    : QAbstractTableModel(parent) 
{
}

// 返回行数
int MusicModel::rowCount(const QModelIndex& parent) const 
{
    Q_UNUSED(parent)
        return songList.size();
}

// 列数
int MusicModel::columnCount(const QModelIndex& parent) const 
{
    Q_UNUSED(parent)
        return TABLEVIEW_COL; // 歌手、专辑、歌曲名
}

// 设置表项数据
QVariant MusicModel::data(const QModelIndex& index, int role) const 
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= songList.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) 
    {
        const SongNames& song = songList.at(index.row());
        // 根据列的不同返回歌曲信息
        switch (index.column()) 
        {
            case 0: return song.singerName;
            case 1: return song.albumName;
            case 2: return song.musicName;
            default: return QVariant();
        }
    }
    return QVariant();
}

// 设置列头数据
QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) 
    {
        switch (section) 
        {
            case 0: return QStringLiteral("歌手");
            case 1: return QStringLiteral("专辑");
            case 2: return QStringLiteral("歌曲名");
            default: return QVariant();
        }
    }
    return QVariant();
}

// 向列表中添加歌曲
void MusicModel::addToSongList(const QVector<Song>& v)
{
    SongNames song;
    beginResetModel();
    for each (Song s in v)
    {
        SongNames song = { s.getSingerName(), s.getAlbumName(), s.getMusicName() };
        songList.append(song);
    }
    endResetModel();
}

// 得到index行的所有数据
QVariant MusicModel::getLineData(const QModelIndex& index, int role) const 
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= songList.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        const SongNames& song = songList.at(index.row());
        // 将歌曲信息放入 QVariant 列表
        QVariantList rowData;
        rowData << song.singerName << song.albumName << song.musicName;
        return rowData;
    }
    return QVariant();
}
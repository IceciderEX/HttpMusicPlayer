#include "musicmodel.h"

MusicModel::MusicModel(QObject* parent)
    : QAbstractTableModel(parent) 
{
}

// ��������
int MusicModel::rowCount(const QModelIndex& parent) const 
{
    Q_UNUSED(parent)
        return songList.size();
}

// ����
int MusicModel::columnCount(const QModelIndex& parent) const 
{
    Q_UNUSED(parent)
        return TABLEVIEW_COL; // ���֡�ר����������
}

// ���ñ�������
QVariant MusicModel::data(const QModelIndex& index, int role) const 
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= songList.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) 
    {
        const SongNames& song = songList.at(index.row());
        // �����еĲ�ͬ���ظ�����Ϣ
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

// ������ͷ����
QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) 
    {
        switch (section) 
        {
            case 0: return QStringLiteral("����");
            case 1: return QStringLiteral("ר��");
            case 2: return QStringLiteral("������");
            default: return QVariant();
        }
    }
    return QVariant();
}

// ���б�����Ӹ���
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

// �õ�index�е���������
QVariant MusicModel::getLineData(const QModelIndex& index, int role) const 
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= songList.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        const SongNames& song = songList.at(index.row());
        // ��������Ϣ���� QVariant �б�
        QVariantList rowData;
        rowData << song.singerName << song.albumName << song.musicName;
        return rowData;
    }
    return QVariant();
}
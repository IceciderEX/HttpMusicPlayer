#ifndef __MUSICMODEL_H__
#define __MUSICMODEL_H__

// -------------------------------------------------------
// musicmodel.h
// 创建者：Wanganmin
// 创建时间：2023/12/22
// 功能描述：定义了QTabelView（歌曲列表）的数据model
// --------------------------------------------------------

#include <QAbstractTableModel>
#include <QString>
#include <QObject>

#include "song.h"
#include "common.h"

class MusicModel : public QAbstractTableModel 
{
    Q_OBJECT

public:
    explicit MusicModel(QObject* parent = nullptr);
    // 重新实现的父类方法
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant getLineData(const QModelIndex& index, int role) const;
    void addToSongList(const QVector<Song>& v);

private:
    QVector<SongNames> songList;
};

#endif

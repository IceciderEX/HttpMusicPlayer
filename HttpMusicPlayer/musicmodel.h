#ifndef __MUSICMODEL_H__
#define __MUSICMODEL_H__

// -------------------------------------------------------
// musicmodel.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/22
// ����������������QTabelView�������б�������model
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
    // ����ʵ�ֵĸ��෽��
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

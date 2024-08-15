#ifndef __MENUBARHANDLER_H__
#define __MENUBARHANDLER_H__

// -------------------------------------------------------
// menubarhandler.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/26
// ����������ר�����ڴ���Menubar�����˵���ʾ���ܵ���
// --------------------------------------------------------

#include <QObject>
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QMediaPlaylist>

#include "ui_httpmusicplayer.h"

class MenuBarHandler : public QObject
{
    Q_OBJECT
public:
    explicit MenuBarHandler(QObject* parent = nullptr);

public slots:
    void onActSeqClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList);
    void onActRandClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList);
    void onActLoopClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList);
};

#endif
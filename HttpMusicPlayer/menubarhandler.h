#ifndef __MENUBARHANDLER_H__
#define __MENUBARHANDLER_H__

// -------------------------------------------------------
// menubarhandler.h
// 创建者：Wanganmin
// 创建时间：2023/12/26
// 功能描述：专门用于处理Menubar下拉菜单显示功能的类
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
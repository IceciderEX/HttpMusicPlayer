#include "menubarhandler.h"

MenuBarHandler::MenuBarHandler(QObject* parent) : QObject(parent)
{
}

// 播放模式设置为顺序模式
void MenuBarHandler::onActSeqClicked(Ui::HttpMusicPlayerClass ui,QMediaPlaylist* playList)
{
    qDebug() << "set to Sequential mode";
    playList->setPlaybackMode(QMediaPlaylist::Sequential);
    QIcon playIcon(":/HttpMusicPlayer/res/seqplay.png");
    ui.m_playModeBtn->setIcon(playIcon);
}

// 播放模式设置为随机播放
void MenuBarHandler::onActRandClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList)
{
    qDebug() << "set to Random mode";
    playList->setPlaybackMode(QMediaPlaylist::Random);
    QIcon playIcon(":/HttpMusicPlayer/res/randomplay.png");
    ui.m_playModeBtn->setIcon(playIcon);
}

// 播放模式设置为单曲循环
void MenuBarHandler::onActLoopClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList)
{
    qDebug() << "set to Loop mode";
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    QIcon playIcon(":/HttpMusicPlayer/res/loopmode.png");
    ui.m_playModeBtn->setIcon(playIcon);
}
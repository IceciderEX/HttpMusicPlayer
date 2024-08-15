#include "menubarhandler.h"

MenuBarHandler::MenuBarHandler(QObject* parent) : QObject(parent)
{
}

// ����ģʽ����Ϊ˳��ģʽ
void MenuBarHandler::onActSeqClicked(Ui::HttpMusicPlayerClass ui,QMediaPlaylist* playList)
{
    qDebug() << "set to Sequential mode";
    playList->setPlaybackMode(QMediaPlaylist::Sequential);
    QIcon playIcon(":/HttpMusicPlayer/res/seqplay.png");
    ui.m_playModeBtn->setIcon(playIcon);
}

// ����ģʽ����Ϊ�������
void MenuBarHandler::onActRandClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList)
{
    qDebug() << "set to Random mode";
    playList->setPlaybackMode(QMediaPlaylist::Random);
    QIcon playIcon(":/HttpMusicPlayer/res/randomplay.png");
    ui.m_playModeBtn->setIcon(playIcon);
}

// ����ģʽ����Ϊ����ѭ��
void MenuBarHandler::onActLoopClicked(Ui::HttpMusicPlayerClass ui, QMediaPlaylist* playList)
{
    qDebug() << "set to Loop mode";
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    QIcon playIcon(":/HttpMusicPlayer/res/loopmode.png");
    ui.m_playModeBtn->setIcon(playIcon);
}
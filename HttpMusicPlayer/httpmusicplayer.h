#ifndef __HTTP_MUSICPLAYER_H__
#define __HTTP_MUSICPLAYER_H__

// -------------------------------------------------------
// httpmusicplayer.h
// 创建者：Wanganmin
// 创建时间：2023/12/22
// 功能描述：主窗口类，用于显示播放器的界面
// --------------------------------------------------------

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTransform>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRotation>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QAction>
#include <QCompleter>

#include "ui_httpmusicplayer.h"
#include "musicmodel.h"
#include "imagehandler.h"
#include "song.h"
#include "common.h"
#include "lyricmanager.h"
#include "filemanager.h"
#include "trayicon.h"
#include "messageboxhandler.h"
#include "menubarhandler.h"
#include "utils.h"

class HttpMusicPlayer : public QMainWindow
{
    Q_OBJECT

public:
    HttpMusicPlayer(QWidget *parent = nullptr);
    ~HttpMusicPlayer() = default;

    void closeEvent(QCloseEvent* event) override;
    void init();
    void connectSignals();
    void searchMusic();
    void displayAlbumImg(const QString filePath);
    void initLocalSongs();
    void playSong(int index);

public slots:
    void onStateChanged(QMediaPlayer::State state);
    void onPlayBtnClicked();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void updateLabels(qint64 currentPosition, qint64 totalTime);
    void onVolumeBarChanged(int volume);
    void onLastSongBtnChanged();
    void onNextSongBtnChanged();
    void onPlayModeBtnClicked();
    void onAddLocalJsonSongBtnClicked();
    void onAddLocalMusicFileBtnClicked();

private:
    Ui::HttpMusicPlayerClass ui; 
    LyricManager* m_lyricManager;  // 歌词管理器
    FileManager* m_fileManager;  // 文件管理器
    MenuBarHandler* m_menuBarHandler;  // 菜单栏处理器
    MusicModel* m_localMusicModel;  // 本地音乐模型

    QCompleter* m_completer;  // 用于实现搜索框补全的自动完成器
    QVector<Song> m_songs;  // 存放所有歌曲的信息
    QMediaPlayer* m_player;  // 播放器
    QMediaPlaylist* m_playList;  // 播放列表
    QTimer timer;  // 专辑封面的旋转定时器
    QGraphicsPixmapItem* m_albumImgMapItem;  // 专辑封面图像项
    qreal rotationAngle;  // 专辑封面的旋转角度
};

#endif
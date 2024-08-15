#ifndef __HTTP_MUSICPLAYER_H__
#define __HTTP_MUSICPLAYER_H__

// -------------------------------------------------------
// httpmusicplayer.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/22
// �����������������࣬������ʾ�������Ľ���
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
    LyricManager* m_lyricManager;  // ��ʹ�����
    FileManager* m_fileManager;  // �ļ�������
    MenuBarHandler* m_menuBarHandler;  // �˵���������
    MusicModel* m_localMusicModel;  // ��������ģ��

    QCompleter* m_completer;  // ����ʵ��������ȫ���Զ������
    QVector<Song> m_songs;  // ������и�������Ϣ
    QMediaPlayer* m_player;  // ������
    QMediaPlaylist* m_playList;  // �����б�
    QTimer timer;  // ר���������ת��ʱ��
    QGraphicsPixmapItem* m_albumImgMapItem;  // ר������ͼ����
    qreal rotationAngle;  // ר���������ת�Ƕ�
};

#endif
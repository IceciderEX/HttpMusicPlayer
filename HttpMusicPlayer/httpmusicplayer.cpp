#include "httpmusicplayer.h"

HttpMusicPlayer::HttpMusicPlayer(QWidget* parent)
    : QMainWindow(parent)
{
    init();
    connectSignals();
}

// ��س�ʼ������
void HttpMusicPlayer::init()
{
    ui.setupUi(this);
    m_player = new QMediaPlayer();
    m_playList = new QMediaPlaylist();
    m_lyricManager = new LyricManager();
    m_fileManager = new FileManager();
    m_localMusicModel = new MusicModel();
    initLocalSongs();
    displayAlbumImg("./res/default_img.jpg");
    ui.m_songList->resizeColumnsToContents();
    ui.m_songList->verticalHeader()->setHidden(true);
    ui.m_songList->setColumnWidth(0, 150);
    ui.m_songList->setColumnWidth(1, 150);
    m_fileManager->fetchGiteeRepoFolders();
    m_completer = new QCompleter(m_fileManager->getSearchOptions());
    ui.m_searchBar->setCompleter(m_completer);
}

// ���ø���connect����
void HttpMusicPlayer::connectSignals()
{
    // ������ť��connect����
    (void)connect(ui.m_searchBtn, &QPushButton::clicked, this, &HttpMusicPlayer::searchMusic);
    (void)connect(ui.m_playBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onPlayBtnClicked);
    (void)connect(ui.m_volumeBar, &QSlider::valueChanged, this, &HttpMusicPlayer::onVolumeBarChanged);
    (void)connect(ui.m_lastSongBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onLastSongBtnChanged);
    (void)connect(ui.m_nextSongBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onNextSongBtnChanged);
    (void)connect(ui.m_playModeBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onPlayModeBtnClicked);
    (void)connect(ui.m_addLocalSongBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onAddLocalJsonSongBtnClicked);
    (void)connect(ui.m_addSimpleFileBtn, &QPushButton::clicked, this, &HttpMusicPlayer::onAddLocalMusicFileBtnClicked);

    // ����connect����
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onStateChanged(QMediaPlayer::State)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(ui.m_manual, &QAction::triggered, this, &MessageBoxHandler::onActionManualClicked);
    connect(ui.m_about, &QAction::triggered, this, &MessageBoxHandler::onActionAboutClicked);

    connect(ui.m_slideBar, &QSlider::sliderMoved, [=](int position)
        {
            ui.m_progressText->setText(Utils::StringUtil::formatTime(position));  // ���µ�ǰ����ʱ��
        });
    connect(ui.m_slideBar, &QSlider::sliderReleased, [=]()
        {
            m_player->setPosition(ui.m_slideBar->value()); // ���¸�������λ��
        });
    connect(m_playList, &QMediaPlaylist::currentMediaChanged, [&](const QMediaContent& media)
        {
            playSong(m_playList->currentIndex());
        });
    // ������תר�������߼�
    connect(&timer, &QTimer::timeout, [&]() {
        rotationAngle += 0.02; // ÿ��������ת�Ƕ�
        m_albumImgMapItem->setRotation(rotationAngle);
        });
    // ʵ�ֵ������еĸ�������л�����������Ĺ���
    connect(ui.m_songList, &QTableView::doubleClicked, [=](const QModelIndex& index) {
        if (index.isValid()) {
            playSong(index.row());
        }
        });
    connect(ui.m_volumeIcon, &QPushButton::clicked, [=]() {
        ui.m_volumeBar->setValue(0);
        });
}

// �����ظ���������json�뵥����Ƶ�ļ�����ʼ������������
void HttpMusicPlayer::initLocalSongs()
{
    // ��ȡ��Ҫ���صı���json����
    QString filePath = DATA_JSON_PATH;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString folderPath = RESOURCE_PATH + line;
            m_fileManager->setJsonPath(folderPath + "/music.json");
            QByteArray data;
            m_fileManager->readMusicJson(m_songs, data, false, "", "");
        }
        file.close();
    }
    m_localMusicModel->addToSongList(m_songs);
    for each (Song s in m_songs)
        m_playList->addMedia(QUrl::fromLocalFile(s.getMp3Path()));
    // ��ȡ��Ҫ���صı��ص�����Ƶ����
    QDir folderDir(DATA_FILE_PATH);
    QStringList nameFilters;
    nameFilters << "*.mp3" << "*.flac" << "*.wav" << "*.aac";
    folderDir.setNameFilters(nameFilters);
    QStringList files = folderDir.entryList(QDir::Files);
    QVector<Song> songList;
    for (const QString& file : files)
    {
        m_playList->addMedia(QUrl::fromLocalFile(DATA_FILE_PATH + file));
        Song addedMusic = m_fileManager->processSimpleFiles(true, DATA_FILE_PATH + file);
        songList.push_back(addedMusic);
        m_songs.push_back(addedMusic);
    }
    m_localMusicModel->addToSongList(songList);
    ui.m_songList->reset();
    m_player->setPlaylist(m_playList);
    // ��ʼ�������б���ʾ������
    ui.m_songList->setModel(m_localMusicModel);
}

// �������Ϊindex������
void HttpMusicPlayer::playSong(int index)
{
    QAbstractItemModel* model = ui.m_songList->model();
    // ��ȡѡ���е�����
    QVariantList rowData;
    for (int i = 0; i < TABLEVIEW_COL; ++i) 
    {
        QVariant data = model->data(model->index(index, i));
        rowData << data;
    }
    SongNames names{ rowData.at(0).toString(), rowData.at(1).toString(), rowData.at(2).toString() };
    Song foundSong = Song::findSong(m_songs, names);
    // ���������������Դ�ļ��ĸ����뵥������Ƶ�ļ�
    if (foundSong.getMp3Path() != "")
    {
        if (foundSong.getSingerName() == "")
        {
            displayAlbumImg("./res/default_img.jpg");
            m_lyricManager->clearLyric();
            m_lyricManager->setDefaultLyrics();
            ui.m_beforeLyric->setText("");
            ui.m_curLyric->setText(QStringLiteral("������û���ṩ����ļ�"));
            ui.m_nextLyric->setText("");
            ui.m_songNameText->setText(names.musicName);
            ui.m_singerNameText->setText(names.singerName);
        }
        else
        {
            displayAlbumImg(foundSong.getAlbumImgPath());
            m_lyricManager->clearLyric();
            m_lyricManager->setfilePath(foundSong.getLyricPath());
            m_lyricManager->readLyricsFile(foundSong.getLyricPath());
            ui.m_beforeLyric->setText(m_lyricManager->updateLyrics(0)[0]);
            ui.m_curLyric->setText(m_lyricManager->updateLyrics(0)[1]);
            ui.m_nextLyric->setText(m_lyricManager->updateLyrics(0)[2]);
        }
        ui.m_playBtn->setEnabled(true);
        ui.m_lastSongBtn->setEnabled(true);
        ui.m_nextSongBtn->setEnabled(true);
        ui.m_slideBar->setEnabled(true);
        ui.m_songNameText->setText(names.musicName);
        ui.m_singerNameText->setText(names.singerName);
        if (m_playList->currentIndex() != index)
            m_player->playlist()->setCurrentIndex(index);
        m_player->play();
    }
}

// ʵ�����߸��������������ع���
void HttpMusicPlayer::searchMusic()
{
    QString key = ui.m_searchBar->text().trimmed();
    if (key.isEmpty()) return;
    // �û��������music.json�ļ���url
    QString music = key.split("-")[0];
    QString singer = key.split("-")[1];
    if (music.isEmpty() || singer.isEmpty()) return;

    QString url = NET_SONG_REPO + music.toUtf8().toPercentEncoding() + "/music.json";
    QVector<Song> addedMusic = m_fileManager->getNetMusic(music, singer, url, m_songs);
    // ��ӵ������б���
    for each (Song eachSong in addedMusic)
        m_playList->addMedia(QUrl::fromLocalFile(eachSong.getMp3Path()));
    m_localMusicModel->addToSongList(addedMusic);
    ui.m_songList->reset();
    bool searchRes = addedMusic.size() != 0;
    MessageBoxHandler::showSearchResult(searchRes);
}

// ʵ��ר��ͼƬ����ʾ
void HttpMusicPlayer::displayAlbumImg(const QString filePath)
{
    QPixmap roundedPixmap = ImageHandler::loadImage(ui.m_songPic->size(), filePath);
    // ��ͼƬ��ʾ�ڶ�Ӧ������
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, ALNUM_IMG_SIZE, ALNUM_IMG_SIZE); // ���ó�����С
    m_albumImgMapItem = new QGraphicsPixmapItem(roundedPixmap);
    m_albumImgMapItem->setTransformOriginPoint(roundedPixmap.width() / 2, roundedPixmap.height() / 2); // ������ת���ĵ�
    scene->addItem(m_albumImgMapItem);
    ui.m_songPic->setScene(scene);
    ui.m_songPic->setRenderHint(QPainter::Antialiasing, true);
    ui.m_songPic->show();
}

// ���µ�ǰʱ�����ʱ������ʾ
void HttpMusicPlayer::updateLabels(qint64 currentPosition, qint64 totalTime)
{
    QString currentTimeStr = Utils::StringUtil::formatTime(currentPosition);
    QString totalTimeStr = Utils::StringUtil::formatTime(totalTime);
    // �������ֽ��������ı�����
    ui.m_progressText->setText(currentTimeStr + "/" + totalTimeStr);
}

// ������״̬�仯�Ĳۺ���
void HttpMusicPlayer::onStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        QIcon playIcon(":/HttpMusicPlayer/res/pause.png");
        ui.m_playBtn->setIcon(playIcon);
        timer.start(1);
    }
    else if (state == QMediaPlayer::StoppedState)
    {
        // ��⵽ֹͣ״̬������Ϊ˳�򲥷ţ��л�����һ�׸���
        rotationAngle = 0;
        if (m_playList->playbackMode() == QMediaPlaylist::Sequential)
            m_playList->setCurrentIndex(0);
    }
    else
    {
        QIcon playIcon(":/HttpMusicPlayer/res/continue.png");
        ui.m_playBtn->setIcon(playIcon);
        timer.stop();
    }
}

// ����/��ͣ��ť�Ĳۺ���
void HttpMusicPlayer::onPlayBtnClicked()
{
    if (m_player->state() == QMediaPlayer::PlayingState)
    {
        m_player->pause();
    }
    else
    {
        if (!m_player->playlist()->isEmpty())
            m_player->play();
    }
}

// ����ģʽ��ť�Ĳۺ��������ò���ģʽ
void HttpMusicPlayer::onPlayModeBtnClicked()
{
    QMenu* menu = new QMenu(this);
    QAction* actSeq = new QAction(QStringLiteral("˳�򲥷�"), this);
    QAction* actRand = new QAction(QStringLiteral("�������"), this);
    QAction* actLoop = new QAction(QStringLiteral("����ѭ��"), this);

    connect(actSeq, &QAction::triggered, [=]() {
        m_menuBarHandler->onActSeqClicked(ui, m_playList);
        });
    connect(actRand, &QAction::triggered, [=]() {
        m_menuBarHandler->onActRandClicked(ui, m_playList);
        });
    connect(actLoop, &QAction::triggered, [=]() {
        m_menuBarHandler->onActLoopClicked(ui, m_playList);
        });
    menu->addAction(actSeq);
    menu->addAction(actRand);
    menu->addAction(actLoop);
    ui.m_playModeBtn->setMenu(menu);
    menu->exec(QPoint(QCursor::pos().x(), QCursor::pos().y()));
}

// ��ǰ�����ļ�ʱ���仯�����½���������ʾ
void HttpMusicPlayer::onDurationChanged(qint64 duration)
{
    ui.m_slideBar->setMaximum(duration);
    qint64 currentPosition = m_player->position();
    qint64 totalTime = m_player->duration();
    updateLabels(currentPosition, totalTime);
}

// ��ǰ���ֲ���λ�ñ仯�����½���������ʾ���ʵ���ʾ
void HttpMusicPlayer::onPositionChanged(qint64 position)
{
    if (ui.m_slideBar->isSliderDown()) return;
    // ��ȡ��ʱ��
    qint64 duration = m_player->duration();

    ui.m_slideBar->setRange(0, duration);
    ui.m_slideBar->setValue(position);
    qint64 currentPosition = m_player->position();
    qint64 totalTime = m_player->duration();
    updateLabels(currentPosition, totalTime);
    ui.m_beforeLyric->setText(m_lyricManager->updateLyrics(position)[0]);
    ui.m_curLyric->setText(m_lyricManager->updateLyrics(position)[1]);
    ui.m_nextLyric->setText(m_lyricManager->updateLyrics(position)[2]);
}

// �����һ�׸�����ť�Ĵ����߼�
void HttpMusicPlayer::onLastSongBtnChanged()
{
    if (!(m_playList->playbackMode() == QMediaPlaylist::Loop))
    {
        m_playList->previous();
        playSong(m_playList->currentIndex());
    }
    // ѭ�����ŵ����⴦��
    else
    {
        m_player->setPosition(0);
        rotationAngle = 0;
        m_player->play();
    }
}

// �����һ�׸�����ť�Ĵ����߼�
void HttpMusicPlayer::onNextSongBtnChanged()
{
    if (!(m_playList->playbackMode() == QMediaPlaylist::Loop))
    {
        m_playList->next();
        playSong(m_playList->currentIndex());
    }
    else 
    {
        m_player->setPosition(0);
        rotationAngle = 0;
        m_player->play();
    }
}

// ���뱾��json�ļ��Ĵ����߼�
void HttpMusicPlayer::onAddLocalJsonSongBtnClicked()
{
    QVector<Song> addedMusic = m_fileManager->processLocalJsonSongs(m_songs);
    for each (Song eachSong in addedMusic)
        m_playList->addMedia(QUrl::fromLocalFile(eachSong.getMp3Path()));
    m_localMusicModel->addToSongList(addedMusic);
    ui.m_songList->reset();
    MessageBoxHandler::showImportResult(addedMusic.size());
}

// ���뱾�ص�����Ƶ�ļ��Ĵ����߼�
void HttpMusicPlayer::onAddLocalMusicFileBtnClicked()
{
    Song addedMusic = m_fileManager->processSimpleFiles(false, "");
    if (!addedMusic.getMp3Path().isEmpty())
    {
        m_playList->addMedia(QUrl::fromLocalFile(addedMusic.getMp3Path()));
        QVector<Song> songList;
        songList.push_back(addedMusic);
        m_localMusicModel->addToSongList(songList);
        m_songs.push_back(addedMusic);
        ui.m_songList->reset();
        MessageBoxHandler::showImportResult(1);
    }
    else
    {
        MessageBoxHandler::showImportResult(0);
    }
}

// �����������϶�ʱ�����Ķ�Ӧ�ı�
void HttpMusicPlayer::onVolumeBarChanged(int volume)
{
    if (volume == 0)
    {
        QIcon icon(":/HttpMusicPlayer/res/mute.png");
        ui.m_volumeIcon->setIcon(icon);
    }
    else
    {
        QIcon icon(":/HttpMusicPlayer/res/volume.png");
        ui.m_volumeIcon->setIcon(icon);
    }
    qreal volumeLevel = volume / 100.0;
    m_player->setVolume(volumeLevel * 100);
    QString volumeText = QString("%1%").arg(volume);
    ui.m_volumeVal->setText(volumeText);
}

// ��д���ڹر��¼�closeEvent��������С�������̵Ĺ���ʵ��
void HttpMusicPlayer::closeEvent(QCloseEvent* event)
{
    // ����һ��ѡ��ť���Ƿ���С��������������
    QMessageBox::StandardButton button = QMessageBox::question(this, QStringLiteral("��ʾ"),
        QStringLiteral("�Ƿ���С����ϵͳ���̣�"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (button == QMessageBox::Yes)
    {
        TrayIcon::Instance()->setMainWidget(this);
        event->ignore();
        this->hide();
        TrayIcon::Instance()->setVisible(true);
        TrayIcon::Instance()->showMessage(QStringLiteral("�Զ�����С������"),
            QStringLiteral("����С��"));
    }
    // ֱ�ӹرճ���
    else
    {
        event->accept();
    }
}
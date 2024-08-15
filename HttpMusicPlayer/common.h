#ifndef __COMMON_H__
#define __COMMON_H__

// -------------------------------------------------------
// common.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/22
// ��������������һЩ�������������ݽṹ�Ķ���
// --------------------------------------------------------

// �б���и���
#define TABLEVIEW_COL 3
#define RESOURCE_NUM 3
// ������Դ�ļ��е�λ��
#define RESOURCE_PATH "./songs/"
#define RESOURCE_PATH_NO_SLASH "./songs"
// ������Դ���Ĵ洢λ��
#define DATA_JSON_PATH "./songs/importjson.txt"
#define DATA_FILE_PATH "./songs/"
// ����ֿ�ĵ�ַ
#define NET_SONG_REPO "https://gitee.com/MarkYangUp/music/raw/master/"
#define NET_SONG_REPO_NO_SLASH "https://gitee.com/MarkYangUp/music/raw/master"
#define NET_SONG_FOLDER "https://gitee.com/MarkYangUp/music/tree/master/"
// ͼƬ����ʾ��С
#define ALNUM_IMG_SIZE 450

// ���ÿ�׸���·���Ľṹ��
struct SongPaths 
{
    QString jsonPath;
    QString musicPath;
    QString lyricPath;
    QString albumImgPath;
};

// ���ÿ�׸���������Ϣ�Ľṹ��
struct SongNames 
{
    QString singerName;
    QString albumName;
    QString musicName;
};

#endif
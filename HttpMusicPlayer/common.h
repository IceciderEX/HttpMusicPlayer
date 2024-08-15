#ifndef __COMMON_H__
#define __COMMON_H__

// -------------------------------------------------------
// common.h
// 创建者：Wanganmin
// 创建时间：2023/12/22
// 功能描述：用于一些基本变量与数据结构的定义
// --------------------------------------------------------

// 列表的列个数
#define TABLEVIEW_COL 3
#define RESOURCE_NUM 3
// 本地资源文件夹的位置
#define RESOURCE_PATH "./songs/"
#define RESOURCE_PATH_NO_SLASH "./songs"
// 本地资源名的存储位置
#define DATA_JSON_PATH "./songs/importjson.txt"
#define DATA_FILE_PATH "./songs/"
// 网络仓库的地址
#define NET_SONG_REPO "https://gitee.com/MarkYangUp/music/raw/master/"
#define NET_SONG_REPO_NO_SLASH "https://gitee.com/MarkYangUp/music/raw/master"
#define NET_SONG_FOLDER "https://gitee.com/MarkYangUp/music/tree/master/"
// 图片的显示大小
#define ALNUM_IMG_SIZE 450

// 存放每首歌曲路径的结构体
struct SongPaths 
{
    QString jsonPath;
    QString musicPath;
    QString lyricPath;
    QString albumImgPath;
};

// 存放每首歌曲名字信息的结构体
struct SongNames 
{
    QString singerName;
    QString albumName;
    QString musicName;
};

#endif
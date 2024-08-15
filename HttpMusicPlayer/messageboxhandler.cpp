#include "messageboxhandler.h"

// About消息框的显示
void MessageBoxHandler::onActionAboutClicked()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About HttpMusicPlayer");
    QString aboutText = QStringLiteral(
        "HttpMusicPlayer\n\n"
        "Version: 1.0\n"
        "Description: 一个HTTP音乐播放器，能够实现mp3，wav、flac、aac等等主流音频格式音乐的播放，实现了播放器的基本功能。\n"
        "支持从对应的Gitee仓库中在线下载歌曲并播放\n");
    aboutBox.setText(aboutText);
    QPixmap iconPixmap(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIconPixmap(iconPixmap);
    QIcon icon(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.addButton(QMessageBox::Ok);
    aboutBox.exec();
}

// 帮助消息框的显示
void MessageBoxHandler::onActionManualClicked()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("HttpMusicPlayer's manual");
    QString aboutText = QStringLiteral(
        "1.在线歌曲的下载以提供的Gitee仓库为数据来源\n"
        "   以提供的Gitee仓库为数据来源，可在搜索框中进行搜索，如果歌曲存在会获得相应提示，请点击对应的提示补全后再进行搜索 eg.孤勇者-陈奕迅\n"
        "2.使用方法\n"
        "   ①双击歌曲列表中的歌曲项即可播放对应的歌曲，其他播放器功能与其他播放器一致，不再赘述。\n"
        "   ②有关歌曲的运行中导入：右上角存在两个导入按钮，分别可以导入json文件对应的歌曲资源文件（包括歌词，图片与音频）和导入一个单独的音频文件。\n"
        "   ③有关歌曲的自动导入：目前我选择在./songs文件夹中的importjson.txt文件中配置用于自动导入json文件对应的歌曲。\n"
        "需要注意json文件所在文件夹需要在./songs文件夹的下级目录中，并且文件夹名即为importjson.txt中的行内容；单独的音频文件直接放在./songs文件夹即可，"
        "播放器会自动导入mp3，flac，wav，aac格式的音频文件。\n"
        "3.其他说明\n"
        "  有关资源存放的文件夹配置信息存放在common.h头文件中，可根据需要修改。\n"
        );
    aboutBox.setText(aboutText);
    QPixmap iconPixmap(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIconPixmap(iconPixmap);
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.addButton(QMessageBox::Ok);
    aboutBox.exec();
}

// 显示搜索结果
void MessageBoxHandler::showSearchResult(bool result)
{
    QMessageBox infoBox;
    infoBox.resize(100, 50);
    infoBox.setWindowTitle(QStringLiteral("在线歌曲获取结果"));
    infoBox.setIcon(QMessageBox::Information);
    if (!result)
        infoBox.setText(QStringLiteral("在线歌曲获取失败，可能在线仓库中没有该歌曲！"));
    else
        infoBox.setText(QStringLiteral("在线歌曲下载完成！"));
    infoBox.addButton(QMessageBox::Ok);
    infoBox.exec();
}

// 显示歌曲本地导入结果
void MessageBoxHandler::showImportResult(int addedSize)
{
    QMessageBox infoBox;
    infoBox.resize(100, 50);
    infoBox.setWindowTitle(QStringLiteral("本地歌曲导入结果"));
    infoBox.setIcon(QMessageBox::Information);
    QString message = QStringLiteral("导入文件对应的歌曲完成，成功添加个数：%1").arg(addedSize);
    infoBox.setText(message);
    infoBox.addButton(QMessageBox::Ok);
    infoBox.exec();
}
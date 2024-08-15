#ifndef __MESSAGEBOXHANDLER_H__
#define __MESSAGEBOXHANDLER_H__

// -------------------------------------------------------
// messageboxhandler.h
// 创建者：Wanganmin
// 创建时间：2023/12/26
// 功能描述：专门用于处理MessageBox显示功能的类
// --------------------------------------------------------

#include <QMessageBox>
#include <QIcon>

class MessageBoxHandler
{
public:
    static void onActionManualClicked();
    static void onActionAboutClicked();
    static void showSearchResult(bool result);
    static void showImportResult(int addedSize);

private:
    MessageBoxHandler();
};

#endif
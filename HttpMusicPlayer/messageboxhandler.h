#ifndef __MESSAGEBOXHANDLER_H__
#define __MESSAGEBOXHANDLER_H__

// -------------------------------------------------------
// messageboxhandler.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/26
// ����������ר�����ڴ���MessageBox��ʾ���ܵ���
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
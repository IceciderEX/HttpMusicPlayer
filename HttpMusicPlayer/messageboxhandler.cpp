#include "messageboxhandler.h"

// About��Ϣ�����ʾ
void MessageBoxHandler::onActionAboutClicked()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About HttpMusicPlayer");
    QString aboutText = QStringLiteral(
        "HttpMusicPlayer\n\n"
        "Version: 1.0\n"
        "Description: һ��HTTP���ֲ��������ܹ�ʵ��mp3��wav��flac��aac�ȵ�������Ƶ��ʽ���ֵĲ��ţ�ʵ���˲������Ļ������ܡ�\n"
        "֧�ִӶ�Ӧ��Gitee�ֿ����������ظ���������\n");
    aboutBox.setText(aboutText);
    QPixmap iconPixmap(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIconPixmap(iconPixmap);
    QIcon icon(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.addButton(QMessageBox::Ok);
    aboutBox.exec();
}

// ������Ϣ�����ʾ
void MessageBoxHandler::onActionManualClicked()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("HttpMusicPlayer's manual");
    QString aboutText = QStringLiteral(
        "1.���߸������������ṩ��Gitee�ֿ�Ϊ������Դ\n"
        "   ���ṩ��Gitee�ֿ�Ϊ������Դ�������������н�������������������ڻ�����Ӧ��ʾ��������Ӧ����ʾ��ȫ���ٽ������� eg.������-����Ѹ\n"
        "2.ʹ�÷���\n"
        "   ��˫�������б��еĸ�����ɲ��Ŷ�Ӧ�ĸ�������������������������������һ�£�����׸����\n"
        "   ���йظ����������е��룺���ϽǴ����������밴ť���ֱ���Ե���json�ļ���Ӧ�ĸ�����Դ�ļ���������ʣ�ͼƬ����Ƶ���͵���һ����������Ƶ�ļ���\n"
        "   ���йظ������Զ����룺Ŀǰ��ѡ����./songs�ļ����е�importjson.txt�ļ������������Զ�����json�ļ���Ӧ�ĸ�����\n"
        "��Ҫע��json�ļ������ļ�����Ҫ��./songs�ļ��е��¼�Ŀ¼�У������ļ�������Ϊimportjson.txt�е������ݣ���������Ƶ�ļ�ֱ�ӷ���./songs�ļ��м��ɣ�"
        "���������Զ�����mp3��flac��wav��aac��ʽ����Ƶ�ļ���\n"
        "3.����˵��\n"
        "  �й���Դ��ŵ��ļ���������Ϣ�����common.hͷ�ļ��У��ɸ�����Ҫ�޸ġ�\n"
        );
    aboutBox.setText(aboutText);
    QPixmap iconPixmap(":/HttpMusicPlayer/res/musicicon.png");
    aboutBox.setIconPixmap(iconPixmap);
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.addButton(QMessageBox::Ok);
    aboutBox.exec();
}

// ��ʾ�������
void MessageBoxHandler::showSearchResult(bool result)
{
    QMessageBox infoBox;
    infoBox.resize(100, 50);
    infoBox.setWindowTitle(QStringLiteral("���߸�����ȡ���"));
    infoBox.setIcon(QMessageBox::Information);
    if (!result)
        infoBox.setText(QStringLiteral("���߸�����ȡʧ�ܣ��������ֿ߲���û�иø�����"));
    else
        infoBox.setText(QStringLiteral("���߸���������ɣ�"));
    infoBox.addButton(QMessageBox::Ok);
    infoBox.exec();
}

// ��ʾ�������ص�����
void MessageBoxHandler::showImportResult(int addedSize)
{
    QMessageBox infoBox;
    infoBox.resize(100, 50);
    infoBox.setWindowTitle(QStringLiteral("���ظ���������"));
    infoBox.setIcon(QMessageBox::Information);
    QString message = QStringLiteral("�����ļ���Ӧ�ĸ�����ɣ��ɹ���Ӹ�����%1").arg(addedSize);
    infoBox.setText(message);
    infoBox.addButton(QMessageBox::Ok);
    infoBox.exec();
}
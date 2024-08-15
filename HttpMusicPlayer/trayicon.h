#ifndef __TRAYICON_H__
#define __TRAYICON_H__

// -------------------------------------------------------
// trayicon.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/24
// ��������������ģʽʵ�ֵ�һ����С���������ʵ��
// --------------------------------------------------------

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QApplication>

class TrayIcon : public QObject
{
    Q_OBJECT

public:
    static TrayIcon* Instance();
    void setMainWidget(QWidget* mainWidget);
    void setVisible(bool visible);
    void showMessage(const QString& title, const QString& msg);
    ~TrayIcon();

private:
    explicit TrayIcon(QObject* parent = nullptr);
    QSystemTrayIcon* trayIcon;
    QWidget* mainWidget;
    QMenu* menu;
    bool exitDirect; // �Ƿ�ֱ���˳�
    static QScopedPointer<TrayIcon> self; // ����

public slots:
    void showMainWidget();
    void closeAll();

signals:
    void trayIconExit();
};

#endif

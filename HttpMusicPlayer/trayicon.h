#ifndef __TRAYICON_H__
#define __TRAYICON_H__

// -------------------------------------------------------
// trayicon.h
// 创建者：Wanganmin
// 创建时间：2023/12/24
// 功能描述：单例模式实现的一个最小化托盘类的实现
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
    bool exitDirect; // 是否直接退出
    static QScopedPointer<TrayIcon> self; // 单例

public slots:
    void showMainWidget();
    void closeAll();

signals:
    void trayIconExit();
};

#endif

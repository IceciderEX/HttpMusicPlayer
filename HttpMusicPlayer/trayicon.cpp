#include "trayicon.h"
#include <QMutexLocker>

QScopedPointer<TrayIcon> TrayIcon::self;

TrayIcon::TrayIcon(QObject* parent)
    : QObject(parent), trayIcon(new QSystemTrayIcon(this)), mainWidget(nullptr), menu(new QMenu()), exitDirect(false)
{
    QIcon icon(":/HttpMusicPlayer/res/musicicon.png");
    trayIcon->setIcon(icon);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::showMainWidget);
    trayIcon->show();
}

TrayIcon::~TrayIcon()
{
    trayIcon->deleteLater();
}

TrayIcon* TrayIcon::Instance()
{
    if (self.isNull())
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull())
        {
            self.reset(new TrayIcon);
        }
    }
    return self.data();
}

void TrayIcon::setMainWidget(QWidget* mainWidget)
{
    this->mainWidget = mainWidget;
    // �����̼��ϲ˵�����
    menu->addAction(QStringLiteral("������"), this, &TrayIcon::showMainWidget);
    if (exitDirect)
        menu->addAction(QStringLiteral("�˳�"), this, &TrayIcon::closeAll);
    else
        menu->addAction(QStringLiteral("�˳�"), this, &TrayIcon::trayIconExit);
    trayIcon->setContextMenu(menu);
}

void TrayIcon::showMainWidget()
{
    if (mainWidget)
    {
        mainWidget->showNormal();
        mainWidget->activateWindow();
    }
}

void TrayIcon::closeAll()
{
    trayIcon->hide();
    trayIcon->deleteLater();
    qApp->exit();
}

void TrayIcon::setVisible(bool visible)
{
    if (trayIcon)
        trayIcon->setVisible(visible);
}

void TrayIcon::showMessage(const QString& title, const QString& msg)
{
    if (trayIcon)
        trayIcon->showMessage(title, msg, QSystemTrayIcon::Information, 3000);
}
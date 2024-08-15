#include <QtWidgets/QApplication>
#include <QFont>
#include "httpmusicplayer.h"
#include "filemanager.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    HttpMusicPlayer w;
    w.show();
    w.setFixedSize(1400, 900);
    return a.exec();
}
#include "utils.h"

namespace Utils 
{
    // 将播放位置转换为字符串显示xx:xx
    QString StringUtil::formatTime(int milliseconds)
    {
        int seconds = milliseconds / 1000;
        int minutes = seconds / 60;
        seconds %= 60;
        return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    }
} 
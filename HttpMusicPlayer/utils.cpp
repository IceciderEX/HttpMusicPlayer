#include "utils.h"

namespace Utils 
{
    // ������λ��ת��Ϊ�ַ�����ʾxx:xx
    QString StringUtil::formatTime(int milliseconds)
    {
        int seconds = milliseconds / 1000;
        int minutes = seconds / 60;
        seconds %= 60;
        return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    }
} 
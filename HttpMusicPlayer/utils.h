#ifndef __UTILS_H__
#define __UTILS_H__

// -------------------------------------------------------
// utils.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/26
// ���������������࣬�ṩһЩͨ�õĹ��ܺ���
// --------------------------------------------------------

#include <QString>
#include <QVector>

namespace Utils 
{
    class StringUtil 
    {
    public:
        static QString formatTime(int milliseconds);
    };
}

#endif

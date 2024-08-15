#ifndef __UTILS_H__
#define __UTILS_H__

// -------------------------------------------------------
// utils.h
// 创建者：Wanganmin
// 创建时间：2023/12/26
// 功能描述：工具类，提供一些通用的功能函数
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

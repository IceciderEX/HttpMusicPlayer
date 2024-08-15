#ifndef __IMAGEHANDLER_H__
#define __IMAGEHANDLER_H__

// -------------------------------------------------------
// imagehandler.h
// 创建者：Wanganmin
// 创建时间：2023/12/27
// 功能描述：图片处理类，用于处理专辑图片的生成
// --------------------------------------------------------

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include "common.h"

class ImageHandler : public QObject
{
    Q_OBJECT

public:
    explicit ImageHandler(QObject* parent = nullptr);
    ~ImageHandler() = default;

    static QPixmap loadImage(QSize imgSize, const QString& filePath);
};

#endif

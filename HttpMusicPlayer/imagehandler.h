#ifndef __IMAGEHANDLER_H__
#define __IMAGEHANDLER_H__

// -------------------------------------------------------
// imagehandler.h
// �����ߣ�Wanganmin
// ����ʱ�䣺2023/12/27
// ����������ͼƬ�����࣬���ڴ���ר��ͼƬ������
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

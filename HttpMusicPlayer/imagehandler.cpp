#include "ImageHandler.h"

ImageHandler::ImageHandler(QObject* parent)
    : QObject(parent) 
{
}

// ���صõ�Բ����ʾ��ͼƬ
QPixmap ImageHandler::loadImage(QSize imgSize,const QString& filePath)
{
    QPixmap originalPixmap(filePath);
    QSize viewSize = imgSize;
    // ����ͼƬ����Ӧ QGraphicsView
    QPixmap scaledPixmap = originalPixmap.scaled(viewSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // ����Բ���������ʾ
    QPixmap roundedPixmap(ALNUM_IMG_SIZE, ALNUM_IMG_SIZE);
    roundedPixmap.fill(Qt::transparent);
    QPainter painter(&roundedPixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::transparent);
    painter.drawEllipse(0, 0, ALNUM_IMG_SIZE, ALNUM_IMG_SIZE);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, ALNUM_IMG_SIZE, ALNUM_IMG_SIZE, scaledPixmap);

    return roundedPixmap;
}

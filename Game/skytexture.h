#ifndef SKYTEXTURE_H
#define SKYTEXTURE_H

#include <QBuffer>
#include <QFuture>
#include <QFutureWatcher>
#include <QImage>
#include <QMLData.h>
#include <QObject>
#include <QPainter>
#include <QQmlEngine>
#include <QQuick3DTextureData>
#include <QVector3D>
#include <QtConcurrent/QtConcurrentRun>
#include <macros.h>

class SkyTexture : public QQuick3DTextureData {
    Q_OBJECT
    QML_ELEMENT
    AUTO_PROPERTY_DEFAULT(CGEnums::TerrainType, terrainType, CGEnums::Desert)
    AUTO_PROPERTY_DEFAULT(CGEnums::Quality, quality, CGEnums::High)
    AUTO_PROPERTY_DEFAULT(QVector3D, sunDir, QVector3D(10, 10, -45))

    static QByteArray rgba8FromColor(QColor color);
    bool firstDraw = true;

private slots:
    void regenerateTextureData();

public:
    SkyTexture();
};

#endif // SKYTEXTURE_H

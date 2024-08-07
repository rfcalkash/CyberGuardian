#ifndef NOISEPROVIDER_H
#define NOISEPROVIDER_H

#include "macros.h"
#include "qpainter.h"
#include "qtconcurrentrun.h"
#include <QMLData.h>
#include <QObject>
#include <QQuickImageProvider>
#include <QRandomGenerator>
#include <noise/qnoise.h>

class NoiseProvider : public QQuickImageProvider {
    Q_OBJECT
    AUTO_PROPERTY_DEFAULT(qint32, seed, 0)
    AUTO_PROPERTY_DEFAULT(CGEnums::TerrainType, terrainType, CGEnums::Desert)

    QMap<QString, QSharedPointer<QImage>> m_images {
        { "h400", QSharedPointer<QImage>(new QImage(QSize(400, 400), QImage::Format_RGB32)) },
        { "h200", QSharedPointer<QImage>(new QImage(QSize(200, 200), QImage::Format_RGB32)) },
        { "h100", QSharedPointer<QImage>(new QImage(QSize(100, 100), QImage::Format_RGB32)) },
        { "diffuse", QSharedPointer<QImage>(new QImage(QSize(1600, 1600), QImage::Format_RGB32)) },
    };

    QVector<QVector<float>> m_noise;

    static QVector<QVector<float>> generateNoise(qint32 seed, const QSize& size);

public:
    NoiseProvider();

public slots:
    void generatePixmaps();

private slots:

    void drawMapsFromNoise();

signals:
    void mapsChanged();
    // QQuickImageProvider interface
public:
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
};

#endif // NOISEPROVIDER_H

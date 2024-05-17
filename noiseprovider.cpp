#include "noiseprovider.h"

QVector<QVector<float>> NoiseProvider::generateNoise(qint32 seed, const QSize& size)
{
    QNoise noise(seed);
    QVector<QVector<float>> data;
    data.resize(size.width());
    for (int x = 0; x < size.width(); ++x) {
        data[x].resize(size.height());
        for (int y = 0; y < size.height(); ++y) {
            data[x][y] = 0;
            for (int d = 1; d <= 3; ++d) {
                data[x][y] = noise.noise(x * d, y * d) / d;
            }
        }
    }
    return data;
}

void NoiseProvider::drawMapsFromNoise()
{
    QRandomGenerator rg(seed());
    QPainter h400P(m_images.value("h400").data());
    QPainter h200P(m_images.value("h200").data());
    QPainter h100P(m_images.value("h100").data());
    QPainter dP(m_images.value("diffuse").data());
    for (int x = 0; x < 400; ++x) {
        for (int y = 0; y < 400; ++y) {
            const auto height = m_noise[x][y];
            h400P.setPen(QColor::fromRgbF(height, height, height));
            h400P.drawPoint(QPointF(x, y));
            if (x % 2 == 0 && y % 2 == 0) {
                h200P.setPen(QColor::fromRgbF(height, height, height));
                h200P.drawPoint(QPointF(x / 2, y / 2));
                if (x % 4 == 0 && y % 4 == 0) {
                    h100P.setPen(QColor::fromRgbF(height, height, height));
                    h100P.drawPoint(QPointF(x / 4, y / 4));
                }
            }
            QColor penColor = StaticQmlHelper::fromTerrainType(terrainType());
            for (int dx = 0; dx < 4; ++dx) {
                for (int dy = 0; dy < 4; ++dy) {
                    dP.setPen(penColor.darker(rg.bounded(20)));
                    dP.drawPoint(x * 4 + dx, y * 4 + dy);
                }
            }
        }
    }
    h400P.end();
    h200P.end();
    h100P.end();
    dP.end();
    emit mapsChanged();
}

NoiseProvider::NoiseProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    connect(this, &NoiseProvider::seedChanged, this, &NoiseProvider::generatePixmaps);
    connect(this, &NoiseProvider::terrainTypeChanged, this, &NoiseProvider::drawMapsFromNoise);
}

void NoiseProvider::generatePixmaps()
{
    QtConcurrent::run(generateNoise, seed(), QSize(400, 400)).then([this](QVector<QVector<float>> data) {
        m_noise = data;
        drawMapsFromNoise();
    });
}

QImage NoiseProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    if (m_images.contains(id)) {
        const auto pm = m_images.value(id);
        *size = QSize(pm->size());
        return QImage(*pm);
    }
    *size = QSize(requestedSize);
    return QImage(requestedSize, QImage::Format_RGB32);
}

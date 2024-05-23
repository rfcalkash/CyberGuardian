#include "terraingeometry.h"

TerrainGeometry::TerrainGeometry()
    : QQuick3DGeometry()
{
    rebuild();
    connect(this, &TerrainGeometry::expChanged, this, &TerrainGeometry::rebuild);
}

void TerrainGeometry::chunksSize(const QSize& newValue)
{
    if (m_chunksSize != newValue) {
        m_chunksSize = newValue;
        m_sizeInVetex = QSize(requestedRect().width() * newValue.width(), requestedRect().height() * newValue.height());
        rebuild();
        emit chunksSizeChanged(newValue);
    }
}

void TerrainGeometry::fillVertexes(QVector<QVector<float>> data)
{
    QByteArray v;
    v.resize((2 * requestedRect().width() * requestedRect().height() + requestedRect().height() + requestedRect().width() + 1) * sizeof(float) * 3);
    QDataStream s(&v, QIODeviceBase::WriteOnly);
    float* p = reinterpret_cast<float*>(v.data());
    for (int x = 0; x < requestedRect().width(); ++x) {
        for (int y = 0; y < requestedRect().height(); ++y) {
            *p++ = x;
            *p++ = data[x][y];
            *p++ = y;
        }
    }
    QRandomGenerator rg(seed());
    for (int x = 0; x < requestedRect().width() - 1; ++x) {
        for (int y = 0; y < requestedRect().height() - 1; ++y) {
            *p++ = x + 0.5;
            *p++ = /*height() * (rg.generateDouble() * 0.002 - 0.001) + */ (data[x][y] + data[x + 1][y] + data[x][y + 1] + data[x + 1][y + 1]) / 4;
            *p++ = y + 0.5;
        }
    }
    setVertexData(v);
}

void TerrainGeometry::fillIndexes()
{
    QByteArray i;
    const auto width = requestedRect().width();
    i.resize(width * requestedRect().height() * 4 * 3 * sizeof(qint32));
    qint32* iP = reinterpret_cast<qint32*>(i.data());
    const qint32 initMidIndex = requestedRect().height() * width;
    for (int x = 0; x < requestedRect().width() - 1; ++x) {
        for (int y = 0; y < requestedRect().height() - 1; ++y) {
            qint32 center = initMidIndex + x + y * (width - 1);

            *iP++ = center;
            *iP++ = x + y * (width);
            *iP++ = x + 1 + y * (width);

            *iP++ = center;
            *iP++ = x + (y + 1) * (width);
            *iP++ = x + y * (width);

            *iP++ = center;
            *iP++ = x + 1 + (y + 1) * (width);
            *iP++ = x + (y + 1) * (width);

            *iP++ = center;
            *iP++ = x + 1 + y * (width);
            *iP++ = x + 1 + (y + 1) * (width);
        }
    }
    setIndexData(i);
}

void TerrainGeometry::fillVertexesSimple(QVector<QVector<float>> data)
{
    QByteArray v;
    v.resize((2 * requestedRect().width() * requestedRect().height() + requestedRect().height() + requestedRect().width() + 1) * sizeof(float) * 3);
    QDataStream s(&v, QIODeviceBase::WriteOnly);
    float* p = reinterpret_cast<float*>(v.data());
    for (int x = 0; x < requestedRect().width(); ++x) {
        for (int y = 0; y < requestedRect().height(); ++y) {
            *p++ = x;
            *p++ = data[x][y];
            *p++ = y;
        }
    }
    setVertexData(v);
}

void TerrainGeometry::fillIndexesSimple()
{
    QByteArray i;
    const auto width = requestedRect().width();
    i.resize(width * requestedRect().height() * 2 * 3 * sizeof(qint32));
    qint32* iP = reinterpret_cast<qint32*>(i.data());
    for (int x = 0; x < requestedRect().width() - 1; ++x) {
        for (int y = 0; y < requestedRect().height() - 1; ++y) {

            *iP++ = x + (y + 1) * (width);
            *iP++ = x + y * (width);
            *iP++ = x + 1 + y * (width);

            *iP++ = x + 1 + y * (width);
            *iP++ = x + 1 + (y + 1) * (width);
            *iP++ = x + (y + 1) * (width);
        }
    }
    setIndexData(i);
}

void TerrainGeometry::rebuild()
{
    clear();
    float maxH = 0;
    for (int d = 1; d <= OCTAVES; ++d) {
        maxH += 1.0 / d;
    }
    QNoise noise(seed());
    QVector<QVector<float>> data;
    data.resize(requestedRect().width());
    for (int x = 0; x < requestedRect().width(); ++x) {
        data[x].resize(requestedRect().height());
        for (int y = 0; y < requestedRect().height(); ++y) {
            float h = 0;
            for (int d = 1; d <= OCTAVES; ++d) {
                h += noise.noise((x + requestedRect().x()) * d / density(), (y + requestedRect().y()) * d / density()) / d;
            }
            const float d = qPow(2 * (float)((x + requestedRect().x()) - m_sizeInVetex.width() / 2) / flatSize().width(), 4) + qPow(2 * (float)((y + requestedRect().y()) - m_sizeInVetex.height() / 2) / flatSize().height(), 4);
            float maxHeight = d < 1 ? (height() - flatHeight()) * d * d * (3 - 2 * d) + flatHeight() : height();
            data[x][y] = maxHeight * qPow((h + maxH) / (2 * maxH), exp());
        }
    }
    setBounds(QVector3D(0, 0, 0), QVector3D(requestedRect().width(), height(), requestedRect().height()));
    setStride(3 * sizeof(float));
    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::IndexSemantic, 0, QQuick3DGeometry::Attribute::U32Type);
    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);
    fillVertexesSimple(data);
    fillIndexesSimple();
    emit terrainUpdated();
}

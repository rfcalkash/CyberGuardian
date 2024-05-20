#include "terraingeometry.h"

TerrainGeometry::TerrainGeometry()
    : QQuick3DGeometry()
{
    rebuild();
}

void TerrainGeometry::fillVertexes(QVector<QVector<float>> data)
{
    QByteArray v;
    v.resize((2 * size().width() * size().height() + size().height() + size().width() + 1) * sizeof(float) * 3);
    QDataStream s(&v, QIODeviceBase::WriteOnly);
    float* p = reinterpret_cast<float*>(v.data());
    // for (int x = 0; x < size().width(); ++x) {
    //     for (int y = 0; y < size().height(); ++y) {
    //         *p++ = x;
    //         *p++ = data[x][y];
    //         *p++ = y;
    //         float h = data[x][y];
    //         int d = 1;
    //         if (x > 0) {
    //             h += data[x - 1][y];
    //             d++;
    //         }
    //         if (y > 0) {
    //             h += data[x][y - 1];
    //             d++;
    //         }
    //         if (x < size().width() - 1) {
    //             h += data[x + 1][y];
    //             d++;
    //         }
    //         if (y < size().height() - 1) {
    //             h += data[x][y + 1];
    //             d++;
    //         }
    //         *p++ = x - 0.5;
    //         *p++ = h / d;
    //         *p++ = y - 0.5;
    //         if (x == size().width() - 1) {
    //             h = data[x][y];
    //             d = 1;
    //             if (y > 0) {
    //                 h += data[x][y - 1];
    //                 d++;
    //             }
    //             *p++ = x + 0.5;
    //             *p++ = h / d;
    //             *p++ = y - 0.5;
    //         }
    //     }
    // }
    // *p++ = -0.5;
    // *p++ = data[0][size().height() - 1];
    // *p++ = size().height() - 0.5;
    // for (int x = 1; x < size().width() - 1; ++x) {
    //     *p++ = x - 0.5;
    //     *p++ = (data[x][size().height() - 1] + data[x - 1][size().height() - 1]) / 2;
    //     *p++ = size().height() - 0.5;
    // }
    // *p++ = size().width() - 0.5;
    // *p++ = data[size().width() - 1][size().height() - 1];
    // *p++ = size().height() - 0.5;
    for (int x = 0; x < size().width(); ++x) {
        for (int y = 0; y < size().height(); ++y) {
            *p++ = x;
            *p++ = data[x][y];
            *p++ = y;
        }
    }
    QRandomGenerator rg(seed());
    for (int x = 0; x < size().width() - 1; ++x) {
        for (int y = 0; y < size().height() - 1; ++y) {
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
    i.resize(size().width() * size().height() * 4 * 3 * sizeof(qint32));
    qint32* iP = reinterpret_cast<qint32*>(i.data());
    // for (int x = 0; x < size().width(); ++x) {
    //     for (int y = 0; y < size().height(); ++y) {
    //         qint32 center = (x + y * size().width()) * 2 + y;
    //         qint32 tRShift = x < size().width() - 1 ? 3 : 2;
    //         *iP++ = center;
    //         *iP++ = center + tRShift;
    //         *iP++ = center + 1;

    //         if (y < size().height() - 1) {
    //             qint32 downCenter = (x + (y + 1) * size().width()) * 2 + y + 1;
    //             *iP++ = center;
    //             *iP++ = center + 1;
    //             *iP++ = downCenter + 1;

    //             *iP++ = center;
    //             *iP++ = downCenter + 1;
    //             *iP++ = downCenter + tRShift;

    //             *iP++ = center;
    //             *iP++ = downCenter + tRShift;
    //             *iP++ = center + tRShift;
    //         } else {
    //             qint32 downLeft = size().width() * size().height() * 2 + 3 + x;
    //             *iP++ = center;
    //             *iP++ = center + 1;
    //             *iP++ = downLeft;

    //             *iP++ = center;
    //             *iP++ = downLeft;
    //             *iP++ = downLeft + 1;

    //             *iP++ = center;
    //             *iP++ = downLeft + 1;
    //             *iP++ = center + tRShift;
    //         }
    //     }
    // }
    const qint32 initMidIndex = size().height() * size().width();
    for (int x = 0; x < size().width() - 1; ++x) {
        for (int y = 0; y < size().height() - 1; ++y) {
            qint32 center = initMidIndex + x + y * (size().width() - 1);

            *iP++ = center;
            *iP++ = x + y * (size().width());
            *iP++ = x + 1 + y * (size().width());

            *iP++ = center;
            *iP++ = x + (y + 1) * (size().width());
            *iP++ = x + y * (size().width());

            *iP++ = center;
            *iP++ = x + 1 + (y + 1) * (size().width());
            *iP++ = x + (y + 1) * (size().width());

            *iP++ = center;
            *iP++ = x + 1 + y * (size().width());
            *iP++ = x + 1 + (y + 1) * (size().width());
        }
    }
    setIndexData(i);
}

void TerrainGeometry::rebuild()
{
    float maxH = 0;
    float minH = 0;
    QNoise noise(seed());
    QVector<QVector<float>> data;
    data.resize(size().width());
    for (int x = 0; x < size().width(); ++x) {
        data[x].resize(size().height());
        for (int y = 0; y < size().height(); ++y) {
            data[x][y] = 0;
            for (int d = 1; d <= 3; ++d) {
                float h = noise.noise(x * d / density(), y * d / density()) / d;
                data[x][y] = h;
                if (x == 0 && y == 0) {
                    maxH = h;
                    minH = h;
                } else {
                    if (h > maxH) {
                        maxH = h;
                    }
                    if (h < minH) {
                        minH = h;
                    }
                }
            }
        }
    }
    for (int x = 0; x < size().width(); ++x) {
        for (int y = 0; y < size().height(); ++y) {
            const float d = qPow(2 * (float)(x - size().width() / 2) / flatSize().width(), 4) + qPow(2 * (float)(y - size().height() / 2) / flatSize().height(), 4);
            float maxHeight = d < 1 ? (height() - flatHeight()) * d * d * (3 - 2 * d) + flatHeight() : height();
            data[x][y] = maxHeight * (data[x][y] - minH) / (maxH - minH);
        }
    }
    setBounds(QVector3D(0, 0, 0), QVector3D(size().width() + 1, height(), size().height() + 1));
    setStride(3 * sizeof(float));
    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic, 0, QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::IndexSemantic, 0, QQuick3DGeometry::Attribute::U32Type);
    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);
    fillVertexes(data);
    fillIndexes();
}

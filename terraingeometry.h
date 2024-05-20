#ifndef TERRAINGEOMETRY_H
#define TERRAINGEOMETRY_H

#include "macros.h"
#include "noise/qnoise.h"
#include "qrandom.h"
#include "qsize.h"
#include "qvectornd.h"
#include <QColor>
#include <QObject>
#include <QQmlEngine>
#include <QQuick3DGeometry>

class TerrainGeometry : public QQuick3DGeometry {
    Q_OBJECT
    QML_NAMED_ELEMENT(TerrainGeometry)
    AUTO_PROPERTY_DEFAULT(qint32, seed, 0)
    AUTO_PROPERTY_DEFAULT(QSize, size, QSize(800, 800))
    AUTO_PROPERTY_DEFAULT(QSize, flatSize, QSize(600, 400))
    AUTO_PROPERTY_DEFAULT(float, height, 100)
    AUTO_PROPERTY_DEFAULT(float, flatHeight, 10)
    AUTO_PROPERTY_DEFAULT(float, density, 100)
public:
    TerrainGeometry();
public slots:
    void rebuild();

private:
    void fillVertexes(QVector<QVector<float>> data);
    void fillIndexes();
    void pushVertex(float* buf, float x, float y, float z, const QColor& color);
};

#endif // TERRAINGEOMETRY_H

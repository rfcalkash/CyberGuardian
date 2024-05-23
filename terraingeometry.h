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

#define OCTAVES 10

#define AUTO_PROPERTY_DEFAULT_REBUILD(TYPE, NAME, DEFAULT)                \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME##Changed FINAL) \
public:                                                                   \
    TYPE NAME() const                                                     \
    {                                                                     \
        return m_##NAME;                                                  \
    }                                                                     \
    void NAME(const TYPE& newValue)                                       \
    {                                                                     \
        if (m_##NAME != newValue) {                                       \
            m_##NAME = newValue;                                          \
            rebuild();                                                    \
            emit NAME##Changed(newValue);                                 \
        }                                                                 \
    }                                                                     \
signals:                                                                  \
    Q_SIGNAL void NAME##Changed(const TYPE& newValue);                    \
                                                                          \
private:                                                                  \
    TYPE m_##NAME = DEFAULT;

class TerrainGeometry : public QQuick3DGeometry {
    Q_OBJECT
    QML_NAMED_ELEMENT(TerrainGeometry)
    AUTO_PROPERTY_DEFAULT_REBUILD(qint32, seed, 0)
    AUTO_PROPERTY_WRITE_DEFAULT(QSize, chunksSize, QSize(80, 80))
    AUTO_PROPERTY_DEFAULT_REBUILD(QSize, flatSize, QSize(600, 600))
    AUTO_PROPERTY_DEFAULT_REBUILD(QRect, requestedRect, QRect(0, 0, 100, 100))
    AUTO_PROPERTY_DEFAULT_REBUILD(float, height, 500)
    AUTO_PROPERTY_DEFAULT_REBUILD(float, flatHeight, 10)
    AUTO_PROPERTY_DEFAULT_REBUILD(float, density, 100)
    AUTO_PROPERTY_DEFAULT_REBUILD(float, exp, 3)

    QSize m_sizeInVetex = QSize(requestedRect().width() * chunksSize().width(), requestedRect().height() * chunksSize().height());

public:
    TerrainGeometry();

    void chunksSize(const QSize& newValue);

public slots:
    void rebuild();

signals:
    void terrainUpdated();

private:
    void fillVertexes(QVector<QVector<float>> data);
    void fillIndexes();
    void pushVertex(float* buf, float x, float y, float z, const QColor& color);
};

#endif // TERRAINGEOMETRY_H

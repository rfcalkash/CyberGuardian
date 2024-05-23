#ifndef QMLDATA_H
#define QMLDATA_H

#include "qobject.h"
#include "qobjectdefs.h"
#include "qpoint.h"
#include "qqmlintegration.h"
#include "qsize.h"
#include "qtmetamacros.h"
#include <QColor>
#include <QVariantMap>
#include <QVector3D>

namespace CGEnums {
Q_NAMESPACE
QML_ELEMENT
enum TerrainType {
    Desert,
    Snow,
    Grass
};
Q_ENUM_NS(TerrainType)

enum Quality {
    Low,
    Medium,
    High
};
Q_ENUM_NS(Quality)
}

class StaticQmlHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    Q_INVOKABLE static QColor fromTerrainType(CGEnums::TerrainType tType)
    {
        switch (tType) {
        case CGEnums::Desert:
            return 0xe1bf92;
        case CGEnums::Snow:
            return 0xFFFFFF;
        default:
            return 0x91eb95;
        }
    }

    Q_INVOKABLE static QColor roadFromTerrainType(CGEnums::TerrainType tType)
    {
        switch (tType) {
        case CGEnums::Desert:
            return 0x493c3c;
        case CGEnums::Snow:
            return 0x6b5428;
        default:
            return 0xe7c496;
        }
    }

    Q_INVOKABLE static QColor skyColor()
    {
        return 0x8ae5ff;
    }

    Q_INVOKABLE static QVariantList rebuildChunksModel(const QSize& size, const QSize& chunkSize)
    {
        QVariantList ret;
        for (int x = 0; x < size.width(); ++x) {
            for (int y = 0; y < size.width(); ++y) {
                ret.append(QVariantMap { { "rect", QRect(x * chunkSize.width(), y * chunkSize.height(), chunkSize.width() + 1, chunkSize.height() + 1) },
                    { "position", QVector3D(x * (chunkSize.width()), 0, y * (chunkSize.height())) } });
            }
        }
        return ret;
    }
};

#endif // QMLDATA_H

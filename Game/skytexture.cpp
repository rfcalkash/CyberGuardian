#include "skytexture.h"

void SkyTexture::regenerateTextureData()
{
    const auto groundColor = rgba8FromColor(StaticQmlHelper::fromTerrainType(terrainType()));
    const auto skyColor = rgba8FromColor(StaticQmlHelper::skyColor());
    if (firstDraw) {
        firstDraw = false;
        setSize(QSize(1, 2));
        QByteArray textureData;
        textureData.append(groundColor);
        textureData.append(skyColor);
        setTextureData(textureData);
        update();
    }
    int size = qPow<int, int>(4, (int)quality() + 3);

    QImage image(QSize(size, size), QImage::Format_RGBA8888);
    QPainter painter(&image);
    painter.fillRect(0, 0, size, size / 2, StaticQmlHelper::skyColor());
    painter.fillRect(0, size / 2, size, size / 2, StaticQmlHelper::fromTerrainType(terrainType()));
    painter.end();
    // QByteArray textureData(*image.constBits(), image.sizeInBytes());
    QByteArray textureData;
    // QBuffer buf(&textureData);
    // buf.open(QIODeviceBase::WriteOnly);
    // image.save(&buf, "BMP");
    // buf.close();

    for (int y = size - 1; y >= 0; --y) {
        for (int x = 0; x < size; ++x) {
            textureData.append(rgba8FromColor(image.pixelColor(x, y)));
        }
    }
    // for (int y = 0; y < size / 2; ++y) {
    //     for (int x = 0; x < size; ++x) {
    //         textureData.append(groundColor);
    //     }
    // }
    // for (int y = 0; y < size / 2; ++y) {
    //     for (int x = 0; x < size; ++x) {
    //         textureData.append(skyColor);
    //     }
    // }
    setSize(QSize(size, size));
    setTextureData(textureData);
    update();
}

QByteArray SkyTexture::rgba8FromColor(QColor color)
{
    QByteArray ret;
    ret.append(255 * color.redF());
    ret.append(255 * color.greenF());
    ret.append(255 * color.blueF());
    ret.append(0xFF);
    return ret;
}

SkyTexture::SkyTexture()
    : QQuick3DTextureData()
{
    setFormat(QQuick3DTextureData::Format::RGBA8);
    setHasTransparency(false);
    regenerateTextureData();
    connect(this, &SkyTexture::terrainTypeChanged, this, &SkyTexture::regenerateTextureData);
}

#include "utils.h"

// Get image path (local file path)
QString Utils::getFolderPath()
{
    return "file://" + QStandardPaths::locate(QStandardPaths::PicturesLocation, "Books", QStandardPaths::LocateDirectory);
}

// Generate Base64 image from QImage data
// temp => should use image provider instead
QString Utils::generateBase64Url(const QImage &img, const QString &type)
{
    // byte array for image data
    QByteArray imgData;
    QBuffer buffer(&imgData);

    // QString to const char *
    // see: https://wiki.qt.io/Technical_FAQ#How_can_I_convert_a_QString_to_char.2A_and_vice_versa.3F
    QByteArray ba = type.toLocal8Bit();
    const char *imgFormat = ba.data();

    // Save image data into buffer
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, imgFormat);

    // Generate Base64 QString from buffer
    QString base64Img("data:image/"+type+";base64,");
    base64Img.append(QString::fromLatin1(imgData.toBase64().data()));

    return base64Img;
}

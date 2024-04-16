#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QByteArray>
#include <QBuffer>
#include <QImage>

#include <QDebug>

class Utils
{
public:
    static QString getFolderPath();
    static QString generateBase64Url(const QImage &, const QString &);
};

#endif // UTILS_H

#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QImage>
#include <QTimer>
#include <QThread>
#include <QFileInfo>
#include <QtQml>
#include <QUrl>
#include <QDebug>

#include <opencv2/opencv.hpp>

#include "OCR/translationthread.h"
#include "OCR/imagetreatment.h"
#include "Helpers/selection.h"
#include "Helpers/utils.h"
#include "apicontroller.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString image READ image NOTIFY imageChanged FINAL)
    Q_PROPERTY(QString translation READ translation WRITE setTranslation NOTIFY translationChanged FINAL)
    Q_PROPERTY(Selection imgSelection READ getSelection WRITE setSelection NOTIFY selectionChanged FINAL)
public:
    explicit AppController(QObject *parent = nullptr);

    // get "Image" folder filepath
    Q_INVOKABLE QString folderPath() const;

    // opencv image result
    QString image() const;

    // tesseract translation text content
    QString translation() const;

    // image text selection
    Selection getSelection() const;
    void setSelection(Selection selection);
    Selection img_selection; // Selection struct


signals:
    void imageChanged();
    void translationStarted();
    void translationChanged();
    void selectionChanged();
    void processImgStarted();

public slots:
    void initProcess(QString selectedFile);
    void imgToText();
    void setTranslation(QString newTranslation);


private:
    void tesseractResults(const QString &res);

    QImage _img_data; // for display (opencv intermediate result)
    cv::Mat _treated; // opencv result
    cv::Mat _edited; // final image
    QString m_translation; // tesseract result
    const int _timeoutVal; // timeout while process occur

    float m_ratio; // image ratio value
    QString _filetype; // file type (jpeg or png)
};
#endif // APPCONTROLLER_H

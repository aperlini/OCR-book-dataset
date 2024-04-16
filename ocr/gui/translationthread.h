#ifndef TRANSLATIONTHREAD_H
#define TRANSLATIONTHREAD_H

#include <QThread>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class TranslationThread : public QThread
{
    Q_OBJECT
public:
    explicit TranslationThread(const cv::Mat &mat_processed);
    ~TranslationThread();

protected:
    void run() override;

signals:
    void translationDone(const QString &);

private:
    tesseract::TessBaseAPI *m_tessApi = nullptr; // tesseract api
    Pix *m_pixData = nullptr; // necessary leptonica format for tesseract
    cv::Mat m_imgArea; // open cv processed image selection
    QString m_textContent; // translated text

    Pix *convertToPix(const cv::Mat &mat);
};

#endif // TRANSLATIONTHREAD_H

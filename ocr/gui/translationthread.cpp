#include "translationthread.h"

TranslationThread::TranslationThread(const cv::Mat &mat_processed)
{
    m_tessApi = new tesseract::TessBaseAPI(); // Tesseract translation api
    m_imgArea = mat_processed; // cv::mat text image selection
}

TranslationThread::~TranslationThread()
{
    pixDestroy(&m_pixData);
    delete m_tessApi;
}

void TranslationThread::run()
{    
    // Convert cv::mat to Pix
    m_pixData = convertToPix(m_imgArea);
    if(m_pixData == nullptr) {
        qFatal() << "cv::mat to pix conversion failed";
    }
    // qInfo() << "pix image w: " << pixData->w << ", and h: " << pixData->h;

    // Starting api
    if(m_tessApi->Init(NULL, "eng")) {
        qFatal() << "tesseract::TessBaseAPI : could not initialize";
    }

    // Provide image data
    m_tessApi->SetImage(m_pixData);
    m_tessApi->SetSourceResolution(300);

    // Recognized text returned as char * (utf8 encoded)
    char *recognized = m_tessApi->GetUTF8Text();
    m_textContent = QString::fromUtf8(recognized);
    delete[] recognized;

    // Replacing new line to keep text as a block
    m_textContent.replace(QChar('\n'), QChar(' '));

    // Closing down api
    m_tessApi->End();

    // emit signal with text to image data
    emit translationDone(m_textContent);
}

/*
 * Convert OpenCV `Mat` to Leptonic `Pix` image format
 * Tesseract will requires Leptonic image representation for translation
 *
 * Conversion based on : https://stackoverflow.com/questions/39293922/convert-between-opencv-mat-and-leptonica-pix
 *
 */
Pix *TranslationThread::convertToPix(const cv::Mat &mat)
{
    Pix *p = pixCreate(mat.cols, mat.rows, 8);
    for(l_uint32 y=0; y<mat.rows; y++) {
        for(l_uint32 x=0; x<mat.cols; x++) {
            pixSetPixel(p, x, y, (l_uint32)(mat.at<uchar>(y,x)));
        }
    }
    return p;
}

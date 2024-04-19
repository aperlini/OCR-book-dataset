#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent}, m_translation{""},  _timeoutVal{1000}
{
    img_selection.m_is_active = false;
}

/*
 * Image process (First Stage) :
 *
 * - 1: loading image
 * - 2: process in opencv
 * - 3: display image at the end of the process
 *
 */
void AppController::initProcess(QString selectedFile)
{
    // emit process started
    emit processImgStarted();

    // get file absolute path
    QUrl fileUrl(selectedFile);
    QString tmpStr = fileUrl.toLocalFile();

    // Get file extension
    QFileInfo fi(tmpStr);
    _filetype = fi.completeSuffix();
    // qInfo() << "filetype : " << _filetype;

    // Qstring to std::string convert
    std::string img_path = tmpStr.toStdString();

    // OpenCV read image data
    const cv::Mat tmp  = ImageTreatment::readImg(img_path);

    // OpenCV grayscale img
    _treated = ImageTreatment::grayscale(tmp);

    // qInfo() << "original size (w): " << _treated.size().width << ", (h): " << _treated.size().height;

    // set image to be displayed
    _img_data = ImageTreatment::matToQImage(_treated);

    // Processed done
    QTimer::singleShot(_timeoutVal, this, [=](){
        emit imageChanged();
    });
}

/*
 * Image to text (Second Stage) :
 *
 * - send processed image to tesseract api translation thread
 * - display result at the end of process
 *
 */

void AppController::imgToText() {

    // crop cv::mat based on text (image) selection
    if(img_selection.m_is_active) {
        _edited = ImageTreatment::cropSelection(_treated, img_selection);
        _treated = _edited;
    }

    // signal process started
    emit translationStarted();

    // Handling translation with new thread
    TranslationThread *t = new TranslationThread(_treated);
    connect(t, &TranslationThread::translationDone, this, &AppController::tesseractResults);

    // Ensure new thread self-destructed when it finished
    connect(t, &TranslationThread::finished, t, &TranslationThread::deleteLater);

    // Starting new thread
    t->start();
}

// Handling tesseract results
void AppController::tesseractResults(const QString &res)
{
    m_translation = res;

    // signal process ended
    emit translationChanged();
}

// Image to url (displaying results)
QString AppController::image() const
{
    return Utils::generateBase64Url(_img_data, _filetype);
}

// Default image folder path
QString AppController::folderPath() const
{
    return Utils::getFolderPath();
}


// Translation (text to image content) property accessor
QString AppController::translation() const
{
    return m_translation;
}

// Translation (text to image content) property setter
void AppController::setTranslation(QString newTranslation)
{
    if(m_translation != newTranslation) {
        m_translation = newTranslation;
        emit translationChanged();
    }
}

// Current text selection on image
Selection AppController::getSelection() const
{
    return img_selection;
}

// Updating text selection on image
void AppController::setSelection(Selection selection)
{
    img_selection = selection;
    // selection is active if area exist
    img_selection.m_is_active = (img_selection.m_w > 0 && img_selection.m_h > 0);
    emit selectionChanged();
}



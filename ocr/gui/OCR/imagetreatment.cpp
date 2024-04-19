#include "imagetreatment.h"


/*
 * OpenCV imread wrapper
 *
 */
cv::Mat ImageTreatment::readImg(const std::string &filepath)
{
    // read image in OpenCV
    cv::Mat mat = cv::imread(filepath, cv::IMREAD_COLOR);

    if(!mat.data) {
        qFatal() << "Could not read image data";
    }

    return mat;
}

/*
 * OpenCV grayscale
 *
 */
cv::Mat ImageTreatment::grayscale(const cv::Mat &mat)
{
    cv::Mat grayscale;
    cv::cvtColor(mat, grayscale, cv::COLOR_BGR2GRAY);

    return grayscale;
}

/*
 * OpenCV cv::Mat scale
 *
 */
cv::Mat ImageTreatment::scale(const cv::Mat &mat, const float scale)
{
    // Original cv::Mat size
    int orig_w = mat.size().width;
    int orig_h = mat.size().height;

    // img scale
    float ratio = (scale-1.0)*100.0;

    // how much width and height of image must be scaled
    float wDiff = (float)(orig_w / 100.0) * ratio;
    float hDiff = (float)(orig_h / 100.0) * ratio;

    // diff must be split for each side of image
    int xOffset = (int)(wDiff) / 2;
    int yOffset = (int)(hDiff) / 2;

    // generate new matrix with region of interest to be cropped
    // as we crop the image, offset x and y are doubled to be removed from width and height
    // Rect(x, y, width, height)
    cv::Mat ROI(mat, cv::Rect(xOffset, yOffset, orig_w-(xOffset*2), orig_h-(yOffset*2)));

    // making a copy to be returned
    cv::Mat cropped;
    ROI.copyTo(cropped);

    return cropped;
}

/*
 * OpenCV cv::Mat crop image selection
 *
 */
cv::Mat ImageTreatment::cropSelection(const cv::Mat &mat, Selection &imgSelection)
{
    // Original cv::Mat size
    int orig_w = mat.size().width;
    int orig_h = mat.size().height;

    // calculate width and height ratio (visible size vs. real size)
    float wRatio = ((float)orig_w / (float)imgSelection.m_visible_w);
    float hRatio = ((float)orig_h / (float)imgSelection.m_visible_h);

    // apply ratio on imgSelection
    float xOffset = (float)(imgSelection.m_x) * wRatio;
    float yOffset = (float)(imgSelection.m_y) * hRatio;
    float width = (float)(imgSelection.m_w) * wRatio;
    float height = (float)(imgSelection.m_h) * hRatio;

    // generate new matrix with region of interest to be cropped
    // Rect(x, y, width, height)
    cv::Mat ROI(mat, cv::Rect((int)xOffset, (int)yOffset, (int)width , (int)height));

    // making a copy to be returned
    cv::Mat cropped;
    ROI.copyTo(cropped);

    return cropped;
}


/*
 * Convert OpenCV `Mat` to `QImage`
 * and determine OpenCV image format for conversion
 * Based on : https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
 *
 */
QImage ImageTreatment::matToQImage(const cv::Mat &mat)
{
    QImage conv_img;

    switch(mat.type()) {
        case CV_8UC4:
            conv_img = format(mat, QImage::Format_ARGB32);
            break;
        case CV_8UC3:
            conv_img = format(mat, QImage::Format_RGB888);
            conv_img.rgbSwap();
            break;
        case CV_8UC1:
            conv_img = format(mat, QImage::Format_Grayscale8);
            break;
        default:
            qFatal() << "Unrecognized format";
    }

    return conv_img;
}

/*
 * Wrapper method for cv::Mat format conversion
 *
 */
QImage ImageTreatment::format(const cv::Mat &mat, const QImage::Format &f)
{
    return QImage((uchar *)mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), f);
}

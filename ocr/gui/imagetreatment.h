#ifndef IMAGETREATMENT_H
#define IMAGETREATMENT_H

#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include "selection.h"

class ImageTreatment
{

public:
    static cv::Mat readImg(const std::string &filepath);
    static cv::Mat grayscale(const cv::Mat &mat);
    static QImage matToQImage(const cv::Mat &mat);
    static cv::Mat scale(const cv::Mat &mat, const float scale);
    static cv::Mat cropSelection(const cv::Mat &mat, Selection &imgSelection);

private:
    static QImage format(const cv::Mat &mat, const QImage::Format &f);

};

#endif // IMAGETREATMENT_H

#ifndef FILTERS_H
#define FILTERS_H

#include "opencv2/opencv.hpp"

#define SCREEN 10
#define WIDTH 320
#define HEIGHT 240

cv::Mat threshold(cv::Mat frame);
cv::Mat blur(cv::Mat frame);
cv::Mat highlightEdge(cv::Mat frame1, cv::Mat frame2);
cv::Mat positionEdgeLR(cv::Mat frame);
cv::Mat frameDiff(cv::Mat currentFrame, cv::Mat prevFrame);
cv::Mat moveEdgeLR(cv::Mat currentFrame, cv::Mat prevFrame);
cv::Mat directionLR(cv::Mat currentFrame, cv::Mat prevFrame);
cv::Mat directionUT(cv::Mat currentFrame, cv::Mat prevFrame);
cv::Mat direction(cv::Mat currentFrame, cv::Mat prevFrame);

#endif

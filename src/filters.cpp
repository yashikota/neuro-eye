#include "filters.h"

#include <iostream>

cv::Mat threshold(cv::Mat frame) {
    cv::Mat grayFrame, binaryFrame, colorFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::threshold(grayFrame, binaryFrame, 0, 255,
                  cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::cvtColor(binaryFrame, colorFrame, cv::COLOR_GRAY2BGR);
    return colorFrame;
}

cv::Mat blur(cv::Mat frame) {
    cv::Mat blurFrame;
    cv::GaussianBlur(frame, blurFrame, cv::Size(15, 15), 0);
    return blurFrame;
}

cv::Mat highlightEdge(cv::Mat frame1, cv::Mat frame2) {
    cv::Mat diffFrame, grayFrame1, grayFrame2;

    cv::cvtColor(frame1, grayFrame1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(frame2, grayFrame2, cv::COLOR_BGR2GRAY);

    diffFrame = grayFrame1.clone();

    grayFrame1.forEach<uchar>([&](uchar &pixel, const int *position) -> void {
        int diff = pixel - grayFrame2.at<uchar>(position[0], position[1]);
        diff += 128;
        if (diff < 0) diff = 0;
        if (diff > 255) diff = 255;
        diffFrame.at<uchar>(position[0], position[1]) = diff;
    });

    cv::cvtColor(diffFrame, diffFrame, cv::COLOR_GRAY2BGR);
    return diffFrame;
}

cv::Mat positionEdgeLR(cv::Mat frame) {
    cv::Mat grayFrame, colorFrame;
    colorFrame = frame.clone();
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    grayFrame.forEach<uchar>([&](uchar &pixel, const int *position) -> void {
        if (position[1] == 0) return;
        const int prevPixel = grayFrame.at<uchar>(position[0], position[1] - 1);
        const int diff = prevPixel - pixel;
        if (prevPixel > 128 && pixel < 128 && diff >= 15) {  // white to black
            colorFrame.at<cv::Vec3b>(position[0], position[1]) =
                cv::Vec3b(0, 0, 255);
        } else if (prevPixel < 128 && pixel > 128 &&
                   diff <= -15) {  // black to white
            colorFrame.at<cv::Vec3b>(position[0], position[1]) =
                cv::Vec3b(255, 0, 0);
        }
    });

    return colorFrame;
}

cv::Mat frameDiff(cv::Mat currentFrame, cv::Mat prevFrame) {
    cv::Mat grayCurrentFrame, grayPrevFrame, diffFrame;
    cv::cvtColor(currentFrame, grayCurrentFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(prevFrame, grayPrevFrame, cv::COLOR_BGR2GRAY);

    cv::absdiff(grayCurrentFrame, grayPrevFrame, diffFrame);
    cv::cvtColor(diffFrame, diffFrame, cv::COLOR_GRAY2BGR);

    return diffFrame;
}

cv::Mat moveEdgeLR(cv::Mat currentFrame, cv::Mat prevFrame) {
    cv::Mat grayCurrentFrame, grayPrevFrame, colorFrame;
    colorFrame = currentFrame.clone();
    cv::cvtColor(currentFrame, grayCurrentFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(prevFrame, grayPrevFrame, cv::COLOR_BGR2GRAY);

    grayCurrentFrame.forEach<uchar>([&](uchar &pixel,
                                        const int *position) -> void {
        const int prevPixel = grayPrevFrame.at<uchar>(position[0], position[1]);
        const int diff = prevPixel - pixel;
        if (prevPixel > 128 && pixel < 128) {  // white to black
            colorFrame.at<cv::Vec3b>(position[0], position[1]) =
                cv::Vec3b(0, 0, 255);
        } else if (prevPixel < 128 && pixel > 128) {  // black to white
            colorFrame.at<cv::Vec3b>(position[0], position[1]) =
                cv::Vec3b(255, 0, 0);
        }
    });

    return colorFrame;
}

// cv::Mat directionLR(cv::Mat currentFrame, cv::Mat prevFrame) {}

// cv::Mat directionUT(cv::Mat currentFrame, cv::Mat prevFrame) {}

// cv::Mat direction(cv::Mat currentFrame, cv::Mat prevFrame) {}

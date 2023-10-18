#include "filters.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

void initialize(cv::VideoCapture &cap) {
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open camera" << std::endl;
        exit(-1);
    }

    // set camera resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);
}

cv::Mat concat(cv::Mat frame[]) {
    const int halfScreen = SCREEN / 2;
    cv::Mat hConcatFrame1, hConcatFrame2, vConcatFrame;
    cv::hconcat(frame, halfScreen, hConcatFrame1);
    cv::hconcat(frame + halfScreen, halfScreen, hConcatFrame2);
    cv::vconcat(hConcatFrame1, hConcatFrame2, vConcatFrame);
    return vConcatFrame;
}

int main() {
    cv::VideoCapture cap;
    initialize(cap);

    cv::Mat frame[SCREEN];
    cv::Mat prevFrame = cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
    cv::Mat prevDiffFrame = cv::Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

    while (cap.read(frame[0])) {
        for (int i = 1; i < SCREEN; i++) {
            frame[i] = frame[0].clone();
        }

        frame[1] = threshold(frame[1]);
        frame[2] = blur(frame[2]);
        frame[3] = highlightEdge(frame[0], frame[2]);
        frame[4] = positionEdgeLR(frame[3]);
        frame[5] = frameDiff(frame[0], prevFrame);
        frame[6] = moveEdgeLR(frame[5], prevDiffFrame);
        // frame[7] = directionLR(frame[0], prevFrame);
        // frame[8] = directionUT(frame[0], prevFrame);
        // frame[9] = direction(frame[0], prevFrame);

        prevFrame = frame[0].clone();
        prevDiffFrame = frame[5].clone();

        cv::imshow("neuro-eye", concat(frame));

        const int key = cv::waitKey(1);
        if (key == 'q') break;
    }
    cv::destroyAllWindows();

    return 0;
}

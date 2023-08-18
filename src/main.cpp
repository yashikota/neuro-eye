#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) return -1;

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::imshow("neuro-eye", frame);
        const int key = cv::waitKey(1);
        if (key == 'q') break;
    }
    cv::destroyAllWindows();

    return 0;
}

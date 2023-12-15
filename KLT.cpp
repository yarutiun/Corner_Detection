
#include "KLT.hpp"

using namespace cv;
using namespace std;

Klt::Klt(){ };
Klt::~Klt(){ };

void Klt::KLT(void)
{
    // Create a tracker
    string trackerType = "CSRT";

    // Create a FAST object
    Ptr<FastFeatureDetector> detector = cv::FastFeatureDetector::create(50, true);

    // Read video
    VideoCapture video("apart.gif");

    // Read first frame
    Mat frame;
    bool ok = video.read(frame);

    // Define initial bounding box
    Rect2d bbox(287, 23, 86, 320);

    // Convert the current frame to grayscale
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

    // Detect corners of the current frame using the FAST algorithm
    vector<KeyPoint> corners;
    detector->detect(grayFrame, corners);

    // Draw corners on the frame
    for (int i = 0; i < corners.size(); i++) {
        Point2f point = corners[i].pt;
        circle(frame, point, 5, Scalar(0, 0, 255), -1);
    }

    // Initialize the tracker with the initial bounding box and the corners of the first frame
    Ptr<Tracker> tracker;
    tracker = TrackerCSRT::create();
    tracker->init(frame, bbox);

    while (video.read(frame)) {

        // Convert the current frame to grayscale
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Detect corners of the current frame using the FAST algorithm
        vector<KeyPoint> corners;
        detector->detect(grayFrame, corners);

        // Update the tracker with the current frame and the corners of the current frame
        Rect_<int> bboxInt = bbox;
        bool ok = tracker->update(frame, bboxInt);

        // Draw the tracked object on the frame
        if (ok) {
            for (int i = 0; i < corners.size(); i++) {
                Point2f point = corners[i].pt;
                circle(frame, point, 5, Scalar(0, 0, 255), -1);
            }
        }

        imshow("Tracking", frame);

        // Exit if ESC pressed
        int k = waitKey(1);
        if (k == 27) {
            break;
        }
    }
}

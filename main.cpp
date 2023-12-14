#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Function to detect corners using the FAST algorithm
void fastCornerDetection(Mat image, int threshold, vector<Point2f>& corners) {
    // Initialize the indicator array
    vector<bool> indicator(image.rows * image.cols, false);

    // Apply the FAST algorithm to detect corners
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            // Check if the current point is a potential corner
            bool isCorner = true;

            // Check the pixels within a circle around the current point
            for (int x = -threshold; x <= threshold; x++) {
                for (int y = -threshold; y <= threshold; y++) {
                    if (i + x < 0 || i + x >= image.rows || j + y < 0 || j + y >= image.cols) {
                        continue;
                    }

                    if (image.at<uchar>(i, j + y) > image.at<uchar>(i, j) + threshold) {
                        indicator[i * image.cols + j + y] = true;
                    } else if (image.at<uchar>(i, j + y) < image.at<uchar>(i, j) - threshold) {
                        indicator[i * image.cols + j + y] = true;
                    }
                }
            }

            // If the number of strong pixels exceeds the threshold, it's a corner
            int strongPixelCount = 0;
            for (int x = -threshold; x <= threshold; x++) {
                for (int y = -threshold; y <= threshold; y++) {
                    if (indicator[i * image.cols + j + y]) {
                        strongPixelCount++;
                    }
                }
            }

            if (strongPixelCount >= threshold) {
                corners.push_back(Point2f(j, i));
                isCorner = false;
            }
        }
    }
}

int main() {
    // Read the image
    Mat image = imread("leaf.jpeg");

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    imshow("Grey", grayImage);

    // Apply a bilateral filter to reduce noise
    Mat denoisedImage;

    //remove noise from image for efficiency
    bilateralFilter(grayImage, denoisedImage, 9, 75, 75);

    // Set the threshold for corner detection
    int threshold = 10;

    // Vector to store detected corners
    vector<Point2f> corners;

    // Detect corners using the FAST algorithm
    fastCornerDetection(grayImage, threshold, corners);

    // Display the original image and the detected corners
    imshow("Original Image", image);

    // Convert the vector of corners to a vector of KeyPoints
    vector<KeyPoint> keyPoints;
    for (const Point2f& point : corners) {
        KeyPoint keypoint;
        keypoint.pt = point;
        keyPoints.push_back(keypoint);
    }

    drawKeypoints(image, keyPoints, image);
    imshow("Corners", image);

    waitKey(0);

    return 0;
}
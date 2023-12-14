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
            int strongPixelCount = 0;

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
            for (int x = -threshold; x <= threshold; x++) {
                for (int y = -threshold; y <= threshold; y++) {
                    if (indicator[i * image.cols + j + y]) {
                        strongPixelCount++;
                    }
                }
            }

            if (isCorner && strongPixelCount >= threshold) {
                corners.push_back(Point2f(j, i));
                isCorner = false;
            }
        }
    }
}

int main() {
    // Read the image
    Mat image = imread("cub.png");

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    imshow("Origin", image);

    // Apply a bilateral filter to reduce noise
    Mat denoisedImage;

    //remove noise from image for efficiency
    bilateralFilter(grayImage, denoisedImage, 9, 75, 75);

    // Set the threshold for corner detection
    int threshold = 1;

    // Vector to store detected corners
    vector<Point2f> corners;

    // Detect corners using the FAST algorithm
    fastCornerDetection(denoisedImage, threshold, corners);

    // Copy the original image
    Mat imageCopy = image.clone();

    // Convert the vector of corners to a vector of KeyPoints
    vector<KeyPoint> keyPoints;
    for (const Point2f& point : corners) {
        KeyPoint keypoint;
        keypoint.pt = point;
        keyPoints.push_back(keypoint);
    }

    drawKeypoints(imageCopy, keyPoints, imageCopy);

    //Scalar(0, 0, 255)

    imshow("Corners", imageCopy);

    waitKey(0);

}

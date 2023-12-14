#include <opencv2/opencv.hpp>

int main() {
  // Read an image
  cv::Mat image = cv::imread("image.png");

  // Check if the image was read successfully
  if (!image.data) {
    std::cerr << "Error: Unable to read image" << std::endl;
    return -1;
  }

  // Display the image
  cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
  cv::imshow("Image", image);

  // Wait for a key press
  cv::waitKey(0);

  // Save the image

  return 0;
}
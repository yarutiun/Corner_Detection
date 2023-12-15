#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include "KLT.hpp"
#include "FAST.hpp"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    //Uncomment to test

    Klt algo;
    algo.KLT();
    // fast algo;
    // algo.fast_algo();
}

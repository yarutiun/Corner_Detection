#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

class Klt {
    public:
        Klt();
        ~Klt();
        void KLT(void);
};
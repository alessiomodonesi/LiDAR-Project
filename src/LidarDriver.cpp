#include <iostream>
#include <stdexcept>
#include <vector>

#include "LidarDriver.h"

LidarDriver::LidarDriver(double resolution)
    : angularResolution_{resolution}, buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angularResolution_) + 1))
{
    if (angularResolution_ >= 0.1 && angularResolution_ <= 1)
        resolution = angularResolution_;
    else
        throw InvalidArgument();
}

// member functions
void new_scan(std::vector<double> scan) {
    buffer[right_position] = scan;
}
std::vector<double> get_scan(void);
void clear_buffer(void);
double get_distance(double angle);

std::ostream &operator<<(std::ostream &out, const std::vector<double> &lastScan)
{
    for (double i : lastScan)
        out << i << " ";
}
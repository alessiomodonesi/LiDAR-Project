#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <cmath>

#include "LidarDriver.h"

// CONSTRUCTOR
LidarDriver::LidarDriver(double resolution)
    : angular_resolution_{resolution}, buffer_(BUFFER_DIM, std::vector<double>((RANGE / angular_resolution_) + 1))
{
    if (angular_resolution_ < 0.1 || angular_resolution_ > 1.0)
        throw std::invalid_argument("angular resolution must be [0.1°, 1.0°]");
    // std::cout << "angular resolution set to: " << angular_resolution_ << "°" << std::endl;
}

// MEMBER FUNCTIONS
void LidarDriver::new_scan(std::vector<double> scan)
{
    if (last_position_ != -1 && update_position(last_position_) == oldest_position_)
        oldest_position_ = update_position(oldest_position_);

    last_position_ = update_position(last_position_);

    // check scan values
    for (double i: scan){
        if (i < 0)
            throw std::invalid_value("found a invalid value, please check the correct positioning of the sensor");
    }

    if (scan.size() < (RANGE / angular_resolution_) + 1)
    {
        int i = 0;
        while (i < scan.size())
        {
            buffer_[last_position_][i] = scan[i];
            i++;
        }
        while (i < (RANGE / angular_resolution_) + 1)
        {
            buffer_[last_position_][i] = 0;
            i++;
        }
    }
    else if (scan.size() > (RANGE / angular_resolution_) + 1)
        for (int i = 0; i < (RANGE / angular_resolution_) + 1; i++)
            buffer_[last_position_][i] = scan[i];
    else
        buffer_[last_position_] = scan;
}

std::vector<double> LidarDriver::get_scan(void)
{
    std::vector<double> oldest_scan = buffer_[oldest_position_];
    buffer_[oldest_position_].clear();
    oldest_position_ = update_position(oldest_position_);
    return oldest_scan;
}

void LidarDriver::clear_buffer(void)
{
    for (int i = 0; i < BUFFER_DIM; i++)
        buffer_[i].clear();

    // reset variabili per gestione posizione
    last_position_ = -1;
    oldest_position_ = 0;
}

double LidarDriver::get_distance(double angle)
{
    return buffer_[last_position_][round_angle(angle) * (1 / angular_resolution_)];
}

// PRIVATE FUNCTIONS
int LidarDriver::count_numbers(void) {
    return static_cast<int>(std::log10(std::abs((RANGE / angular_resolution_) + 1))) + 1;
}

int LidarDriver::update_position(int position)
{
    if (position == (BUFFER_DIM - 1))
        position = 0;
    else
        position++;
    return position;
}

double LidarDriver::round_angle(double angle)
{
    double closest_angle = 0.0;
    double min_diff = 1.0;

    for (double i = 0; i <= RANGE; i += angular_resolution_)
    {
        double diff = std::abs(i - angle);
        if (diff < min_diff)
        {
            min_diff = diff;
            closest_angle = i;
        }
    }
    return closest_angle;
}

// HELPER FUNCTIONS
std::ostream &operator<<(std::ostream &os, LidarDriver obj)
{
    std::vector<double> scan = obj.buffer(obj.last_position());
    for (int i = 0; i < scan.size(); ++i)
    {
        os << "[" << std::setw(obj.count_numbers()) << i << "] = "
            << std::fixed << std::setprecision(2)
            << std::setw(7) << scan[i]
            << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, std::vector<double> scan)
{
    for (int i = 0; i < scan.size(); ++i)
    {
        os << "[" << std::setw(3) << i << "] = "
            << std::fixed << std::setprecision(2)
            << std::setw(7) << scan[i]
            << std::endl;
    }
    return os;
}
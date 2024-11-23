#include <iostream>
#include <stdexcept>
#include <vector>

#include "LidarDriver.h"

LidarDriver::LidarDriver(double resolution)
    : angular_resolution_{resolution}, buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angular_resolution_) + 1))
{
    if (angular_resolution_ < 0.1 || angular_resolution_ > 1)
        throw std::invalid_argument("angular resolution must be [0.1, 1]");
}

// member functions
void LidarDriver::new_scan(std::vector<double> scan) // memorizza nel buffer una scansione
{
    if (position != -1 && update_position(position) == oldest_position)
        oldest_position = update_position(oldest_position);

    position = update_position(position);
    buffer[position] = scan;
}

std::vector<double> LidarDriver::get_scan(void) // fornisce in output la scansione più vecchia e la rimuove dal buffer
{
    std::vector<double> oldest_scan = buffer[oldest_position];
    buffer[oldest_position].clear();
    return oldest_scan;
}

void LidarDriver::clear_buffer(void) {} // elimina tutte le scansioni senza restituirle

double LidarDriver::get_distance(double angle) // ritorna la lettura corrispondente a tale angolo
{
    return buffer[position][find_closest_angle(angle)];
}

int LidarDriver::update_position(int i)
{
    if (i == (BUFFER_DIM - 1))
        return i = 0;
    else
        return i++;
}

double LidarDriver::find_closest_angle(double angle)
{
    double closest_angle = 0.0;
    double min_diff = 1.0;

    for (int i = 0; i <= MAX_RANGE; i++)
    {
        double diff = std::abs(i - angle);
        if (diff < min_diff)
        {
            min_diff = diff;
            closest_angle = angle;
        }
    }

    return closest_angle;
}

// helper function
std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan)
{
    for (double i : last_scan)
        out << i << " ";
    return out;
}
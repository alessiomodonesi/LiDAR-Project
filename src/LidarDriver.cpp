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
        throw std::invalid_argument("angular resolution must be [0.1, 1]");
}

// member functions
void LidarDriver::new_scan(std::vector<double> scan) // memorizza nel buffer una scansione
{
    if (position != -1 && update_position(position) == oldest_position)
        oldest_position = update_position(oldest_position)
    position = update_position(position);
    buffer[position] = scan;
}

std::vector<double> LidarDriver::get_scan(void); // fornisce in output la scansione più vecchia e la rimuove dal buffer

void LidarDriver::clear_buffer(void);

double LidarDriver::get_distance(double angle) // ritorna la lettura corrispondente a tale angolo
{
    return buffer[position][find_closest_angle(angle)]; // elimina tutte le scansioni senza restituirle
}

int LidarDriver::update_position(int i)
{
    if (i == BUFFER_DIM - 1)
        i = 0;
    else
        i++;
    return i;
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

std::ostream &operator<<(std::ostream &out, const std::vector<double> &lastScan)
{
    for (double i : lastScan)
        out << i << " ";
}
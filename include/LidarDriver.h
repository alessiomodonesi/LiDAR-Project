#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <stdexcept>
#include <vector>

class LidarDriver
{

public:
    // constructors
    LidarDriver(void): buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angular_resolution) + 1)){} // default constructor
    LidarDriver(double new_resolution): buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angular_resolution) + 1)){} // costruttore con risoluzione angolare diversa da 1

    // member functions
    void new_scan(std::vector<double> scan); // memorizza nel buffer una scansione
    std::vector<double> get_scan(void);      // fornisce in output la scansione più vecchia e la rimuove dal buffer
    void clear_buffer(void);                 // elimina tutte le scansioni senza restituirle
    double get_distance(double angle) const; // ritorna la lettura corrispondente a tale angolo

private:
    const int BUFFER_DIM = 10;
    const int MAX_RANGE = 180;
    double angular_resolution{1}; // risoluzione angolare del sensore
    std::vector<std::vector<double>> buffer; // buffer con vector bidimensionale 
};

// helper function
std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);

#endif // LIDARDRIVER_H
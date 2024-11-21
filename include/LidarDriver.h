#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <stdexcept>

class LidarDriver
{

public:
    // constant variables
    const int BUFFER_DIM = 10;
    const int MAX_RANGE = 180;

    // constructors
    LidarDriver(void);                  // costruttore di default
    LidarDriver(double new_resolution); // costruttore con risoluzione angolare diversa da 1

    // member functions
    void new_scan(std::vector<double> scan); // memorizza nel buffer una scansione
    std::vector<double> get_scan(void);      // fornisce in output la scansione più vecchia e la rimuove dal buffer
    void clear_buffer(void);                 // elimina tutte le scansioni senza restituirle
    double get_distance(double angle) const; // ritorna la lettura corrispondente a tale angolo

private:
    double angular_resolution{1}; // risoluzione angolare del sensore
    std::vector<std::vector<double>> buffer(int BUFFER_DIM, std::vector<double>((MAX_RANGE / angular_resolution) + 1));
};

// helper function
std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);

#endif // LIDARDRIVER_H
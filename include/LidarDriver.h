#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>

class LidarDriver
{

public:
    // constructor
    LidarDriver(double resolution = defaultResolution) : buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angularResolution_) + 1)) {}

    // member functions
    void new_scan(std::vector<double> scan);                         // memorizza nel buffer una scansione
    std::vector<double> get_scan(void);                              // fornisce in output la scansione più vecchia e la rimuove dal buffer
    void clear_buffer(void);                                         // elimina tutte le scansioni senza restituirle
    double get_distance(double angle) const;                         // ritorna la lettura corrispondente a tale angolo
    int angularResolution(void) const { return angularResolution_; } // metodo get per la risoluzione

private:
    double angularResolution_;               // risoluzione angolare del sensore
    std::vector<std::vector<double>> buffer; // buffer con vector bidimensionale
    static constexpr int BUFFER_DIM = 10;    // dimensione del buffer
    static constexpr int MAX_RANGE = 180;    // range massimo del sensore
    static constexpr int defaultResolution = 1;
};

// helper function
std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);

#endif // LIDARDRIVER_H
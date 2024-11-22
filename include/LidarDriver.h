#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>

class LidarDriver
{

public:
    // constructor
    LidarDriver(void) : buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / angular_resolution_) + 1)) {}

    // member functions
    void new_scan(std::vector<double> scan);                            // memorizza nel buffer una scansione
    std::vector<double> get_scan(void);                                 // fornisce in output la scansione più vecchia e la rimuove dal buffer
    void clear_buffer(void);                                            // elimina tutte le scansioni senza restituirle
    double get_distance(double angle) const;                            // ritorna la lettura corrispondente a tale angolo
    int angularResolution(void) const { return angular_resolution_; }   // metodo get per la risoluzione

private:
    int position {-1};                              // posizione in cui è stata inserita l'ultima scansione
    int oldest_position {0};                        // posizione della scansione più vecchia
    double angular_resolution_{1};                  // risoluzione angolare del sensore
    std::vector<std::vector<double>> buffer;        // buffer con vector bidimensionale

    int update_position (int i);                    // restituisce correttamente la posizione successiva
    double find_closest_angle (double angle);       // trova l'angolo più vicino a quello passato come parametro in get_distance

    static constexpr int BUFFER_DIM = 10;           // dimensione del buffer
    static constexpr int MAX_RANGE = 180;           // range massimo del sensore
};

// helper function
std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);

#endif // LIDARDRIVER_H
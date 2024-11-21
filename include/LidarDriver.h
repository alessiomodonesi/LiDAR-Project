#include <iostream>
#include <vector>

const int BUFFER_DIM = 10;

class LidarDriver
{

public:
    LidarDriver(void);

    double new_scan(std::vector<double>);                 // memorizza nel buffer una scansione
    std::vector<double> get_scan();                       // fornisce in output la scansione più vecchia e la rimuove dal buffer
    void clear_buffer();                                  // elimina tutte le scansioni senza restituirle
    std::vector<double> get_distance(double angle) const; // ritorna la lettura corrispondente a tale angolo

private:
    int buffer_size{BUFFER_DIM};
    int scan_size{181};
};

std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);
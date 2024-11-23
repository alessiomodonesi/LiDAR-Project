#include <iostream>
#include <vector>
#include "LidarDriver.h"

std::vector<double> print_scan(int lower, int upper, int count)
{
    std::vector<double> scan;
    for (int i = 0; i < count; i++)
        scan[i] = (rand() % (upper - lower + 1)) + lower;

    return scan;
}

int main()
{
    // creazione di un oggetto LidarDriver
    LidarDriver default_lidar;

    // // simulazione di scansioni
    // std::vector<double> scan1 = print_scan(0, 2, 181);

    // // aggiunta delle scansioni al buffer
    // default_lidar.new_scan(scan1);

    // // recupero e stampa della scansione più vecchia
    // std::vector<double> oldest_scan = default_lidar.get_scan();
    // std::cout << "scansione più vecchia:" << std::endl;
    // std::cout << oldest_scan;

    // // recupero della distanza a un angolo specifico
    // double angle = 90.3;
    // std::cout << "distanza a " << angle << "°: " << default_lidar.get_distance(angle) << " m" << std::endl;

    // // pulizia del buffer
    // default_lidar.clear_buffer();
    // std::cout << "buffer pulito" << std::endl;
    return 0;
}
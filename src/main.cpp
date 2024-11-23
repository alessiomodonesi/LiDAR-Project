#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include "LidarDriver.h"

std::vector<double> print_scan(double min, double max, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribuzione(min, max);
    std::vector<double> random_numbers;

    for (int i = 0; i < n; ++i)
    {
        double numero = distribuzione(gen);
        numero = std::round(numero * 10000.0) / 10000.0;
        random_numbers.push_back(numero);
    }

    return random_numbers;
}

int main()
{
    // creazione di un oggetto LidarDriver
    LidarDriver default_lidar;

    // simulazione di scansioni
    std::vector<double> scan1 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan2 = print_scan(0.0, 2.0, 181);
    std::cout << "scan1: " << scan1 << std::endl;
    std::cout << "scan2: " << scan2 << std::endl;

    // imposta la risoluzione angolare del sensore

    // aggiunta delle scansioni al buffer
    default_lidar.new_scan(scan1);
    default_lidar.new_scan(scan2);

    // recupero e stampa della scansione più vecchia
    std::vector<double> oldest_scan = default_lidar.get_scan();
    std::cout << "scansione più vecchia:" << std::endl;
    std::cout << oldest_scan;

    // recupero della distanza a un angolo specifico
    double angle = 90.3;
    std::cout << "distanza a " << angle << "°: " << default_lidar.get_distance(angle) << " m" << std::endl;

    // pulizia del buffer
    default_lidar.clear_buffer();
    std::cout << "buffer pulito" << std::endl;
    return 0;
}
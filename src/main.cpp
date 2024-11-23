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
    LidarDriver second_lidar(0.5);

    for (int i = 0; i < 10; i++)
        default_lidar.new_scan(print_scan(0.0, 2.0, 181));

    // recupero e stampa della scansione più vecchia
    std::vector<double> oldest_scan1 = default_lidar.get_scan();
    std::cout << "\n scansione più vecchia:" << std::endl;
    std::cout << oldest_scan1;

    // std::vector<double> scan11 = print_scan(0.0, 2.0, 181);
    // default_lidar.new_scan(scan11);

    // // recupero e stampa della scansione più vecchia
    // std::vector<double> oldest_scan2 = default_lidar.get_scan();
    // std::cout << "2) scansione più vecchia:" << std::endl;
    // std::cout << oldest_scan2;

    // // recupero della distanza a un angolo specifico
    // double angle = 90.3;
    // std::cout << "distanza a " << angle << "°: " << default_lidar.get_distance(angle) << " m" << std::endl;

    // // pulizia del buffer
    // default_lidar.clear_buffer();
    // std::cout << "buffer pulito" << std::endl;
    return 0;
}
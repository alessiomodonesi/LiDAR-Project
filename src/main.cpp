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
    std::vector<double> scan3 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan4 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan5 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan6 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan7 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan8 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan9 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan10 = print_scan(0.0, 2.0, 181);
    std::vector<double> scan11 = print_scan(0.0, 2.0, 181);

    std::cout << scan1 << std::endl;
    std::cout << scan2 << std::endl;
    std::cout << scan3 << std::endl;
    std::cout << scan4 << std::endl;
    std::cout << scan5 << std::endl;
    std::cout << scan6 << std::endl;
    std::cout << scan7 << std::endl;
    std::cout << scan8 << std::endl;
    std::cout << scan9 << std::endl;
    std::cout << scan10 << std::endl;
    std::cout << scan11 << std::endl;

    // aggiunta delle scansioni al buffer
    default_lidar.new_scan(scan1);
    default_lidar.new_scan(scan2);
    default_lidar.new_scan(scan3);
    default_lidar.new_scan(scan4);
    default_lidar.new_scan(scan5);
    default_lidar.new_scan(scan6);
    default_lidar.new_scan(scan7);
    default_lidar.new_scan(scan8);
    default_lidar.new_scan(scan9);
    default_lidar.new_scan(scan10);

    // recupero e stampa della scansione più vecchia
    std::vector<double> oldest_scan = default_lidar.get_scan();
    std::cout << "1) scansione più vecchia:" << std::endl;
    std::cout << oldest_scan;

    default_lidar.new_scan(scan11);

    // recupero e stampa della scansione più vecchia
    std::vector<double> oldest_scan = default_lidar.get_scan();
    std::cout << "2) scansione più vecchia:" << std::endl;
    std::cout << oldest_scan;

    // recupero della distanza a un angolo specifico
    // double angle = 90.3;
    // std::cout << "distanza a " << angle << "°: " << default_lidar.get_distance(angle) << " m" << std::endl;

    // pulizia del buffer
    // default_lidar.clear_buffer();
    // std::cout << "buffer pulito" << std::endl;
    return 0;
}
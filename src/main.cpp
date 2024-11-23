#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

#include "LidarDriver.h"

// genera array di numeri casuali in un intervallo specificato
std::vector<double> print_scan(double min, double max, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> intervallo(min, max);
    std::vector<double> random_numbers;

    for (int i = 0; i < n; ++i)
    {
        double n = intervallo(gen);
        n = std::round(n * 10000.0) / 10000.0;
        random_numbers.push_back(n);
    }
    return random_numbers;
}

int main(int argc, char *argv[])
{
    // creazione di un oggetto LidarDriver
    LidarDriver default_lidar;
    LidarDriver second_lidar(0.5);
    // lancia std::invalid_argument
    // LidarDriver error_lidar(1.1);

    // riempimento del buffer di default_lidar
    for (int i = 0; i < 10; i++)
        default_lidar.new_scan(print_scan(0.0, 2.0, (180.0 / default_lidar.angular_resolution()) + 1));

    // riempimento del buffer di second_lidar
    for (int i = 0; i < 10; i++)
        second_lidar.new_scan(print_scan(0.0, 1.0, (180.0 / second_lidar.angular_resolution()) + 1));

    // recupero e stampa della scansione più vecchia di default_lidar
    std::vector<double> oldest_scan_1 = default_lidar.get_scan();
    std::cout << "\ndefault_lidar.get_scan():\n"
              << oldest_scan_1 << std::endl;

    // recupero e stampa della scansione più vecchia di second_lidar
    std::vector<double> oldest_scan_2 = second_lidar.get_scan();
    std::cout << "\nsecond_lidar.get_scan():\n"
              << oldest_scan_2 << std::endl;

    // test funzione circolare del buffer
    default_lidar.new_scan(print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1));

    // recupero e stampa della scansione più vecchia post buffer-testing
    std::vector<double> oldest_scan_3 = default_lidar.get_scan();
    std::cout << "\ndefault_lidar.get_scan():\n"
              << oldest_scan_3 << std::endl;

    // recupero della distanza ad un angolo specifico di default_lidar
    std::cout << "\ndistanza a " << 10.3 << "°: " << default_lidar.get_distance(10.3) << "m" << std::endl;
    std::cout << "\ndistanza a " << 10.6 << "°: " << default_lidar.get_distance(10.6) << "m" << std::endl;

    // recupero della distanza ad un angolo specifico di second_lidar
    std::cout << "\ndistanza a " << 10.1 << "°: " << second_lidar.get_distance(10.1) << "m" << std::endl;
    std::cout << "\ndistanza a " << 10.3 << "°: " << second_lidar.get_distance(10.3) << "m" << std::endl;

    // pulizia del buffer
    default_lidar.clear_buffer();
    std::cout << "\nbuffer pulito" << std::endl;

    // inserimento di una nuova scansione dopo la pulizia del buffer
    std::vector<double> post_clear_scan = print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1);
    default_lidar.new_scan(post_clear_scan);
    std::cout << "\nscan_post_clear:\n"
              << post_clear_scan << std::endl;

    // provo ad eliminarlo (l'unico scan presente)
    std::vector<double> oldest_post_clear_scan = default_lidar.get_scan();
    std::cout << "\ndefault_lidar.get_scan():\n"
              << oldest_post_clear_scan << std::endl;
    return 0;
}
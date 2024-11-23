#include <iostream>
#include <random>
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

    // simulazione di scansioni
    std::vector<double> scan1 = print_scan(0, 2, 181);

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
    std::cout << "buffer pulito" << std::endl;
    return 0;
}

// #include <iostream>
// #include <iomanip>
// #include <random>
// #include <vector>

// std::vector<double> generaNumeriCasuali(double min, double max, int n)
// {
//     // Crea un generatore di numeri casuali
//     std::random_device rd;                                          // Inizializza il generatore con una sorgente di casualità
//     std::mt19937 gen(rd());                                         // Mersenne Twister
//     std::uniform_real_distribution<double> distribuzione(min, max); // Distribuzione uniforme

//     std::vector<double> numeriCasuali;

//     for (int i = 0; i < n; ++i)
//     {
//         double numero = distribuzione(gen);
//         // Arrotonda a 4 cifre decimali
//         numero = std::round(numero * 10000.0) / 10000.0;
//         numeriCasuali.push_back(numero);
//     }

//     return numeriCasuali;
// }

// int main()
// {
//     double min = 1.0;  // Estremo inferiore
//     double max = 10.0; // Estremo superiore
//     int n = 5;         // Numero di elementi da generare

//     std::vector<double> numeri = generaNumeriCasuali(min, max, n);

//     std::cout << "Numeri casuali generati:" << std::endl;
//     for (double numero : numeri)
//     {
//         std::cout << std::fixed << std::setprecision(4) << numero << std::endl;
//     }

//     return 0;
// }
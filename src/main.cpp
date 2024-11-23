#include <iostream>
#include <vector>
#include "LidarDriver.h"

int main()
{
    try
    {
        // Creazione di un oggetto LidarDriver con una risoluzione angolare di 0.5
        LidarDriver lidar(0.5);

        // Simulazione di scansioni
        std::vector<double> scan1 = {1.0, 2.0, 3.0, 4.0, 5.0};
        std::vector<double> scan2 = {2.0, 3.0, 4.0, 5.0, 6.0};
        std::vector<double> scan3 = {3.0, 4.0, 5.0, 6.0, 7.0};

        // Aggiunta delle scansioni al buffer
        lidar.new_scan(scan1);
        lidar.new_scan(scan2);
        lidar.new_scan(scan3);

        // Recupero e stampa della scansione più vecchia
        std::vector<double> oldest_scan = lidar.get_scan();
        std::cout << "Scansione più vecchia:" << std::endl;
        std::cout << oldest_scan;

        // Recupero della distanza a un angolo specifico
        double angle = 2.0; // esempio di angolo
        double distance = lidar.get_distance(angle);
        std::cout << "Distanza a " << angle << " gradi: " << distance << " m" << std::endl;

        // Pulizia del buffer
        lidar.clear_buffer();
        std::cout << "Buffer pulito." << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    return 0;
}
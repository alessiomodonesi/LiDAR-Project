#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>

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
        n = std::round(n * 100.0) / 100.0;
        random_numbers.push_back(n);
    }
    return random_numbers;
}
 
// overload dell'operator per facilitare la fase di testing
std::ostream &operator<<(std::ostream &os, const std::vector<double> array)
{
    int size = array.size();
    int numbers = static_cast<int>(std::log10(std::abs(size))) + 1;
    for (int i = 0; i < array.size(); ++i)
    {
        os << "[" << std::setw(numbers) << i << "] = "
            << std::fixed << std::setprecision(2)
            << std::setw(7) << array[i]
            << std::endl;
    }
    return os;
}

int main(int argc, char *argv[])
{
    // creazione di un oggetto LidarDriver
    LidarDriver default_lidar;
    LidarDriver second_lidar(0.5);
    // lancia std::invalid_argument
    // LidarDriver error_lidar(1.1);

    // chiamata a get_scan() ma il buffer è vuoto, lancia std::invalid_argument
    // std::vector<double> empty_buffer = default_lidar.get_scan();

    // stampa di un oggetto di tipo LidarDriver vuoto, lancia std::bad_alloc
    // std::cout << default_lidar << std::endl;

    // riempimento del buffer di default_lidar
    for (int i = 0; i < 10; i++)
        default_lidar.new_scan(print_scan(0.0, 2.0, (180.0 / default_lidar.angular_resolution()) + 1));

    // riempimento del buffer di second_lidar
    for (int i = 0; i < 10; i++)
        second_lidar.new_scan(print_scan(0.0, 1.0, (180.0 / second_lidar.angular_resolution()) + 1));

    // recupero e stampa della scansione più vecchia di default_lidar
    std::vector<double> oldest_scan_1 = default_lidar.get_scan();
    std::cout << "\nrecupero e stampa della scansione più vecchia di default_lidar\n" << oldest_scan_1 << std::endl;

    // recupero e stampa della scansione più vecchia di second_lidar
    std::vector<double> oldest_scan_2 = second_lidar.get_scan();
    std::cout << "\nrecupero e stampa della scansione più vecchia di second_lidar\n" << oldest_scan_2 << std::endl;

    // test funzione circolare del buffer
    default_lidar.new_scan(print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1));

    // recupero e stampa della scansione più vecchia post buffer-testing
    std::vector<double> oldest_scan_3 = default_lidar.get_scan();
    std::cout << "\nrecupero e stampa della scansione più vecchia post buffer-testing\n" << oldest_scan_3 << std::endl;

    // recupero della distanza ad un angolo specifico di default_lidar
    std::cout << "\ndistanza a " << 10.3 << "°: " << default_lidar.get_distance(10.3) << "m" << std::endl;
    std::cout << "\ndistanza a " << 10.6 << "°: " << default_lidar.get_distance(10.6) << "m" << std::endl;

    // recupero della distanza ad un angolo specifico di second_lidar
    std::cout << "\ndistanza a " << 10.1 << "°: " << second_lidar.get_distance(10.1) << "m" << std::endl;
    std::cout << "\ndistanza a " << 10.3 << "°: " << second_lidar.get_distance(10.3) << "m" << std::endl;

    // recupero della distanza ad un angolo errato, lancia std::invalid_argument
    std::cout << "\ndistanza a " << 181.0 << "°: " << default_lidar.get_distance(181.0) << "m" << std::endl;

    // // pulizia del buffer
    // default_lidar.clear_buffer();
    // std::cout << "\nbuffer pulito" << std::endl;

    // // inserimento di una nuova scansione dopo la pulizia del buffer
    // std::vector<double> post_clear_scan = print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1);
    // default_lidar.new_scan(post_clear_scan);
    // std::cout << "\ninserimento di una nuova scansione dopo la pulizia del buffer\n" << post_clear_scan << std::endl;
    
    // // stampa di un oggetto di tipo LidarDriver
    // std::cout << "stampa di un oggetto di tipo LidarDriver\n" << default_lidar << std::endl;

    // // prova di eliminazione dello scan inserito post buffer clear
    // std::vector<double> oldest_post_clear_scan = default_lidar.get_scan();
    // std::cout << "\nprova di eliminazione dello scan inserito post buffer clear\n" << oldest_post_clear_scan << std::endl;
    
    // // caso in cui scan contiene meno valori del dovuto
    // default_lidar.new_scan(print_scan(0.0, 2.0, 134));
    // std::vector<double> incomplete_scan = default_lidar.get_scan();
    // std::cout << "\ncaso in cui scan contiene meno valori del dovuto\n" << incomplete_scan << std::endl;
    
    // // caso in cui scan contiene più valori del dovuto
    // default_lidar.new_scan(print_scan(0.0, 2.0, 201));
    // std::vector<double> too_much_value = default_lidar.get_scan();
    // std::cout << "\ncaso in cui scan contiene più valori del dovuto\n" << too_much_value << std::endl;
    
    // // caso in cui scan contiene anche valori negativi
    // std::vector<double> negative_value = print_scan(-0.5, 2.0, (180.0 / default_lidar.angular_resolution()) + 1);
    // int count_negative_value = 0;
    // for (int i = 0; i < negative_value.size(); i++)
    //     if (negative_value[i] < 0)
    //         count_negative_value++;

    // std::cout << "\nvector con valori negativi\n" << negative_value << std::endl;
    // std::cout << "\ntotale di valori negativi: " << count_negative_value << "\n" << std::endl;
    // default_lidar.new_scan(negative_value);
    // std::vector<double> s = default_lidar.get_scan();
    // std::cout << "\ncaso in cui scan contiene anche valori negativi\n" << s << std::endl;
    return 0;
}
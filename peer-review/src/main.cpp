
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/LidarDriver.h"
using namespace std;
int main()
{
	try {
	cout << "Hello, World!" << endl;
	LidarDriver lidar(20, 0.1);
	vector<double> vect;
	ifstream inputFile("../file/vector.txt");
	if (!inputFile.is_open())
	{
		cerr << "Impossibile aprire il file" << endl;
		return 1;
	}
	string line;
	while (getline(inputFile, line))
	{
		stringstream ss(line);
		string number;
		vect.clear();
		while (getline(ss, number, ','))
		{
			vect.push_back(stod(number));
		}
		lidar.new_scan(vect);
	}
	inputFile.close();
	cout << lidar << endl;
	cout << "Scansione piú vecchia" << endl;
	vector<double> last_scan = lidar.get_scan();
	for (double value : last_scan) {
		cout << value << " ";
	}
	cout << endl;
	cout << "Scansione piú vecchia" << endl;
	last_scan = lidar.get_scan();
	for (double value : last_scan) {
		cout << value << " ";
	}
	cout << endl;

	cout << "Lettura all'angolo 90" << endl;
	cout << lidar.get_distance(90) << endl;
	
	cout << "L' ultima scansione salvata" << endl;

	cout << lidar << endl;
	lidar.clear_buffer();
	
	cout << lidar << endl;
	} catch (const exception &e) {
		cerr << e.what();
	}
	return 0;
}

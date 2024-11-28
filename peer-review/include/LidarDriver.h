#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H
#include <vector>
#include <iostream>
using namespace std;

class LidarDriver{
	
private:
	const double risAngolare;
	const int BUFFER_DIM;
	const int LIST_DIM; // round(180/risAngolare)+1
	vector< vector<double> > BUFFER;
public:
	//constructor of class
	LidarDriver(const int BUFFER_DIM, const double risAngolare);
	void new_scan(vector<double> &v);
	vector<double> get_scan();
	void clear_buffer();
	double get_distance(const double &angle);
	friend ostream& operator<<(ostream& os,LidarDriver& lidar);
};
#endif //LIDARDRIVER_H
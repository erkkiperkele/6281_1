/* calculatePi.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <ctime>
#include <ratio>
#include <fstream>

using namespace std;
using namespace std::chrono;

bool FindIsInCircle(double x, double y);
void Print(double &duration);

int main()
{
	high_resolution_clock::time_point startTime = high_resolution_clock::now();

	int npoints = 1000000;
	int circle_count = 0;
	int i = 0;

	while(i< npoints)
	{
		double x = (double)rand() / (double)RAND_MAX;		
		double y = (double)rand() / (double)RAND_MAX;		
		bool isInCircle = FindIsInCircle(x, y);

		if (isInCircle)
		{
			++circle_count;
		}
		++i;
	}

	double PI = 4 * (double)circle_count / (double)npoints;

	cout << endl << "number of points: " << npoints << endl;
	cout << "value of Pi: " << PI << endl;

	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	double time_span = duration_cast<duration<double> >(endTime - startTime).count();
	cout << "Duration: " << time_span << " seconds" << endl;
	Print(time_span);

	return 0;
}

bool FindIsInCircle(double x, double y)
{
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	return distance < 1;
}


void Print(double &duration)
{
	std::ofstream myfile;
	myfile.open("./calculatePiOutput.csv", ios::app);
	myfile << "1," << duration << "\n";
	myfile.close();
}

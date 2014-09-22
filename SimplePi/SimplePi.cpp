/* SimplePi.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool FindIsInCircle(double x, double y);

int main()
{
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
}

bool FindIsInCircle(double x, double y)
{
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	return distance < 1;
}

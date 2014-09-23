/* ParallelPi.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

using namespace std;

bool FindIsInCircle(double x, double y);

int main(int argc, char* argv[])
{
	int mpiRank; 
	int mpiSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	int npoints = 1000000;
	int circle_count[mpiSize];
	int i = 0;
	int count = 0;
	circle_count[mpiRank] = 0;

	if (npoints % mpiSize != 0)
	{
		cout << endl << "please enter a multiple value of " << npoints << endl;
		return 1;
	}

	int num = npoints / mpiSize;

	//p = number of tasks
	//find out if I am MASTER or WORKER 


	while(i< num)
	{
		double x = (double)rand() / (double)RAND_MAX;		
		double y = (double)rand() / (double)RAND_MAX;		
		bool isInCircle = FindIsInCircle(x, y);

		if (isInCircle)
		{
			++circle_count[mpiRank];
		}
		++i;
	}

	if (mpiRank != 0)
	{
		//Every slave sends its result to root
		int source = 1;		
		while (source < mpiSize)
		{
			MPI_Send(&circle_count[mpiRank], mpiSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
			++source;
		}
	}

	if (mpiRank == 0)
	{
		int source = 1;
		while(source < mpiSize)
		{
			MPI_Recv(&circle_count[source], mpiSize, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			count += circle_count[source];
			++source;
		}

		count += circle_count[0];		//Adds master's result to the count of all points
		double PI = 4 * (double)count / (double)npoints;

		cout << endl << "circle_count[0]" << circle_count[0];
		cout << endl << "circle_count[1]" << circle_count[1];
		cout << endl << "circle_count[2]" << circle_count[2];
		cout << endl << "circle_count[3]" << circle_count[3];
		
		cout << endl << "count:" << count << endl;

		cout << endl << "number of points: " << npoints << endl;
		cout << "value of Pi: " << PI << endl;
	}

	MPI_Finalize();
	return 0;
}

bool FindIsInCircle(double x, double y)
{
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	return distance < 1;
}

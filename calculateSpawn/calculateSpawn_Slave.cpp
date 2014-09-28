/* calculateSpawn_Slave.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <fstream>

using namespace std;

bool FindIsInCircle(double x, double y);
void CalculateCircleCount(int &num, int &circle_count);

int main(int argc, char* argv[])
{
	int mpiRank; 
	int mpiSize;

	MPI_Comm master;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	MPI_Comm_get_parent(&master); 
	
	//TODO FROM HERE (cast and reduce)

	//Divide total amount of work between both master and slave processes
	//int num = npoints / mpiSize;
	//int rem = num + (npoints % mpiSize);
    	int num = atoi( argv[0] );
    	int rem = atoi( argv[1] );

	int send = 0;
	int recv = 0;

	CalculateCircleCount(num, send);
	MPI_Reduce(&send, &recv, 1, MPI_INT, MPI_SUM, 0, master);


	MPI_Finalize();
	return 0;
}

bool FindIsInCircle(double x, double y)
{
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	return distance < 1;
}

void CalculateCircleCount(int &num, int &count)
{
	int i = 0;
	while(i< num)
	{
		double x = (double)rand() / (double)RAND_MAX;
		double y = (double)rand() / (double)RAND_MAX;
		bool isInCircle = FindIsInCircle(x, y);
        
		if (isInCircle)
		{
			++count;
		}
		++i;
	}
}

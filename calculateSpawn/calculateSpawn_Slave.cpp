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
	
	cout << "SLAVE process # " << mpiRank << " / " << mpiSize << endl;
	cout << "argv[0]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	cout << "argv[2]: " << argv[2] << endl;

	int num;

	if (mpiRank == 0)
	{
		num = atoi( argv[2] );
	}
	else
	{
		num = atoi( argv[1] );
	}

	int send = 0;
	int recv = 0;


	CalculateCircleCount(num, send);
	cout << "Count: " << send << endl;

	//TODO: Reduce communication not working!!
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

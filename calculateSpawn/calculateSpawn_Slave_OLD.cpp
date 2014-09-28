/* calculateSpawn_Slave.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <fstream>

using namespace std;

void Print(int &nodes, double &duration);

int main(int argc, char* argv[])
{
	int mpiRank; 
	int mpiSize;

	MPI_Status status;
	MPI_Comm workercomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	
	double startTime = MPI_Wtime();


	int npoints = 1000000;
	int circle_count[mpiSize];
	int count = 0;

	//Create an array of 2 arguments. Second arg represents the number of points to be calculated by all slaves but one.
	//The first one represent the rest of the points to be calculated by the first slave.
	int slaveArgs[2];
	int slaveArgs[0] = num + (npoints % mpiSize);
	int slaveArgs[1] = npoints / mpiSize;

        int numworkers = atoi( argv[1] );
	MPI_Comm_spawn( "slave", slaveArgs, numworkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &workercomm, MPI_ERRCODES_IGNORE );
	
	//MPI_Bcast( b, SIZE, MPI_DOUBLE, MPI_ROOT, workercomm );

	//TODO FROM HERE (cast and reduce)
	
	int send = 0;
	int recv = 0;
	MPI_Reduce(&send, &recv, 1, MPI_INT, MPI_SUM, MPI_COMM_SELF, MPI_COMM_WORLD);

	double PI = 4 * (double)recv / (double)npoints;
	double endTime = MPI_Wtime();
	double duration = endTime - startTime;

	cout << "reduce result: " << recv << endl;
	cout << "number of points: " << npoints << endl;
	cout << "value of Pi: " << PI << endl;

	cout << endl << "Duration: " << duration << " seconds" << endl;
	Print(mpiSize, duration);

	MPI_Finalize();
	return 0;
}

void Print(int &nodes, double &duration)
{
        std::ofstream myfile;
	myfile.open("./calculateSpawnOutput.csv", ios::app);
	myfile << nodes << "\t" << duration << "\n";
	myfile.close();
}

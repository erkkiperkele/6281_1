/* calculateSpawn.cpp */

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

	MPI_Comm workercomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	
	double startTime = MPI_Wtime();

	int npoints = 1000000;

        int numworkers = atoi( argv[1] );
	MPI_Comm_spawn("calculateSpawn_Slave", MPI_ARGV_NULL, numworkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &workercomm, MPI_ERRCODES_IGNORE);
	
	//TODO FROM HERE (cast and reduce)

	int send = 0;
	int recv = 0;
	MPI_Reduce(&send, &recv, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	//MPI_Reduce(&amp;local_sum, &amp;global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

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

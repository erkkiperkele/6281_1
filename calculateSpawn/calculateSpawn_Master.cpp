/* calculateSpawn_Master.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

void Print(int &nodes, double &duration);

int main(int argc, char* argv[])
{
	cout << "--------- Starting SLAVE process ---------" << endl;

	int mpiRank; 
	int mpiSize;

	MPI_Comm workercomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

        int numworkers = atoi( argv[1] ); 		//Get the number of workers from command line arguments
	
	double startTime = MPI_Wtime();			//Starts chrono

	int npoints = 1000000;
	int num = npoints / numworkers;			//Number of points to be calculated per worker
	int rem = num + (npoints % numworkers);		//Number of points remaining to arrive to the total (npoints)

	//Instantiates 2 arguments to be passed to the slaves.
	char arg1[15];
	char arg2[15];
	
	snprintf(arg1,sizeof(arg1),"%d",num);		//1st argument: All but the 1st slave (0) will perform this number of operations
	snprintf(arg2,sizeof(arg2),"%d",rem);		//2nd argument: The 1st slave (0) will perform the same number of operations as others plus the remainder
	char* args[]={arg1,arg2,NULL};

	cout << "MASTER numString: " << args[1]<< endl;
	cout << "MASTER remString: " << args[0]<< endl;
	cout << "MASTER argv[0]: " << argv[0] << endl;
	cout << "MASTER argv[1]: " << argv[1] << endl;
	cout << "MASTER numWorkers: " << numworkers << endl;

	//Master spawns slave processes
	MPI_Comm_spawn("calculateSpawn_Slave", args, numworkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &workercomm, MPI_ERRCODES_IGNORE);

	int send = 0;
	int recv = 0;

	//Master reduces the slaves results to 1 value.
	MPI_Reduce(&send, &recv, 1, MPI_INT, MPI_SUM, MPI_ROOT, workercomm);

	double PI = 4 * (double)recv / (double)npoints;

	double endTime = MPI_Wtime();			//Pi calculation is over. Chrono stops.
	double duration = endTime - startTime;

	cout << "MASTER reduce result: " << recv << endl;
	cout << "MASTER number of points: " << npoints << endl;
	cout << "MASTER value of Pi: " << PI << endl;

	cout << endl << "MASTER Duration: " << duration << " seconds" << endl;
	Print(numworkers, duration);

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

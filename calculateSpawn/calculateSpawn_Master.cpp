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
	int mpiRank; 
	int mpiSize;

	MPI_Comm workercomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	
	double startTime = MPI_Wtime();

	int npoints = 1000000;
	int num = npoints / mpiSize;
	int rem = num + (npoints % mpiSize);
	

	//Creating arguments for slaves with the total amount of operations to be performed for the first slave, and the amount for all over slaves.
	char** args = new char*[2];

	std::ostringstream n,r;
	n << num;
	std::string numString(n.str());
	r << rem;
	std::string remString(r.str());


	args[1] = (char*)numString.c_str();
	args[0] = (char*)remString.c_str();
	//DO NOT CHECKIN:
	cout << "numString: " << args[1]<< endl;
	cout << "remString: " << args[0]<< endl;

	//char arg1[15];
	//char arg2[15];
	//snprintf(arg2,sizeof(arg2),"%d",arg[2]);
	//char* argsForKids[]={arg1,arg2,NULL};/


        //int numworkers = atoi( argv[0] );
	int numworkers = 10;
	
	//DO NOT CHECKIN
	cout << "numWorkers: " << numworkers << endl;
	MPI_Comm_spawn("calculateSpawn_Slave", args, numworkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &workercomm, MPI_ERRCODES_IGNORE);
	//MPI_Comm_spawn("calculateSpawn_Slave", MPI_ARGV_NULL, numworkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &workercomm, MPI_ERRCODES_IGNORE);
	
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

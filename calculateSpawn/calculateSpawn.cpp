/* calculateSpawn.cpp */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
#include <fstream>

using namespace std;

//TODO: Make it spawn!! (dumb copy of parallelPi at the moment)

bool FindIsInCircle(double x, double y);
void CalculateCircleCount(int &num, int* circle_count, int mpiRank);
void Print(int &nodes, double &duration);

int main(int argc, char* argv[])
{
	int mpiRank; 
	int mpiSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	
	double startTime = MPI_Wtime();

	int npoints = 1000000;
	int circle_count[mpiSize];
	int count = 0;

	//Divide total amount of work between both master and slave processes
	int num = npoints / mpiSize;
	int rem = num + (npoints % mpiSize); 
	
	circle_count[mpiRank] = 0;

	if (mpiRank != 0)
	{
		CalculateCircleCount(num, circle_count, mpiRank);
		MPI_Send(&circle_count, mpiSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	if (mpiRank == 0)
	{
		CalculateCircleCount(rem, circle_count, mpiRank);

		cout << endl << "circle_count[" << mpiRank
			<< "] " << circle_count[mpiRank] << " / "
			<< rem;
		count += circle_count[mpiRank];

		int source = 1;
		while(source < mpiSize)
		{
			MPI_Recv(&circle_count, mpiSize, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			count += circle_count[source];

			cout << endl << "circle_count[" << source
				<< "] " << circle_count[source] << " / "
				<< num;

			++source;
		}

		double PI = 4 * (double)count / (double)npoints;
		double endTime = MPI_Wtime();
		double duration = endTime - startTime;
		cout << endl << "count:" << count << endl;
		cout << "number of points: " << npoints << endl;
		cout << "value of Pi: " << PI << endl;

		cout << endl << "Duration: " << duration << " seconds" << endl;
		Print(mpiSize, duration);
	}

	MPI_Finalize();
	return 0;
}

bool FindIsInCircle(double x, double y)
{
	double distance = sqrt(pow(x, 2) + pow(y, 2));
	return distance < 1;
}

void CalculateCircleCount(int &num, int* circle_count, int slaveId)
{
	int i = 0;
	while(i< num)
	{
		double x = (double)rand() / (double)RAND_MAX;		
		double y = (double)rand() / (double)RAND_MAX;		
		bool isInCircle = FindIsInCircle(x, y);

		if (isInCircle)
		{
			++circle_count[slaveId];
		}
		++i;
	}
}
void Print(int &nodes, double &duration)
{
        std::ofstream myfile;
	myfile.open("./calculateSpawnOutput.csv", ios::app);
	myfile << nodes << "\t" << duration << "\n";
	myfile.close();
}

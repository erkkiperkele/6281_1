CC = mpic++
CFLAGS = -Wall
LIBS = -lmpi

all: calculateSpawn_Master calculateSpawn_Slave

calculateSpawn_Master : calculateSpawn_Master.cpp 
	$(CC) $(CFLAGS) -o calculateSpawn_Master calculateSpawn_Master.cpp $(LIBS)
clean : rm calculateSpawn_Master 

calculateSpawn_Slave : calculateSpawn_Slave.cpp
	$(CC) $(CFLAGS) -o calculateSpawn_Slave calculateSpawn_Slave.cpp $(LIBS)
clean : rm calculateSpawn_Slave

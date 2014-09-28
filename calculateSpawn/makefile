CC = mpic++
CFLAGS = -Wall
LIBS = -lmpi

calculateSpawn_Master : calculateSpawn_Master.cpp
	$(CC) $(CFLAGS) -o calculateSpawn_Master calculateSpawn_Master.cpp $(LIBS)
calculateSpawn_Slave : calculateSpawn_Slave.cpp
	$(CC) $(CFLAGS) -o calculateSpawn_Slave calculateSpawn_Slave.cpp $(LIBS)
clean : rm calculateSpawn_Master 
clean : rm calculateSpawn_Slave

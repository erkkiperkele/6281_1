CC = mpic++
CFLAGS = -Wall
LIBS = -lmpi

ParallelPi : ParallelPi.cpp
	$(CC) $(CFLAGS) -o ParallelPi ParallelPi.cpp $(LIBS)

#	if [ -d "/Users/Aymeric" ]; then \
#	codesign -v ./ParallelPi; \
#	fi;

clean : rm ParallelPi

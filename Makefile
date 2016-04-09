CC = g++
CFLAGS  = -std=c++11 -g -Wall

DES: DES.o 
	$(CC) $(CFLAGS) DES.o -o DES

DES.o: DES.cpp
	$(CC) $(CFLAGS) -c DES.cpp

clean:
	rm -f *.o
	rm -f DES

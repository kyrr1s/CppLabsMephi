CC=g++ -std=c++14
CFLAGS=-c -Wall
LDFLAGS=

all: exe

exe: main.o matrix_functions.o d_functions.o
	$(CC) main.o matrix_functions.o d_functions.o -o exe

main.o: main.cpp matrix_functions.h
	$(CC) $(CFLAGS) main.cpp

matrix_functions.o: matrix_functions.cpp matrix_functions.h
	$(CC) $(CFLAGS) matrix_functions.cpp

d_functions.o: d_functions.cpp d_functions.h
	$(CC) $(CFLAGS) d_functions.cpp

clean:
	rm -f *.o exe

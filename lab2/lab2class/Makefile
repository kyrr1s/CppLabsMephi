CC=g++ -std=c++20
CFLAGS=-c -Wall
LDFLAGS=

libarchspiral.a: classFunctions.o
	ar rc libarchspiral.a classFunctions.o
	ranlib libarchspiral.a
	cp archspiral.h ~/c++/lab2/lab2dialog
	cp libarchspiral.a ~/c++/lab2/lab2dialog
	cp archspiral.h ~/c++/lab2/lab2tests
	cp libarchspiral.a ~/c++/lab2/lab2tests

classFunctions.o: classFunctions.cpp archspiral.h
	$(CC) $(CFLAGS) classFunctions.cpp

clean:
	rm -f *.o *.a exe
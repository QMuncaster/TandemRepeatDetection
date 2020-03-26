CC=g++
CFLAGS=-Wall -pedantic --std=c++17

all: tr.o tr_fast.o tr_bf.o generate.o

tr.o:
	$(CC) $(CFLAGS) -o tr.o tr.cpp

tr_fast.o:
	$(CC) $(CFLAGS) -o tr_fast.o tr_fast.cpp

tr_bf.o:
	$(CC) $(CFLAGS) -o tr_bf.o tr_bf.cpp

generate.o:
	$(CC) $(CFLAGS) -o generate_random.o generate_random.cpp

clean:
	rm *.o
CC=g++
CFLAGS=-Wall -pedantic --std=c++17

all: tr.o tr_fast.o tr_bf.o generate_random.o

tr.o:
	$(CC) $(CFLAGS) -o tr.o src/tr.cpp

tr_fast.o:
	$(CC) $(CFLAGS) -o tr_fast.o src/tr_fast.cpp

tr_bf.o:
	$(CC) $(CFLAGS) -o tr_bf.o src/tr_bf.cpp

generate_random.o:
	$(CC) $(CFLAGS) -o generate_random.o test_generators/generate_random.cpp

clean:
	rm *.o
CC=g++
CFLAGS=-std=c++17

all: kdtree

kdtree: kdtree.cpp
	$(CC) $(CFLAGS) $^ -o $@.out 

clean:
	rm kdtree.out

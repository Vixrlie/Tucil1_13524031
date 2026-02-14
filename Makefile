CC = g++

all:
	$(CC) src/main.cpp -o bin/main;./bin/main

clean:
	rm -rf bin/*
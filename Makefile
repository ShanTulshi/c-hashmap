# Super simple Makefile

all: test

test: 
	gcc -g -o main-debug ./src/map.c ./src/hashes.c ./src/main.c

build: 
	gcc -o main ./src/map.c ./src/hashes.c ./src/main.c

clean:
	rm -r ./bin main*


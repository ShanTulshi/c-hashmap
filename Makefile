# Super simple Makefile

all: test

test: main-debug

main-debug: # bin/map.o bin/hashes.o
	clang -g -o main-debug ./src/map.c ./src/hashes.c ./src/main.c

bin/map.o: bin/hashes.o
	mkdir -p ./bin/
	clang -g -c -o ./bin/map.o ./src/map.c

# build: 
# 	mkdir -p ./bin/
# 	clang -o ./bin/main ./src/main.c

clean:
	rm -r ./bin main-debug main

bin/hashes.o:
	mkdir -p ./bin/
	clang -g -c -o ./bin/hashes.o ./src/hashes.h
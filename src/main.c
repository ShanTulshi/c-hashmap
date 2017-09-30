#include "map.h"
#include "hashes.h"

#include <stdio.h>

void * cc(void * in) {
	return in;
}

void d(void * in) {
	
}

int main(int argc, char * argv[]) {
	map * thing = map_create(&string_djb2, cc, d);
	map_set(thing, "abc", "def");
	printf("Hello, world!\n");
	map_destroy(thing);
	return 0;
}
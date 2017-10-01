#include "map.h"
#include "hashes.h"

#include <stdio.h>

void * cc(void * in) {
	return in;
}

void d(void * in) {
	
}

int main(int argc, char * argv[]) {
	map * thing = map_create(10, &string_djb2, cc, d);
	map_set(thing, "abc", "def");
	char * get = (char *) map_get(thing, "abc");
	printf("%s\t%p\n", get, get);
	printf("Hello, world!\n");
	map_destroy(thing);
	return 0;
}
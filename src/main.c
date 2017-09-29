#include "map.h"
#include "hashes.h"

#include <stdio.h>

int main(int argc, char * argv[]) {
	map * thing = map_create(&string_djb2);
	printf("Hello, world!\n");
	map_destroy(thing);
	return 0;
}
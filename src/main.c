#include "map.h"

int main(int argc, char * argv[]) {
	map * thing = map_create(&string_djb2);
	map_destroy(thing);
	return 0;
}
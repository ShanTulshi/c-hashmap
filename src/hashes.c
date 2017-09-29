#include "hashes.h"

unsigned long string_djb2(void * input) {
	assert(input);
	char * str = (char *) input;

	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

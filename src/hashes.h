#ifndef HASHES_H
#define HASHES_H

#include <assert.h>

/**
 * All hash functions must take in a void * and return an unsigned long
 */

typedef unsigned long (*hashfunc)(void * input);

/**
 * djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
 * found on https://stackoverflow.com/questions/7666509/hash-function-for-string
 */
unsigned long string_djb2(void * input) {
	assert(input);
	char * str = (char *) input;

	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

#endif
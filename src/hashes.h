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

unsigned long string_djb2(void * input);

#endif
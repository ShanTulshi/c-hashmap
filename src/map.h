#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <assert.h> 

#include "hashes.h"

/**
LINEAR PROBING hash table because building vectors in C is a bit much.
*/

// /**
//  * All hash functions must take in a void * and return an unsigned long
//  */

// typedef unsigned long (*hashfunc)(void * input);

// /**
//  * djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
//  * found on https://stackoverflow.com/questions/7666509/hash-function-for-string
//  */
// unsigned long string_djb2(void * input) {
// 	assert(input);
// 	char * str = (char *) input;

// 	unsigned long hash = 5381;
// 	int c;

// 	while ((c = *str++))
// 		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

// 	return hash;
// }

typedef struct {
    void * key;
	void * value;
} entry;

typedef struct {
    entry ** arr;
    size_t size;
    size_t n;
    hashfunc hash;
} map;


map * map_create(hashfunc f);

// DO NOT PASS NULL

int map_destroy(map * rip);

int map_insert(map * input, void * key, void * value);

int map_resize(map * input, size_t newsize);

void * map_get(map * input, void * key);

void * map_delete(map * input, void * key);

double map_load(map * input);

#endif
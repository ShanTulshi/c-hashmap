#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashes.h"

/**
LINEAR PROBING hash table because building vectors in C is a bit much.
*/

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
#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <assert.h> 

#include "hashes.h"

/**
LINEAR PROBING hash table because building vectors in C is a bit much.
Maps string -> void pointers
*/

// Copy constructor typedef
typedef void * (*cctor)(void *);

// Destructor typedef
typedef void (*dtor)(void *);

typedef struct {
    void * key;
	void * value;
} entry;

typedef struct {
    entry ** arr;
    size_t size;
    size_t n;
    hashfunc hash;
    cctor copy;
    dtor destroy;
} map;

// DO NOT PASS NULL

map * map_create(hashfunc f, cctor, dtor);

int map_destroy(map * rip);

int map_set(map * input, char * key, void * value);

int map_resize(map * input, size_t newsize);

void * map_get(map * input, char * key);

void * map_delete(map * input, char * key);

double map_load(map * input);

#endif
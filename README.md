# Fixed-size Map (in C)

This is an implementation of a fixed-size map in C (resizing coming soon!).

## Install Instructions

### Prerequisites

Make sure you have [`gcc`](https://gcc.gnu.org/) and [`make`](https://www.gnu.org/software/make/), and make sure the default C revision is C99 or later.

Run `make build` to create executable, modify `main.c` for tests.

## Types

```c
unsigned long (*hashfunc)(void *)
```
Hash functions are user-defined, the provided default is a popular string hash algorithm from [here](http://www.cse.yorku.ca/~oz/hash.html). Every hash function takes a `void *` and returns an `unsigned long`.

```c
void * (*cctor)(void *)
```
User-defined constructor for the arbitrary data the user wants to store.

```c
void (*dtor)(void *)
```
User-defined destructor for said arbitrary data. This, with the copy constructor, allow the map to manage its own copy of the data.

```c
struct entry
```
`entry` is a struct containing a `char * key` and a `void * value`.


```c
struct map
```
`map` contains an internal buffer of `entry` structs, along with references to the user-defined hash function, data copy constructor, and destructor. Also internally tracks size and number of items stored.

## Functions

```c 
map * map_create(size_t size, hashfunc f, cctor copy, dtor destroy)
```
Creates an instance for a map with a maximum of `size` items, hashes keys according to `f`, copies and destroys values with `copy` and `destroy`, respectively.

```c
void map_destroy(map * rip)
```
Destroys the map passed in, freeing all the data stored in it.

```c
int map_set(map * input, char * key, void * value)
```
Creates a new `entry` for the given `key`-`value` pair, and inserts it into map. In case of a duplicate `key`, deletes old entry and places new one in its place. If the map is full, returns `MAP_FULL`.

```c
void * map_get(map * input, char * key)
```
Retrieves value represented by `key` in the input map. Does not alter input map.

```c
void * map_delete(map * input, char * key)
```
Removes entry represented by `key` in `input`, and returns value contained.

```c
double map_load(map * input)
```
Returns the input map's load, defined as the number of entries stored in the map divided by the total size of the map.
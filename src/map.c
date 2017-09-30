#include "map.h"

#define START_SIZE 10       // START_SIZE > 1, preferably powers of two.
#define MAX_LOAD 0.8        // 0 < MAX_LOAD < 1

map * map_create(hashfunc func, cctor copy, dtor destroy) {
    map * ret = malloc(sizeof(map));
    ret->arr = (entry **) calloc(START_SIZE, sizeof(entry **));
    ret->size = START_SIZE;
    ret->n = 0;
    ret->hash = func;
    ret->copy = copy;
    ret->destroy = destroy;
    return ret;
}

int map_destroy(map * rip) {
    if(!rip)
        return 1;
    
    for(size_t i = 0; i < rip->size; i++) {
        if(rip->arr[i]) {
            
        }
        free(rip->arr[i]);
    }
    free(rip->arr);
    free(rip);
    return 0;
}

// Please be safe when calling on strings
int map_set(map * input, char * key, void * value) {
    // wrap key and value in struct
    entry * e = (entry *) malloc(sizeof(entry));
    char * k = (char *) malloc(strlen(key) + 1);
    *e = (entry) {strcpy(k, key), input->copy(value)};
    // find next closest open value
    size_t i = (size_t) input->hash(key);
    for(; input->arr[i % input->size]; i++) {
        // check if value already exists.
        if(strcmp(input->arr[i % input->size]->key, key) == 0) {
            // replace existing value, destroy old value.
            input->destroy(input->arr[i % input->size]->value);
            input->arr[i % input->size]->value = input->copy(value);
            return 0;
        }
    }
    // assign value and update size, resize if necessary.
    input->arr[i % input->size] = e;
    input->n ++;
    map_resize(input, input->n);
    return 0;
}

int map_resize(map * input, size_t newsize) {
    if((newsize < input->size / 2) || (newsize > input->size * MAX_LOAD) || (input->size - newsize < 2)) {
        entry ** ret = calloc(newsize, sizeof(entry **));
        for(size_t i = 0; i < input->size; i++) {
            if(input->arr[i]) {
                ret[input->hash(input->arr[i]->key) % newsize] = input->arr[i];
            }
        }
        free(input->arr);
        input->arr = ret;
    }
    return 0;
}

entry * map_get_entry(map * input, char * key) {
    size_t i0 = (size_t) input->hash(key);
    for(size_t i = 0; i < input->size; i++) {
        if(!strcmp(input->arr[(i0 + i) % input->size]->key, key))
            return input->arr[(i0 + i) % input->size];
    }
    return NULL;
}

void * map_get(map * input, char * key) {
    entry * ret = map_get_entry(input, key);
    if(ret)
        return ret->value;
    return NULL;
}

void * map_delete(map * input, char * key) {
    void * ret = map_get_entry(input, key);
    if(ret) {
        ret = ((entry *)ret)->value;
        free(ret);
        return ret;
    }
    return NULL;
}

double map_load(map * input) {
    return (double) input->n / input->size;
}
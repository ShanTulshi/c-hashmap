#include "map.h"

#define START_SIZE 10       // START_SIZE > 1, preferably powers of two.
#define MAX_LOAD 0.8        // 0 < MAX_LOAD < 1

/************* ENTRY UTILS **************/
entry * map_get_entry(map * input, char * key) {
    size_t i0 = (size_t) input->hash(key);
    for(size_t i = 0; i < input->size; i++) {
        printf("%lu\n", i0 + i);
        if(input->arr[(i0 + i) % input->size] && !strcmp(input->arr[(i0 + i) % input->size]->key, key))
            return input->arr[(i0 + i) % input->size];
    }
    return NULL;
}

entry * entry_create(map * input, char * key, void * value) {
    entry * ret = (entry *) malloc(sizeof(entry));
    ret->key = strdup(key);
    ret->value = input->copy(value);
    return ret;
}

void entry_destroy(map * input, entry * e) {
    if(e) {
        free(e->key);
        input->destroy(e->value);
        free(e);
    }
}

map * map_create(size_t size, hashfunc func, cctor copy, dtor destroy) {
    map * ret = malloc(sizeof(map));
    ret->arr = (entry **) calloc(size, sizeof(entry **));
    ret->size = size;
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
            entry_destroy(rip, rip->arr[i]);
        }
    }
    free(rip->arr);
    free(rip);
    return 0;
}

int map_set(map * input, char * key, void * value) {
    if(input->n == input->size) {
        return -1;
    }
    size_t i = input->hash(key) % input->size;
    for(; input->arr[i] && !strcmp(input->arr[i]->key, key); i = (i + 1) % input->size);
    // found the right index to replace
    entry_destroy(input, input->arr[i]);
    input->arr[i] = entry_create(input, key, value);
    input->n++;
    return 0;
}

// for the future!
// int map_resize(map * input, size_t newsize) {
//     if(((newsize > START_SIZE) && (newsize < input->size / 2)) || (newsize > input->size * MAX_LOAD) || (input->size - newsize < 2)) {
//         entry ** old = input->arr;
//         size_t oldsize = input->size;
//         input->arr = calloc(newsize, sizeof(entry **));
//         input->size = newsize;
//         input->n = 0;
//         for(size_t i = 0; i < oldsize; i++) {
//             if(old[i]) {
//                 map_set_entry(input, old[i]);
//             }
//         }
//         free(input->arr);
//         input->arr = ret;
//     }
//     return 0;
// }

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

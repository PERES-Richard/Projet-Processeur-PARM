#ifndef HASH_H
#define HASH_H

#include "list.h"

struct hash
{
    list_t *list;
    int size;
};

typedef struct hash *hash_t;

hash_t init();
int put(hash_t map, const char *key, void *value);
void *get(hash_t map, const char *key);
void reset(hash_t map);

int count(hash_t map);
int removeElement(hash_t map, const char *key);
int isEmpty(hash_t map);

#endif
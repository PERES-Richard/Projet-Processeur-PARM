#include "hash.h"
#include <stdlib.h>
#include <string.h>

static unsigned long hash(const char *s)
{
    char *str = strdup(s);
    unsigned long hash = 5381;
    for (; *str; str++)
        hash = ((hash << 5) + hash) + *str; // hash*33 + *str
    return hash;
}

hash_t init(int size)
{
    hash_t map = (hash_t)malloc(sizeof(struct hash));
    map->list = (list_t *)calloc(size, sizeof(list_t));
    map->size = size;
    return map;
}

int put(hash_t map, const char *key, void *value)
{
    int index = (int)((int)hash(key)) % map->size;
    return push_list(&map->list[index], key, value);
}

void *get(hash_t map, const char *key)
{
    int index = (int)((int)hash(key)) % map->size;
    return get_list(map->list[index], key);
}

void reset(hash_t map)
{
    for (int i = 0; i < map->size; i++)
    {
        if (map->list[i] != NULL)
            reset_list(map->list[i]);
    }
    free(map->list);
    free(map);
}

int count(hash_t map)
{
    int count = 0;
    for (int i = 0; i < map->size; i++)
    {
        count += size_list(map->list[i]);
    }
    return count;
}

int removeElement(hash_t map, const char *key)
{
    int index = (int)((int)hash(key)) % map->size;
    return remove_list(&map->list[index], key);
}

int isEmpty(hash_t map)
{
    return !count(map);
}
#include <string.h>
#include "split.h"
#include <stdlib.h>

split_t split_init(char *str, const char *token)
{
    split_t split = (split_t)malloc(sizeof(struct split));
    char **ptr = split->array;
    split->size = 0;
    for (char *sub = strtok(str, token); sub && ptr - split->array < 10; sub = strtok(NULL, token))
    {
        *ptr = sub;
        ptr++;
        split->size++;
    }
    return split;
}

char *get_string(split_t split, int i)
{
    return split->array[i];
}
void remove_split(split_t split)
{
    free(split);
}
#ifndef SPLIT_H
#define SPLIT_H

struct split
{
    char *array[20];
    int size;
};

typedef struct split *split_t;

split_t split_init(char *str, const char *token);
char *get_string(split_t split, int i);
void remove_split(split_t split);

#endif
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

list_t init_list()
{
    list_t list = NULL;
    return list;
}

int push_list(list_t *list, const char *key, void *value)
{
    if (*list == NULL)
    {
        *list = (list_t)malloc(sizeof(struct list));
        (*list)->key = strdup(key);
        (*list)->value = value;
        (*list)->next = NULL;
        return 1;
    }
    else if (!strcmp(key, (*list)->key))
    {
        return 0;
    }
    else
    {
        return push_list(&(*list)->next, key, value);
    }
}

void *get_list(list_t list, const char *key)
{
    if (list == NULL)
    {
        return NULL;
    }
    else if (!strcmp(list->key, key))
    {
        return list->value;
    }
    else
    {
        return get_list(list->next, key);
    }
}

void reset_list(list_t list)
{
    if (list == NULL)
        return;
    if (list->next != NULL)
    {
        reset_list(list->next);
    }
    free(list);
}

int size_list(list_t list)
{
    if (list == NULL)
        return 0;
    else
        return size_list(list->next) + 1;
}

int remove_list(list_t *list, const char *key)
{
    if (list == NULL)
        return 0;
    else if (!strcmp((*list)->key, key))
    {
        list_t next = (*list)->next;
        free((*list));
        *(list) = next;
        return 1;
    }
    else
    {
        return remove_list(&(*list)->next, key);
    }
}

void *peek_list(list_t list)
{
    if(list == NULL) return NULL;
    if(list->next == NULL)
        return list->value;
    else 
        return peek_list(list->next);
}
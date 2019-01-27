#ifndef LIST_H
#define LIST_H

struct list
{
    char *key;
    void *value;
    struct list *next;
};

typedef struct list *list_t;

list_t init_list();
int push_list(list_t *list, const char *key, void *value);
void *get_list(list_t list, const char *key);
void *peek_list(list_t list);
void reset_list(list_t list);

int size_list(list_t list);
int remove_list(list_t *list, const char *key);

#endif
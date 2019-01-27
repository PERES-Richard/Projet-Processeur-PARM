#include "data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

data_t* data(int addr, int size, char* content)
{
    int ctnt = 0;
    if(content[0] == '0' && content[1] == 'x')
    {
        ctnt = strtol(content, NULL, 16);
    }
    else
    {
        ctnt = strtol(content, NULL, 10);
    }
    data_t* data = (data_t*)malloc(sizeof(data_t));
    data->addr = addr;
    data->size = size;
    data->content = ctnt;
    return data;
}


void removeData(data_t* data)
{
    free(data);
}

data_t* dataFromLine(data_t* last, char* line)
{
    int addr;
    if(last == NULL) addr = 0;
    else addr = last->addr + 1;
    char* sizeChar = strtok(line, " ");
    char* content = strtok(NULL, " ");
    int size = 0;
    if(!strcmp(sizeChar, ".word"))
        size = 8;
    else if(!strcmp(sizeChar, "db"))
        size = 16;
    else
        size = 8;
    return data(addr, size, content);
}
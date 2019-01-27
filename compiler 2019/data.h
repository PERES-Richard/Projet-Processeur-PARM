#ifndef DATA_H
#define DATA_H

typedef struct 
{
    int addr;
    int size;
    int content;
} data_t;

data_t* data(int addr, int size, char* content);
void removeData(data_t* data);
data_t* dataFromLine(data_t* last, char* line);


#endif
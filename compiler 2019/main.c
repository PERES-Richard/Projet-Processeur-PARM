#include <stdio.h>
#include "asm.h"
#include "hash.h"
#include "data.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "alias.h"

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "No input file\n");
        return 1;
    }
    char *inName;
    char *outName = "a.out";

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-')
            inName = argv[i];
        else if (argv[i][1] == 'o' && i + 1 < argc)
            outName = strdup(argv[++i]);
    }

    FILE *in = fopen(inName, "r");
    if (in == NULL)
    {
        fprintf(stderr, "No such file or directory : %s\n", inName);
        return 2;
    }

    FILE *out = fopen(outName, "w+");

    if(out == NULL) { fprintf(stderr, "Fail to create %s file\n", outName); return 3;}

    char rline[255];

    hash_t inst = create();

    list_t datalist = init_list();
    hash_t alias = init(1000);

    int mode_data = 0;
    int mode_text = 0;

    fprintf(out, "v2.0 raw\n");

    int nbLine = 0;

    while (fgets(rline, 255, in) != NULL)
    {
        if(rline[0] == ';') continue;
        char* line = trim(strtok(rline, ";"));
        if(line == NULL || strlen(line) == 0 || *line == ';') continue;
        if(!strcmp(line, ".data"))
        {
             mode_data = 1;
             mode_text = 0;
        }
        else if(!strcmp(line, ".text"))
        {
             mode_data = 0;
             mode_text = 1;
        }
        else if(!strcmp(line, ".end")) continue;
        else
        {
            if(mode_data)
            {
                char* name = strtok(strdup(line), ":");
                void* last = peek_list(datalist);
                data_t* data;
                if(last == NULL) data = dataFromLine(NULL, strtok(NULL, ":"));
                else data = dataFromLine((data_t*)last, strtok(NULL, ":"));
                push_list(&datalist, name, data);
            }
            else if(mode_text)
            {
                if(strstr(line,  ":"))
                {
                    alias_t* aliasContent = (alias_t*)malloc(sizeof(alias_t));
                    char* nameAlias = strtok(strdup(line), ":");
                    aliasContent->name = nameAlias;
                    aliasContent->nbLine = nbLine;
                    put(alias, nameAlias, aliasContent);
                }
                else nbLine++;
            }
        }
    }

    nbLine = 0;

    fclose(in);
    in = fopen(inName, "r");

    while (fgets(rline, 255, in) != NULL)
    {
        if(rline[0] == ';') continue;
        char* line = strtok(trim(rline), ";");
        if(line == NULL || strlen(line) == 0) continue;
        if(!strcmp(line, ".data"))
        {
             mode_data = 1;
             mode_text = 0;
        }
        else if(!strcmp(line, ".text"))
        {
             mode_data = 0;
             mode_text = 1;
        }
        else if(!strcmp(line, ".end")) continue;
        else
        {
            if(mode_text)
            {
                if(!strstr(line,  ":"))
                {
                    uint16_t instruction = f_all(inst, line, datalist, alias);
                    fprintf(out, "%04x ", instruction);
                }
                else nbLine++;
            }
        }
    }

    reset(alias);
    reset(inst);
    reset_list(datalist);
    fclose(in);
    fclose(out);

    return 0;
}

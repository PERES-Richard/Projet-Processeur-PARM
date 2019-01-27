#include <stdio.h>
#include "asm.h"
#include "hash.h"
#include "data.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct
{
    int nbLine;
    char* name;
} alias_t;

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

void testWithFile(const char* inName, uint16_t expect[]) {
    FILE *in = fopen(inName, "r");
    if (in == NULL)
    {
        fprintf(stderr, "No such file or directory : %s\n", inName);
        exit(2);
    }

    char rline[255];

    hash_t inst = create();

    list_t datalist = init_list();
    hash_t alias = init(1000);

    int mode_data = 0;
    int mode_text = 0;

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

    int i=-1;
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
                    uint16_t expected = *(expect+(++i));
                    if(expected != instruction) {
                         fprintf(stderr,"Test failed : exepected '%04x' got '%04x' (line %d = '%s').\n", expected, instruction, i, line);
                         exit(3);
                    }
                }
                else nbLine++;
            }
        }
    }

    reset(alias);
    reset(inst);
    reset_list(datalist);
    fclose(in);
}


int main(int argc, char const *argv[])
{
    printf("Start testing...\n\n");
    const char *inName = "code_test2.asm"; // Version simple de toutes les instructions
    const char *inNameCond = "code_testB.asm"; // Version avec conditions (code Forum Assembleur)

    /** Valeurs attendus **/
    uint16_t expect[] = {
        0x07ff, // LSLS
        0x0fff, // LSRS
        0x17ff, // ASRS
        0x19ff, // ADDS
        0x1bff, // SUBS
        0x1dff, // ADDS
        0x1fff, // SUBS
        0x27ff, // MVS
        0x403f, // ANDS
        0x407f, // EORS
        0x40bf, // LSLS
        0x40ff, // LSRS
        0x413f, // ASRS
        0x417f, // ADCS
        0x41bf, // SBCS
        0x41ff, // RORS
        0x423f, // TST
        0x427f, // RSBS
        0x42bf, // CMP
        0x42ff, // CMN
        0x433f, // ORRS
        0x437f, // MULS
        0x43bf, // BICS
        0x43ff, // MVNS
        0x97ff, // STR
        0x9fff, // LDR
        0xb07f, // ADD
        0xb0ff  // SUB
    };

    uint16_t expectB[] = {
        0x9800,
        0x9901,
        0x4288,
        0xd406,
        0x9002,
        0xde07,
        0x9102
    };

    printf("Start test 1 :\n");
    testWithFile(inName, expect);      // Toutes les instructions
    printf("Test 1 : OK\n\n");

    /** TEST 3 (B) **/
    printf("Start test 2 : conditions\n");
    testWithFile(inNameCond, expectB);  // Avec conditions (code Forum Assembleur)
    printf("Test 2 : OK\n");


    printf("\nTest completed without error.\n");
    return 0;
}
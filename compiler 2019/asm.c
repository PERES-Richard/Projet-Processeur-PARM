#include "asm.h"
#include "split.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include "data.h"
#include "alias.h"

static int isImmFormat(const char *str)
{
    if ((str[0] == 'R' || str[0] == 'r') && isdigit(str[1]))
    {
        return 0;
    }
    return 1;
}

static void printBits(size_t const size, void const *const ptr)
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

static int containsImmediate(split_t split)
{
    for (int i = 1; i < split->size; i++)
    {
        if (isImmFormat(get_string(split, i)))
        {
            return 1;
        }
    }
    return 0;
}

uint16_t f_lsl(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");
    uint16_t value = 0;

    if (!containsImmediate(split))
    {
        uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

        value = 258 << 6;

        if (rdn > 7 || rm > 7)
            { printf("Error value too high"); exit(1); }

        rm = rm << 3;

        value |= rdn;
        value |= rm;
    }
    else
    {
        value = 0;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');
        uint16_t imm;

        if (atoi((char *)get_string(split, 3)) == 0 && strcmp("0", get_string(split, 3)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 3)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 3));
        }

        if (rd > 7 || rm > 7 || imm > 31)
            { printf("Error value too high"); exit(1); }

        imm = imm << 6;
        rm = rm << 3;

        value |= rd;
        value |= rm;
        value |= imm;
    }

    return value;
}

uint16_t f_lsr(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");
    uint16_t value = 0;

    if (!containsImmediate(split))
    {

        uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');
        value = 259 << 6;

        if (rdn > 7 || rm > 7)
            { printf("Error value too high"); exit(1); }

        rm = rm << 3;

        value |= rdn;
        value |= rm;
    }
    else
    {
        value = 1 << 11;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');
        uint16_t imm;

        if (atoi((char *)get_string(split, 3)) == 0 && strcmp("0", get_string(split, 3)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 3)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 3));
        }

        if (rd > 7 || rm > 7 || imm > 31)
            { printf("Error value too high"); exit(1); }

        imm = imm << 6;
        rm = rm << 3;

        value |= rd;
        value |= rm;
        value |= imm;
    }

    return value;
}
uint16_t f_asr(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    if (!containsImmediate(split))
    {
        uint16_t value = 260 << 6;

        uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

        if (rdn > 7 || rm > 7)
            { printf("Error value too high"); exit(1); }

        rm = rm << 3;

        value |= rdn;
        value |= rm;

        return value;
    }
    else
    {
        uint16_t value = 1 << 12;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');
        uint16_t imm;

        if (atoi((char *)get_string(split, 3)) == 0 && strcmp("0", get_string(split, 3)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 3)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 3));
        }

        if (rd > 7 || rm > 7 || imm > 31)
            { printf("Error value too high"); exit(1); }

        rm = rm << 3;
        imm = imm << 6;

        value |= rd;
        value |= rm;
        value |= imm;

        return value;
    }
}

uint16_t f_adds(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    if(split->size == 2) {
        
        uint16_t value = 352 << 7;

        uint16_t imm;
        if (atoi((char *)get_string(split, 1)) == 0 && strcmp("0", get_string(split, 1)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 1)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 1));
        }

        if (imm > 127)
            { printf("Error value too high"); exit(1); }


        value |= imm;

        return value;
    }

    if (!containsImmediate(split))
    {
        uint16_t value = 3 << 11;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rn = (uint16_t)(get_string(split, 2)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 3)[1] - '0');

        if (rd > 7 || rm > 7 || rn > 7)
            { printf("Error value too high"); exit(1); }

        rm = rm << 6;
        rn = rn << 3;

        value |= rd;
        value |= rm;
        value |= rn;

        return value;
    }
    else
    {
        uint16_t value = 14 << 9;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rn = (uint16_t)(get_string(split, 2)[1] - '0');

        uint16_t imm;

        if (atoi((char *)get_string(split, 3)) == 0 && strcmp("0", get_string(split, 3)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 3)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 3));
        }

        if (rd > 7 || imm > 7 || rn > 7)
            { printf("Error value too high"); exit(1); }

        imm = imm << 6;
        rn = rn << 3;

        value |= rd;
        value |= imm;
        value |= rn;

        return value;
    }
}

uint16_t f_subs(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    if(split->size == 2) {
        
        uint16_t value = 353 << 7;

        uint16_t imm;
        if (atoi((char *)get_string(split, 1)) == 0 && strcmp("0", get_string(split, 1)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 1)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 1));
        }

        if (imm > 127)
            { printf("Error value too high"); exit(1); }


        value |= imm;

        return value;
    }

    if (!containsImmediate(split))
    {
        uint16_t value = 13 << 9;

        uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rn = (uint16_t)(get_string(split, 2)[1] - '0');
        uint16_t rm = (uint16_t)(get_string(split, 3)[1] - '0');

        if (rd > 7 && rm > 7 && rn > 7)
            { printf("Error value too high"); exit(1); }

        rm = rm << 6;
        rn = rn << 3;

        value |= rd;
        value |= rm;
        value |= rn;

        return value;
    }
    else
    {
        uint16_t value = 15 << 9;

        uint16_t rn = (uint16_t)(get_string(split, 1)[1] - '0');
        uint16_t rd = (uint16_t)(get_string(split, 2)[1] - '0');

        uint16_t imm;

        if (atoi((char *)get_string(split, 3)) == 0 && strcmp("0", get_string(split, 3)) != 0)
        {
            imm = ((data_t *)get_list(datalist, get_string(split, 3)))->addr;
        }
        else
        {
            imm = (uint16_t)atoi(get_string(split, 3));
        }

        if (rd > 7 || imm > 7 || rn > 7)
            { printf("Error value too high"); exit(1); }

        imm = imm << 6;
        rn = rn << 3;

        value |= rd;
        value |= imm;
        value |= rn;

        return value;
    }
}

uint16_t f_mov(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 4 << 11;

    uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');

    uint16_t imm;
    if (atoi((char *)get_string(split, 2)) == 0 && strcmp("0", get_string(split, 2)) != 0)
    {
        imm = ((data_t *)get_list(datalist, get_string(split, 2)))->addr;
    }
    else
    {
        imm = (uint16_t)atoi(get_string(split, 2));
    }

    if (rd > 7 || imm > 255)
        { printf("Error value too high"); exit(1); }

    rd = rd << 8;

    value |= rd;
    value |= imm;

    return value;
}

uint16_t f_and(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 256 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_eor(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 257 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_adc(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 261 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_sbc(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 262 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_ror(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 263 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_tst(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 264 << 6;

    uint16_t rn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rn;
    value |= rm;

    return value;
}

uint16_t f_rsb(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 265 << 6;

    uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rd > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rd;
    value |= rm;

    return value;
}

uint16_t f_cmp(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 266 << 6;

    uint16_t rn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rn;
    value |= rm;

    return value;
}

uint16_t f_cmn(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 267 << 6;

    uint16_t rn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rn;
    value |= rm;

    return value;
}

uint16_t f_orr(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 268 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_mul(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 269 << 6;

    uint16_t rdm = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');
    uint16_t rdm2 = (uint16_t)(get_string(split, 3)[1] - '0');

    if (rdm > 7 || rm > 7 || rdm != rdm2)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdm;
    value |= rm;

    return value;
}

uint16_t f_bic(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 270 << 6;

    uint16_t rdn = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rdn > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rdn;
    value |= rm;

    return value;
}

uint16_t f_mvn(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 271 << 6;

    uint16_t rd = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t rm = (uint16_t)(get_string(split, 2)[1] - '0');

    if (rd > 7 || rm > 7)
        { printf("Error value too high"); exit(1); }

    rm = rm << 3;

    value |= rd;
    value |= rm;

    return value;
}

uint16_t f_b(char* line, list_t datalist, hash_t alias)
{
    char* conditionnal = strtok(strdup(line), " ");
    int cond = 0;
    if(!strcmp(conditionnal, "BEQ"))
        cond = 0;
    else if(!strcmp(conditionnal, "BNE"))
        cond = 1;
    else if(!strcmp(conditionnal, "BCS"))
        cond = 2;
    else if(!strcmp(conditionnal, "BCC"))
        cond = 3;
    else if(!strcmp(conditionnal, "BMI"))
        cond = 4;
    else if(!strcmp(conditionnal, "BPL"))
        cond = 5;
    else if(!strcmp(conditionnal, "BVS"))
        cond = 6;
    else if(!strcmp(conditionnal, "BVC"))
        cond = 7;
    else if(!strcmp(conditionnal, "BHI"))
        cond = 8;
    else if(!strcmp(conditionnal, "BLS"))
        cond = 9;
    else if(!strcmp(conditionnal, "BGE"))
        cond = 10;
    else if(!strcmp(conditionnal, "BLT"))
        cond = 11;
    else if(!strcmp(conditionnal, "BGT"))
        cond = 12;
    else if(!strcmp(conditionnal, "BLE"))
        cond = 13;
    else if(!strcmp(conditionnal, "BAL") || !strcmp(conditionnal, "B"))
        cond = 14;
    
    uint16_t value = 13 << 12;
    value |= cond << 8;
    char* aliasName = strtok(NULL, ", ");
    alias_t* element = (alias_t*)get(alias, aliasName);
    value |= element->nbLine;

    return value;
    
}

// Without SP
uint16_t f_str(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 18 << 11;

    uint16_t rt = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t imm;
    if (atoi((char *)get_string(split, 2)) == 0 && strcmp("0", get_string(split, 2)) != 0)
    {
        imm = ((data_t *)get_list(datalist, get_string(split, 2)))->addr;
    }
    else
    {
        imm = (uint16_t)atoi(get_string(split, 2));
    }

    if (rt > 7 || imm > 255)
        { printf("Error value too high"); exit(1); }

    rt = rt << 8;

    value |= rt;
    value |= imm;

    return value;
}

uint16_t f_ldr(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 19 << 11;

    uint16_t rt = (uint16_t)(get_string(split, 1)[1] - '0');
    uint16_t imm;
    if (atoi((char *)get_string(split, 2)) == 0 && strcmp("0", get_string(split, 2)) != 0)
    {
        imm = ((data_t *)get_list(datalist, get_string(split, 2)))->addr;
    }
    else
    {
        imm = (uint16_t)atoi(get_string(split, 2));
    }

    if (rt > 7 || imm > 255)
        { printf("Error value too high"); exit(1); }

    rt = rt << 8;

    value |= rt;
    value |= imm;

    return value;
}


uint16_t f_add(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 352 << 7;

    uint16_t imm;
    if (atoi((char *)get_string(split, 1)) == 0 && strcmp("0", get_string(split, 1)) != 0)
    {
        imm = ((data_t *)get_list(datalist, get_string(split, 1)))->addr;
    }
    else
    {
        imm = (uint16_t)atoi(get_string(split, 1));
    }

    if (imm > 127)
        { printf("Error value too high"); exit(1); }


    value |= imm;

    return value;
}


uint16_t f_sub(char *line, list_t datalist, hash_t alias)
{
    split_t split = split_init(line, ", ");

    uint16_t value = 353 << 7;

    uint16_t imm;
    if (atoi((char *)get_string(split, 1)) == 0 && strcmp("0", get_string(split, 1)) != 0)
    {
        imm = ((data_t *)get_list(datalist, get_string(split, 1)))->addr;
    }
    else
    {
        imm = (uint16_t)atoi(get_string(split, 1));
    }

    if (imm > 127)
        { printf("Error value too high"); exit(1); }


    value |= imm;

    return value;
}


hash_t create()
{
    hash_t map = init(100000);
    put(map, "LSLS", f_lsl);
    put(map, "LSRS", f_lsr);
    put(map, "ASRS", f_asr);
    put(map, "ADDS", f_adds);
    put(map, "SUBS", f_subs);
    put(map, "MOVS", f_mov);
    put(map, "ANDS", f_and);
    put(map, "EORS", f_eor);
    put(map, "ADCS", f_adc);
    put(map, "SBCS", f_sbc);
    put(map, "RORS", f_ror);
    put(map, "TST", f_tst);
    put(map, "RSBS", f_rsb);
    put(map, "CMP", f_cmp);
    put(map, "CMN", f_cmn);
    put(map, "ORRS", f_orr);
    put(map, "MULS", f_mul);
    put(map, "BICS", f_bic);
    put(map, "MVNS", f_mvn);
    put(map, "B", f_b);
// SP function
    put(map, "STR", f_str);
    put(map, "LDR", f_ldr);
    put(map, "ADD", f_add);
    put(map, "SUB", f_sub);

    return map;
}

uint16_t f_all(hash_t map, char *line, list_t datalist, hash_t alias)
{
    char* function = strtok(strdup(line), " ,");
    function_t f;
    if(*function != 'B' || !strcmp(function, "BICS"))
        f = get(map, function);
    else
        f = get(map, "B");
    return f(line, datalist, alias);
}
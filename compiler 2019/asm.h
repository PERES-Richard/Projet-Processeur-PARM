#ifndef ASM_H
#define ASM_H

#include <stdint.h>
#include "hash.h"

typedef uint16_t (*function_t)(char *line, list_t datalist, hash_t alias);

//TODO Complete list with other instruction
uint16_t f_lsl(char *line, list_t datalist, hash_t alias);
uint16_t f_lsr(char *line, list_t datalist, hash_t alias);
uint16_t f_asr(char *line, list_t datalist, hash_t alias);
uint16_t f_adds(char *line, list_t datalist, hash_t alias);
uint16_t f_subs(char *line, list_t datalist, hash_t alias);
uint16_t f_mov(char *line, list_t datalist, hash_t alias);
uint16_t f_and(char *line, list_t datalist, hash_t alias);
uint16_t f_eor(char *line, list_t datalist, hash_t alias);
uint16_t f_adc(char *line, list_t datalist, hash_t alias);
uint16_t f_sbc(char *line, list_t datalist, hash_t alias);
uint16_t f_ror(char *line, list_t datalist, hash_t alias);
uint16_t f_tst(char *line, list_t datalist, hash_t alias);
uint16_t f_rsb(char *line, list_t datalist, hash_t alias);
uint16_t f_cmp(char *line, list_t datalist, hash_t alias);
uint16_t f_cmn(char *line, list_t datalist, hash_t alias);
uint16_t f_orr(char *line, list_t datalist, hash_t alias);
uint16_t f_mul(char *line, list_t datalist, hash_t alias);
uint16_t f_bic(char *line, list_t datalist, hash_t alias);
uint16_t f_mvn(char *line, list_t datalist, hash_t alias);
uint16_t f_str(char *line, list_t datalist, hash_t alias);
uint16_t f_ldr(char *line, list_t datalist, hash_t alias);

hash_t create();
uint16_t f_all(hash_t map, char *line, list_t datalist, hash_t alias); //Function who call all function

#endif
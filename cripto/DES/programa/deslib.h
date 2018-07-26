#ifndef SSDES_LIB
#define SSDES_LIB

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void print_bin(uint32_t input, int num);
void print_bin6(uint8_t input);
void print_bin8(uint8_t input);
void print_bin16(uint16_t input);
uint8_t get_esquerda(uint16_t bloco);
uint8_t get_direita(uint16_t bloco);
void troca_valores(uint8_t *direita, uint8_t *esquerda);
uint8_t * cria_sub_chaves(uint16_t chave, int rounds);
uint8_t sub_chaves(uint16_t chave, int rounds);
uint8_t funcao_e (uint8_t direita);
uint8_t S_Box(uint8_t lado, int S);
uint8_t funcao_f(uint8_t direita, uint8_t subchave);
//Retorna o bloco de 12 bits
uint16_t leitura_de_chars(int leitura, int *contador, uint8_t primeiro, int *continua, char char_lido);
//Retorna bloco que será gravado em um arquivo
void bits_para_gravar(int leitura, FILE *f, uint16_t cifra, int continua);

#endif

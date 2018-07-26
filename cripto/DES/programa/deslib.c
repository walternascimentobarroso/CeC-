#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* S-Box */
static char s[2][16] = {{
    /* S1 */
    5, 2, 1, 6, 3, 4, 7, 0,
    1, 4, 6, 2, 0, 7, 5, 3
    },{
    /* S2 */
    4, 0, 6, 5, 7, 1, 3, 2,
    5, 3, 0, 7, 6, 2, 1, 4
    }
};

/* Usando esta função para testes, conferindo os valores corretos em binário */
void print_bin(uint32_t input, int num) {
    int i;
    for (i=0; i<num; i++) {
        uint32_t shift_byte = 0x01 << (num-1-i);
        if (shift_byte & input) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

//Gera uma sub-chave correspondente ao round atual
uint8_t sub_chaves(uint16_t chave, int rounds) {
    uint8_t subChaves = 0;
    uint32_t chave_extendida = 0;
    chave_extendida = chave << 9 | chave;
    subChaves = chave_extendida >> (10 - rounds%9);
    return subChaves;
}

uint8_t * cria_sub_chaves(uint16_t chave, int rounds) {
    int i;
    uint8_t * array = (uint8_t *) calloc (rounds, sizeof(uint8_t));
    for (i = 0; i < rounds; i++) {
        array[i] = sub_chaves(chave, i);
    }
    return array;
}

uint8_t funcao_e (uint8_t direita){
    int i;
    //mascara é 11000011
    uint8_t expansao = 0, aux = 0, mascara = 0xc3;

    expansao = direita << 2;
    aux = (direita << 6) >> 6;
    //2 primeiros e 2 últimos bits estão na posição correta
    expansao |= aux;
    expansao &= mascara;
    mascara = 4;
    aux = direita & mascara;
    expansao |= (aux << 1);
    expansao |= (aux << 3);
    mascara = 8;
    aux = direita & mascara;
    expansao |= (aux << 1);
    expansao |= (aux >> 1);
    return expansao;
}

uint8_t S_Box(uint8_t lado, int S){
    uint8_t linha = 0, coluna = 0, valor = 0;

    linha = lado >> 3;
    coluna = lado << 5;
    coluna >>= 5;

    if(linha == 0){
        valor = s[S][coluna];
    }
    else{
        valor = s[S][coluna+8];
    }
    return valor;
}

uint8_t funcao_f(uint8_t direita, uint8_t subchave){
    uint8_t expansao, direita_quatro = 0, esquerda_quatro = 0, valorS1 = 0, valorS2 = 0;
    expansao = funcao_e(direita) ^ subchave;
    //Dividir a expansão em chaves de 4 bits
    direita_quatro = (expansao << 4);
    direita_quatro >>= 4;
    esquerda_quatro = expansao >> 4;
    //Fazer a função S1-box e S2-box
    valorS1 = S_Box(esquerda_quatro, 0);
    valorS2 = S_Box(direita_quatro, 1);
    //Concatenar S1 com S2 e formar 6bits, resultado final em valorS1
    valorS1 <<= 3;
    valorS1 |= valorS2;

    return valorS1;
}

uint8_t get_esquerda(uint16_t bloco){
    return bloco >> 6;
}

uint8_t get_direita(uint16_t bloco){
    bloco <<= 10;
    return bloco >> 10;
}

void troca_valores(uint8_t *direita, uint8_t *esquerda) {
    uint16_t aux;
    aux = *direita;
    *direita = *esquerda;
    *esquerda = aux;
    return;
}

uint16_t leitura_de_chars(int leitura, int *contador, uint8_t primeiro, int *continua, char char_lido){
    uint16_t bloco = 0;
    static uint8_t segundo = 0;
    //leitura impar
    if (leitura%2 == 1){
        bloco |= primeiro;
        bloco <<= 8;
        if(*contador){
            segundo = char_lido;
            bloco |= segundo;
            (*contador)--;
        }
        else *continua = 0;
        bloco >>= 4;
    }
    //leitura par
    else{
        bloco = segundo << 12;
        bloco >>= 4;
        if (*continua)   bloco |= primeiro;
    }
    return bloco;
}

void bits_para_gravar(int leitura, FILE *f, uint16_t cifra, int continua){
    uint8_t gravar = 0;
    static uint16_t cifra_aux = 0, cifra_aux2= 0;

    if(leitura%2 == 1){
        gravar = cifra >> 4;
        cifra_aux = cifra << 12;
        cifra_aux >>= 12;
    }
    else{
        cifra_aux <<= 4;
        cifra_aux2 = cifra >> 8;
        gravar = cifra_aux | cifra_aux2;
        fputc(gravar, f);
        gravar = 0;
        gravar = (cifra << 12) >> 12;
    }
    if(continua)    fputc(gravar, f);
}

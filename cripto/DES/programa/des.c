#include "deslib.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE *f, *leitura_arquivo;
    int tamanho, leitura = 0, i = 0, continua = 1, rounds = 8, j = 0, contador = 0;
    char *input, primeiro, segundo, modo = 'c';
    uint16_t bloco, chave = 455, aux, cifra;
    uint8_t *sub_chave, esquerda, direita, direita_aux = 0, esquerda_aux = 0;

 	int inicio_tempo, fim_tempo; //declaração de variaveis 
    double tempo_usado; //declaração de variaveis
 	inicio_tempo = clock(); //iniciando a contagem do tempo
    if(argc < 2){
        FILE *read = fopen("README.md", "r");
        printf("#### LEIA O README:\n");
        while ((primeiro = fgetc(read)) != EOF){
            printf("%c", primeiro);
        }
        printf("\n");
        return 1;
    }
    switch (argc){
        case 5:
            rounds = atoi(argv[4]);
        case 4:
            chave = atoi(argv[3]);
        case 3:
            modo = (char)*argv[2];
        case 2:
            leitura_arquivo = fopen(argv[1], "r"); // Pega arquivo do argv[1] para criptografia ou descriptografia
    		if(leitura_arquivo == NULL){
    			printf("Nome de arquivo inválido.\n");
    			return 1;
    		}
    }

    //Gera sub-chaves. A quantidade de sub-chaves é baseada no número de rounds
    sub_chave = cria_sub_chaves(chave, rounds);

    //Descobre tamanho do arquivo para controle
    fseek (leitura_arquivo, 0, SEEK_END);
    tamanho = ftell(leitura_arquivo);
    fseek (leitura_arquivo, 0, SEEK_SET);

    //instancia o número de chars que precisará ler
    input = (char*)calloc(tamanho, sizeof(char));


    contador = tamanho;
    while(tamanho){
        input[j++] = fgetc(leitura_arquivo);
        tamanho --;
    }
    fclose(leitura_arquivo);
    input[j] = '\0';
    j = 0;

    //abre arquivo onde ficará arquivo criptografado ou descriptografado
    f = fopen("saida", "w");

    while(continua){
        leitura++;
        bloco = 0;

        primeiro = input[j++];
        if (!contador){
            if (leitura%2 == 1) break;
            continua = 0;
        }
        contador--;
        bloco = leitura_de_chars(leitura, &contador, primeiro, &continua, input[j]);
        if (continua && leitura%2 == 1) j++;

        //Colocar em direita os 6 bits menos significativos e em esquerda os 6 mais significativos
        esquerda = get_esquerda(bloco);
        direita = get_direita(bloco);

        //Começo do algoritmo DES aqui:
        for(i = 0; i < rounds; i++){
            esquerda_aux = direita;
            if (modo == 'c')     direita_aux = esquerda ^ funcao_f(direita, sub_chave[i]);
            else if (modo == 'd')   direita_aux = esquerda ^ funcao_f(direita, sub_chave[(rounds-1)-i]);
            direita = direita_aux;
            esquerda = esquerda_aux;
        }
        troca_valores(&direita, &esquerda);

        //Faz a cifra
        cifra = esquerda << 6;
        cifra |= direita;

        //separa em 8 bits e grava em um arquivo para ser descriptografado
        bits_para_gravar(leitura, f, cifra, continua);

    }
    fclose(f);

	fim_tempo = clock(); //finalizando a contagem  do tempo
	//guardo o valor da execução do sort
    tempo_usado = ((double) (fim_tempo - inicio_tempo)) / (double) CLOCKS_PER_SEC;
	if(modo == 'd') {
		printf("Arquivo decriptografado em: %f:\n", tempo_usado); //exibi o tempo de execução
	} else {
	    printf("Arquivo criptografado em: %f:\n", tempo_usado); //exibi o tempo de execução
	}
    return 0;
}

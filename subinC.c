#include <stdio.h>
#include <stdlib.h>
 
#define size(a) (sizeof(a))/(sizeof(a[0]))

static int anterior=0;

/**
 * Para melhorar o algoritmo, foi criado uma função especifica para impressão
 */
void imprimeResultado(int A[], int size) {
    for(int i = 0; i < size; i++)
        printf("%*d", 5, A[i]);
    printf("\n");
}

/**
 * vetor	= vetor de entrada
 * aux		= vetor auxiliar
 * t_vetor	= tamanho do vetor
 * t_aux	= tamanho do vetor até agora
 * soma		= soma até agora
 * cont		= contador
 * w		= soma a ser encontrada
 * anterior	= soma anterior a chamada
 */
void forcaBruta(int vetor[], int aux[], int t_vetor, int t_aux, int soma, int cont, int w) {
    if( w >= soma && soma > anterior) {
		anterior = soma;
		if(cont == t_vetor || w == soma) {
		    imprimeResultado(aux, t_aux);
		}
	}

    if( w == soma ) {
        forcaBruta(vetor, aux, t_vetor, t_aux-1, soma - vetor[cont], cont + 1, w);
    } else {
        for( int i = cont; i < t_vetor; i++ ) {
            aux[t_aux] = vetor[i];
            forcaBruta(vetor, aux, t_vetor, t_aux + 1, soma + vetor[i], i + 1, w);
        }
    }
}

/**
 * Por ter varios parametros e para manter a organização foi criado uma nova função
 */
void generateFuncFB(int vetor[], int t_vetor, int w) {
    int *aux = (int *)malloc(t_vetor * sizeof(int)); 
    forcaBruta(vetor, aux, t_vetor, 0, 0, 0, w);
    free(aux);
}
 
int main() {
    int cheques[] = {1,2,6,4,9,8};
    int tamanho = size(cheques);
	int w = 33;
    generateFuncFB(cheques, tamanho, w);
    return 0;
}

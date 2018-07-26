#include <stdio.h>
// Criando a enumeração:
// Permitindo a sua declaração como um tipo qualquer:
typedef enum boolean {
    true = 1, false = 0
} bool;
#define size(a) (sizeof(a))/(sizeof(a[0]))

bool f = false;

bool sumS(int v[],int tamanho, int somaDesejada, int somaAtual){
    if (somaAtual == somaDesejada) 
		return true;

    tamanho--;
    if (tamanho>=0){
		return sumS(v,tamanho,somaDesejada,somaAtual) || sumS(v,tamanho,somaDesejada,somaAtual+v[tamanho]); // Somei a posição atual (levo)
	} else
		return false;
}

int main() {
    int a[] = {1,2,6,4,9};
    int tam = size(a);
    int w = 10;
    if (sumS(a,tam,w, 0)) 
        printf("Soma encontrada em um subvetor\n");
    else
		printf("Soma NAO encontrada\n");
    
    return 0;
   
}

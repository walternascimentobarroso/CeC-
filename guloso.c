#include <stdio.h>

int selecaoAtividades(int s[], int f[], int n) {
	int i, j;

	//a primeira atividade selecionada
	i = 0;
	printf("%d", i);

	// Considerando o resto das atividades
	for (j = 1; j < n; j++) {
		//Se essa atividade tiver tempo de início maior ou igual ao
		//da atividade selecionada anteriormente, em seguida, selecione-a
		if (s[j] >= f[i]) {
			printf("%d", j);
			i = j;
		}
	}
}

int main() {
	return 0;
}

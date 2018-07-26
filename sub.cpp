#include <iostream>
#include <stdio.h>

using namespace std;

bool isSubsetSum(int set[], int n, int sum) {
	//The subset[i][j] will be true if there is subset of sub[0 .. j-1]
	//with sum equal to i
	bool subset[sum + 1][n + 1];

	// if sum is zero, answer is true
	for(int i = 0; i <= n; i++){
		subset[0][i] = true;
	}

	// if sum is not 0 and subset empty, then answer is false
	for(int i = 0; i <= sum; i++){
		subset[i][0] = false;
	}
	//fill the table in bottom up manner
	for(int i = 1; i <= sum; i++){
		for(int j = 1; j <= n; j++){
			subset[i][j] = subset[i][j-1];
			if(i >= set[j-1])
				subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
		}
	}

	//printing the table
	for (int i = 0; i <= sum; i++) {
		for (int j = 0; j <= n; j++) {
	//		printf ("i = %4d, j = %4d", i, j);
//			if(i%2 == 0)
			printf ("%4d", subset[i][j]);
		}
		printf("\n");
	}

	return subset[sum][n];
}

int main() {
	int cheques[] = {1,2,6,4,9};
	int w = 10;
	int n = sizeof(cheques)/sizeof(cheques[0]);
	if (isSubsetSum(cheques, n, w) == true)
		printf("Encontrou um subconjunto com uma soma dada\n");
	else
		printf("Nenhum subconjunto com determinada soma\n");
	return 0;
}

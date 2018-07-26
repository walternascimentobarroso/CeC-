#include <iostream>

using namespace std;

int knapsack(int valor[], int peso[], int cap, int n); /**Solução do problema da mochila**/

int main(){

    /**n - numero de itens, M - capacidade da mochila**/
    int M, n;
    
    cin >> n;
    cin >> M;

    /**v - valor associado ao item ni, p - peso associado ao item ni**/
    int v[n], p[n];

    for(int i = 0; i < n; i++){
        cin >> p[i];
    }

    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    int res = knapsack(v, p, M, n);

    cout << "Valor total: " << res << endl;

    return 0;
}

int knapsack(int v[], int p[], int M, int n){

    /**Armazenar o valor maximo para subproblemas menores e, posteriormente, solucionar o problema maior**/
    int valMax[n+1][M+1];

    /**Vetor para indicar os elementos selecionados, 1 indica que o elemento foi selecionado**/
    int choosen[n];
    choosen[0] = 0; //Inicializa o vetor com valor 0

    /**Inicia a coluna 0 e linha 0, com 0s, significando que para mochila de capacidade 0
        ou 0 itens na mochila, o valor máximo obtido é zero**/
    for(int i = 0; i <= M; i++){
        valMax[0][i]  = 0;
    }

    for(int i = 0; i <= n; i++){
        valMax[i][0] = 0;
    }

    /**Abordagem Bottom-up**/

    for(int i = 1; i <= n; i++){
        for(int w = 1; w <= M; w++){
            if(p[i-1] <= w){
                int max1 = v[i-1] + valMax[i-1][w - p[i-1]]; //Se o item i esta na solucao otima
                int max2 = valMax[i-1][w]; //Se o item i nao esta na solucao otima
                valMax[i][w] = (max1 > max2)?max1:max2;
            }
            else{ //o item i nao esta na solucao otima por nao caber na mochila
                valMax[i][w] = valMax[i-1][w];
            }
        }
    }

    int w = M, count = n;
    //cout << "Capacidade: " << w << endl;

    /**Laço para indicar os elementos que foram selecionados**/
    while(w >=0 && count > 0){
        if(p[count-1] <= M){
            //cout << "peso[" << count << "]" << p[count-1] << endl;
            if(valMax[count][w] == (v[count-1] + valMax[count-1][w - p[count-1]])){
                choosen[count-1] = 1;
                w -= p[count-1];
                //cout << "Capacidade: " << w << endl;
                count--;
            }else{
                choosen[count-1] = 0;
                count--;
            }
        }else{
            choosen[count-1] = 0;
            count--;
        }
    }

    cout << "Produtos escolhidos: ";

    for(int i = 0; i < n; i++){
        if(choosen[i])
            cout <<  i+1 << " ";
    }

    cout << endl;

    return valMax[n][M];
}

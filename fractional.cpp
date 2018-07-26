// Recebe como parametros o numero de objetos n, 
// o array de objetos com seus respectivos pesos e valores, 
// e a capacidade Capacidade da mochila
double mochilaFracionaria(int n, Object * obj, int Capacidade){
    double peso = 0.0; // Peso armazenado na mochila
    double total = 0.0; // Valor total armazenado na mochila
    int i;
 
    // Ordena os objetos com relacao a razao entre valor/peso
    // Complexidade O(n*log(n))
    qsort(obj, n, sizeof(Object), ratioCmp);
 
    // Coloca o maior numero de objetos de forma completa na mochila,
    // em ordem de razao valor/peso => Complexidade O(n)
    for(i=0; i<n; i++){
        // Caso nao seja possivel colocar o objeto atual na mochila, 
        // entao sai do laco
        if(obj[i].peso + peso > Capacidade) break; 
 
        obj[i].frac = 1.0; // Coloca todo o objeto i na mochila
        total += obj[i].value; // Atualiza o valor total na mochila
        peso += obj[i].peso; // Atualiza o peso total na mochila
    }
 
    // Se nem todos os objetos couberam na mochila,
    // coloca apenas uma fracao do melhor objeto, em termos de valor/peso, 
    //ainda nao considerado
    if(i < n){
         // Coloca apenas a fracao possivel do objeto i na mochila
        obj[i].frac = (Capacidade - peso)/(double)obj[i].peso;
        // Atualiza o valor total da mochila
        total += ((double) obj[i].value) * obj[i].frac; 
    }
 
    // retorna o valor total armazenado na mochila
    return total;
}


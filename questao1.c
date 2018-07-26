algoritmoFB(w, n) {
	max = 0;
	aux[n];
	continua = true;
	int i;

	while(continua) {
		valor = 0;

		for(i = 0; i < n; i++)
			valor=valor+x[i]*w[i]
		if(valor > w)
			valor = 0;
		else
			if(max < valor)
				max = valor;
				aux = x;
		soma(0);
	}

	return aux, max;
}

soma(p) {
	if(x[p] < 1)
		x[p] += 1;
	else
		if(p+1 < n)
			x[p] = 0;
			soma(p+1);
		else
			continua = false;
}

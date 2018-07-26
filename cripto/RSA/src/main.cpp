#include <iostream>
#include "RSA.cpp"

int main() {
	long nbits;
	int inicio_tempo, fim_tempo; //declaração de variaveis 
    double tempo_usado; //declaração de variaveis
 	
	cout << "Number of bits: ";
	cin >> nbits;

	string plaintext = readText("plaintext.txt");
	if (plaintext.empty()) {
		cout << "File not found!" << endl;
		return -1;
	}

	cout << "Generating keys..." << endl;
	RSA r(nbits);

	inicio_tempo = clock(); //iniciando a contagem do tempo
	cout << "Encrypting..." << endl;
	vector<ZZ> cipher = r.encrypt(plaintext);

	for (int i = 0; i < cipher.size(); ++i) {
		writeTextOnFile(cipher[i], "cipher.txt");
	}
	tempo_usado = ((double) (fim_tempo - inicio_tempo)) / (double) CLOCKS_PER_SEC;
	
	printf("Arquivo criptografado em: %f:\n", tempo_usado*-1); //exibi o tempo de execução

	inicio_tempo = clock(); //iniciando a contagem do tempo	
	cout << "Decrypting..." << endl;
	string decipher = r.decrypt(cipher);

	writeTextOnFile(decipher, "decipher.txt");
	cout << "Done!" << endl;
	cout << decipher << endl;
	tempo_usado = ((double) (fim_tempo - inicio_tempo)) / (double) CLOCKS_PER_SEC;
	
	printf("Arquivo decriptografado em: %f:\n", tempo_usado*-1); //exibi o tempo de execução
	// r.getAttributes();
	
	return 0;
}

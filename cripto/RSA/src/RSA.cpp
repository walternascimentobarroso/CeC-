#include "RSA.h"

RSA::RSA(long nbits) {
	generate_keys(nbits);
	clear_files();
}

RSA::~RSA() {
	publickey.kill();
	privatekey.kill();
	n.kill();
	phi.kill();
}


/* public */
vector<ZZ> RSA::encrypt(const string text) {
	vector<ZZ> out;
	for (int i = 0; i < text.size(); i++) {
		ZZ C, M;
		M = text[i];
		C = powerMod(M, this->publickey, this->n);
		out.push_back(C);
	}

	return out;
}

string RSA::decrypt(const vector<ZZ> v) {
	string out;
	for (int i = 0; i < v.size(); i++) {
		ZZ C, M;
		C = v[i];
		M = powerMod(C, this->privatekey, this->n);
		out += ZZtoi(M);
	}

	return out;
}

void RSA::getAttributes() {
	cout << "p: " << this->p << endl << endl;
	cout << "q: " << this->q << endl << endl;
	cout << "n: " << this->n << endl << endl;
	cout << "phi: " << this->phi << endl << endl;
	cout << "publickey: " << this->publickey << endl << endl;
	cout << "privatekey: " << this->privatekey << endl << endl;
}


/* private */
void RSA::generate_keys(long nbits) {
	do {
		do p = long_number_generator(nbits);
		while (!MillerRabin().isPrime(p));

		do q = long_number_generator(nbits);
		while (!MillerRabin().isPrime(q));

		n = p * q;
		phi = (p-1) * (q-1);
		publickey = publickey_generator();

	} while (mdc(phi, publickey) != 1);

	privatekey = privatekey_generator(publickey, phi);
	
	writeTextOnFile(publickey, "publickey.txt", 0);
	writeTextOnFile(privatekey, "privatekey.txt", 0);
}


// return e = 65537
ZZ RSA::publickey_generator() {
	ZZ e, a, b;
	a = 2;
	b = 16;
	e = Power(a, b) + 1;

	return e;
}

// return d = e^{-1} mod(phi)
ZZ RSA::privatekey_generator(const ZZ &e, const ZZ &phi) {
	ZZ d = inverseMod(e, phi);
	return d;
}

#include "Generator.cpp"

class BlumBlumShub {
public:
	long nbits;
	BlumBlumShub(long nbits);
	ZZ generate_number();
};

BlumBlumShub::BlumBlumShub(long nbits) {
	this->nbits = nbits;
}

ZZ BlumBlumShub::generate_number() {
	ZZ p, q;
	do p = large_prime_generator(nbits);
	while (p % 4 != 3);
	do q = large_prime_generator(nbits);
	while (q % 4 != 3);

	ZZ n, s;
	n = p*q;
	do s = RandomLen_ZZ(nbits);
	while (mdc(n, s) != 1);

	vector<ZZ> X;
	vector<bool> B;
	X.push_back((s*s) % n);

	for (int i = 1; i < nbits; ++i) {
		X.push_back(X[i-1]*X[i-1] % n);
		int bit = ZZtoi(X[i] & 1);
		B.push_back(bit);
	}

	ZZ num;
	for (int i = 0; i < B.size(); ++i) {
		ZZ j; j = i;
		num += Power(2, B[i]*j);
	}

	return num;
}

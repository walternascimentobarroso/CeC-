#include "Arithmetic.cpp"

class MillerRabin {
public:
	MillerRabin();
	bool isPrime(ZZ &n);

private:
	void factoring_number(ZZ &k, ZZ &q, const ZZ &n);
	ZZ witness(const ZZ &n);
};


MillerRabin::MillerRabin() {}

bool MillerRabin::isPrime(ZZ &n) {
	ZZ k, q, a;

	factoring_number(k, q, n);
	a = witness(n);

	if (IsOne(powerMod(a, q, n))) {
		return 1;
	}

	ZZ j;
	for (j = 0; j < k; j++) {
		ZZ t = Power(2, j) * q;
		if (powerMod(a, t, n) == n-1)
			return 1;
	}

	return 0;
}

void MillerRabin::factoring_number(ZZ &k, ZZ &q, const ZZ &n) {
	k = 0;
	while ((n-1) % Power(2, ++k) == 0);
	q = (n-1)/Power(2, --k);
}

// return {a, 1 < a < (n-1)}
ZZ MillerRabin::witness(const ZZ &n) {
	srand(time(NULL));
	long t = rand();
	ZZ random; random = t;
	ZZ a = random % (n-1) + 1;
	return a;
}
#include <NTL/ZZ.h>
#include <fstream>

using namespace std;
using namespace NTL;

// return res = a^b mod(n)
ZZ powerMod(const ZZ &A, const ZZ &B, const ZZ &n) {
	ZZ a = A;
	ZZ b = B;
	ZZ res; res = 1;

	while (b > 0) {
		if (IsOne(b&1)) {
			res = (res*a)%n;
		}
		b >>= 1;
		a = (a*a)%n;
	}

	return res;
}

// return res = a^b
ZZ Power(const ZZ &a, const ZZ &b) {
	ZZ A = a;
	ZZ B = b;
	ZZ res; res = 1;

	while (B > 0) {
		if (IsOne(B&1)) {
			res *= A;
		}
		B >>= 1;
		A *= A;
	}

	return res;
}

// return res = a^b
ZZ Power(const long a, const ZZ &b) {
	ZZ A; A = a;
	ZZ B = b;
	ZZ res; res = 1;

	while (B > 0) {
		if (IsOne(B&1)) {
			res *= A;
		}
		B >>= 1;
		A *= A;
	}

	return res;
}

ZZ mdc(const ZZ &A, const ZZ &B) {
	ZZ a, b, r;
	a = A;
	b = B;

	// switch
	if (a < b)
		a ^= b;	b ^= a;	a ^= b;

	r = a % b;
	while (r > 0) {
		a = b;
		b = r;
		r = a % b;
	}

	return b;
}

// y = b^{-1} mod(a)
ZZ inverseMod(const ZZ &number, const ZZ &modulo) {
	ZZ b = number;
	ZZ a = modulo;

	ZZ u, v, r, q, x, y, x_tmp, y_tmp;
	x=1, v=1, y=0, u=0;

	do {
		q = a / b;
		r = a % b;
		a = b; b = r;
		x_tmp = x; y_tmp = y;
		x = u; y = v;
		u = x_tmp - q*u;
		v = y_tmp - q*v;
	} while (b > 0);

	// make it positive
	while (y < 0) {
		y += modulo;	
	}

	return y;
}

long ZZtoi(const ZZ &z) {
	ofstream fout(".temp");
	fout << z << endl;
	ifstream fin(".temp");
	char buff[80];
	fin.getline(buff, 80);
	system("rm .temp");
	return atoi(buff);
}
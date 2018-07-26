#include <vector>
#include "MillerRabin.cpp"
#include "BlumBlumShub.cpp"
#include "read.cpp"

class RSA {
private:
	ZZ p, q;
	ZZ publickey;
	ZZ privatekey;
	ZZ n;
	ZZ phi;

public:
	RSA(long nbits);
	~RSA();
	vector<ZZ> encrypt(const string text);
	string decrypt(const vector<ZZ> v);
	void getAttributes();

private:
	void generate_keys(long nbits);
	ZZ publickey_generator();
	ZZ privatekey_generator(const ZZ &e, const ZZ &phi);
};
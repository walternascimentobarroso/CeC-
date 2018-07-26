
ZZ long_number_generator(long nbits) {
	ZZ random = RandomBits_ZZ(nbits);
	return random;
}

ZZ large_prime_generator(long nbits) {
	ZZ prime = long_number_generator(nbits);
	while (!MillerRabin().isPrime(prime)) {
		prime = long_number_generator(nbits);
	}

	return prime;
}


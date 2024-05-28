#include <math.h>   // sqrtl()
#include <stdlib.h> // malloc(), free(), bsearch()
#include "prime_check.h"

#define COPRIME(a,b) (gcd(a,b) == 1)
ulong gcd(ulong a, ulong b) {
	while(b != 0) {
		ulong rem = a%b;
		a = b; b = rem;
	}
	return a;
}

int comp_ulongs(const void* a, const void* b) {
	if(*(ulong*) a <  *(ulong*) b) return -1;
	if(*(ulong*) a == *(ulong*) b) return  0;
	/* else: a > b */              return  1;
}

bool found_divisor(const ulong n, const ulong* array, ulong final_val) {
	while(true) {
		ulong val = *array;
		if(n%val == 0) return true;
		if(val >= final_val) break;
		array++;
	}
	return false;
}

bool is_prime(const ulong n) {
	return is_prime_with_lvl(n, DEFAULT_SIEVE_LEVEL);
}

bool is_prime_with_lvl(const ulong n, const unsigned sieve_lvl) {

	if(n<2) return false;
	const ulong primes[] = { 2,3,5,7,11,13,17,19,23,29 };
	size_t primes_len = sizeof(primes) / sizeof(*primes);
	if(bsearch(&n, primes, primes_len, sizeof(*primes), comp_ulongs))
		return true;

	// Calculate both k and sieve_len at the same time
	size_t coprimes_size = 1;
	ulong k = 1;
	for(unsigned i = 0; i < sieve_lvl; i++) {
		// see Euler's totient function
		coprimes_size *= primes[i]-1;
		k             *= primes[i];
	}
	if(!COPRIME(n,k)) return false;

	// Declare and populate the sieve
	ulong* coprimes = malloc(sizeof(ulong) * coprimes_size);
	size_t index = 0;
	for(ulong i=2; index < coprimes_size; i++) {
		if(COPRIME(k,i)) {
			coprimes[index] = i;
			index++;
		}
	}

	// Do quick isqrt(n) checks on block boundaries at first,
	// and check each element only for the very last block
	// (a block fits if (k+1)<=root, thus as long as k<root)
	ulong root = (ulong) sqrtl((long double) n);
	for(ulong i=k; i<root; i+=k) {

		if(found_divisor(n, coprimes, i+1)) {
			free(coprimes);
			return false;
		}

		for(size_t j=0; j<coprimes_size; j++)
			coprimes[j] += k;
	}

	// Limit the last search to items <= root
	bool result = !found_divisor(n, coprimes, root);
	free(coprimes);
	return result;
}

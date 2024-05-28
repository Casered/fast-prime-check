#ifndef PRIME_CHECK_H
#define PRIME_CHECK_H

#include <stdbool.h>
#define ulong unsigned long long
#define DEFAULT_SIEVE_LEVEL 7

bool is_prime(const ulong n);
bool is_prime_with_lvl(const ulong n, const unsigned sieve_lvl);

#endif /* PRIME_CHECK_H */

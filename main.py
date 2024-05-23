#!/usr/bin/env python3
from math import isqrt, gcd
from functools import reduce
from itertools import takewhile
from operator import mul

def coprime(a: int, b: int) -> bool:
    return gcd(a,b) == 1

def is_prime(n: int, *, sieve_lvl: int = 4) -> bool:

    if n < 2: return False
    primes = [2,3,5,7,11,13,17,19,23,29]
    if n in primes: return True

    k = reduce(mul, primes[:sieve_lvl])
    if gcd(n,k) > 1: return False
    sieve = [ i for i in range(5,k+1) if coprime(k,i) ]

    # Do quick isqrt(n) checks on block boundaries at first,
    # and check each element only for the very last block
    # (a block fits if (k+1)<=root, thus as long as k<root)
    root = isqrt(n)
    for _ in range(k, root, k):
        if any(n%x == 0 for x in sieve):
            return False
        # pylint: disable = consider-using-enumerate
        for i in range(len(sieve)):
            sieve[i] += k

    # The more fine-grained final iteration
    return all(
        n%x != 0 for x in takewhile(
            lambda x: x <= root, sieve
        )
    )

# - - - - - - - - - - - - - - - - - - - #

def test_prime(p: int, expected_result: bool) -> None:
    result = is_prime(p)
    print(f"is_prime({p}) = {result} -> \033[0;",
          "92mCorrect" if result == expected_result else
          "91;40mError", "\033[0m", sep='')

def main() -> None:
    test_prime(1234576,    False)
    test_prime(1234577,     True)
    test_prime(1234578,    False)
    test_prime(1234567890, False)
    test_prime(1234567891,  True)
    test_prime(1234567892, False)

if __name__ == '__main__':
    main()

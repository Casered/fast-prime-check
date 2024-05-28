#include <stdio.h>   // printf()
#include "prime_check.h" // bool

void test_prime(ulong p, bool expected_result) {

	bool result = is_prime(p);
	const char* status = (result == expected_result) ?
	                     "92mCorrect" : "91;40mError";

	printf("is_prime(%llu) = %s -> \033[0;%s\033[0m\n",
	       p, result ? "true" : "false", status);
}

int main(void) {
	test_prime(2,  true);
	test_prime(27, false);
	test_prime(29, true);
	test_prime(1234576,    false);
	test_prime(1234577,     true);
	test_prime(1234578,    false);
	test_prime(1234567890, false);
	test_prime(1234567891,  true);
	test_prime(1234567892, false);
	test_prime(18014398509481951, true);
	return 0;
}

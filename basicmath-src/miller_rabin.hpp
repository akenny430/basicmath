#ifndef PRIME_H 
#define PRIME_H 

/**
 * @brief
 * Checks if a number is prime.
 * 
 * @param n number to test for prime.
 * 
 * @returns true if number is prime, else false.
 * 
 * @details
 * Implements Miller-Rabin prime tester with S=100 iterations.
 */
bool is_prime(int n);

#endif

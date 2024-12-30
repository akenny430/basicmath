#ifndef PRIME_H
#define PRIME_H

/**
 * @brief
 * Checks if number is prime using Miller-Rabin prime tester.
 *
 * @param n Number to test.
 * @param s Number of iterations.
 *
 * @returns
 * true if number is prime, false if number is not prime.
 */
bool miller_rabin(int n, int s) noexcept;

#endif

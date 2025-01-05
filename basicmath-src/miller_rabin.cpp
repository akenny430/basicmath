#include <cstdint>
#include <random>

#include "miller_rabin.hpp"

/**
 * @brief
 * Taking the mod of a product of two numbers, (a * b) mod n,
 * specific to non-negative integer inputs.
 *
 * @param a first number.
 * @param b second number.
 * @param n modulus.
 *
 * @returns uint64 representing (a * b) mod n.
 *
 * @details
 * This is fundamentally based on the reduction formula
 * (a * b) % n = ((a % n) * (b % n)) % n.
 * We then iteratively step through the binary representation of b.
 */
std::uint64_t mod_product(std::uint64_t a, std::uint64_t b, std::uint64_t n) noexcept
{
    std::uint64_t result = 0;

    // intermediate computation of a % n
    a %= n;

    // looping through all bits of b
    while (b)
    {
        // if least significant bit is active, add a to the result
        if (b & 1)
        {
            result = (result + a) % n;
        }

        // right bit shift b
        b >>= 1;

        // double a to prepare for the next bit of n
        a = (2 * a) % n;
    }

    return result;
}

/**
 * @brief
 * Taking the mod of an exponential number, a^b mod n,
 * specific to non-negative integer inputs.
 *
 * @param a base.
 * @param b power.
 * @param n modulus.
 *
 * @returns uint64 representing a^b mod n.
 *
 * @details
 * Implements `MODULAR-EXPONENTIATION` from Cormen, Section 31.6 Page 957.
 *
 * @note
 * In this code, there is a variable `c` that is commented out.
 * It is used in the loop invariant from the algorithm as presented by Cormen.
 * In other cases, it may be useful to track/store the value of `c`,
 * but for pure computation it is not necessary.
 */
std::uint64_t mod_exponentiation(std::uint64_t a, std::uint64_t b, std::uint64_t n) noexcept
{
    // setup
    // std::uint64_t c = 0;
    std::uint64_t d = 1;

    // holding bit to move through, has 1 in first bit place
    std::uint64_t bit_holder = 0b1000000000000000000000000000000000000000000000000000000000000000;

    // loop through all bits, will end once bit_holder is 0
    while (bit_holder)
    {
        // do this every step
        // c *= 2;
        d = mod_product(d, d, n);

        // if this bit is active, do extra
        if (b & bit_holder)
        {
            // c += 1;
            d = mod_product(d, a, n);
        }

        // shift bit
        bit_holder >>= 1;
    }
    return d;
}

/**
 * @brief
 * Checks if number is composite (i.e., not prime) or not.
 *
 * @param n Number to check.
 * @param a Random number used in algorithm. Must be in interval [1, n - 1].
 *
 * @returns true if number is composite, else false.
 *
 * @details
 * Implements `WITNESS` from Cormen, Section 31.8 Page 969.
 */
bool check_composite_from_witness(std::uint64_t n, std::uint64_t a) noexcept
{
    // figuring out what t and u have to be from n
    std::uint64_t u = n - 1;
    std::uint64_t t = 0;
    while (u % 2 == 0)
    {
        ++t;
        u /= 2;
    }

    // compute mod exponentiation a^u mod n
    std::uint64_t x0 = mod_exponentiation(a, u, n);
    std::uint64_t x1;

    // checking up to t
    for (std::uint64_t i = 0; i < t; ++i)
    {
        x1 = mod_product(x0, x0, n);
        if (x1 == 1 && x0 != 1 && x0 != n - 1)
        {
            return true;
        }
        x0 = x1;
    }
    return (x1 != 1);
}

/**
 * @brief Prime tester using Miller Rabin algorithm.
 *
 * @param n Number to test.
 * @param s Number of iterations to use in algorithm.
 *
 * @returns Status of number being prime.
 *
 * @details
 * Implements `MILLER-RABIN` from Cormen, Section 31.8 Page 970.
 */
bool miller_rabin(std::uint64_t n, int s) noexcept
{
    // false if number is even or less than 2
    if (n % 2 == 0 || n < 2)
    {
        return false;
    }

    // setting up random number generation for Unif(1, n - 1)
    std::random_device rand_dev;
    std::mt19937_64 rand_rng(rand_dev());
    std::uniform_int_distribution<std::uint64_t> rand_dist(1, n - 1);

    // looping through max number of iterations
    std::uint64_t a;
    for (int k = 0; k < s; ++k)
    {
        // generates new number
        a = rand_dist(rand_rng);

        // return false if number is composite
        if (check_composite_from_witness(n, a))
        {
            return false;
        }
    }

    // after s checks, returns true
    return true;
}

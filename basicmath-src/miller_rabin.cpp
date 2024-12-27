#include <stdexcept>
#include <stdlib.h>

#include "miller_rabin.hpp"

/**
 * @brief
 * Taking the mod of an exponential number, a^c mod n,
 * specific to integer inputs.
 * 
 * @param a base.
 * @param b limit of increments to c.
 * @param n modulus.
 * 
 * @returns integer representing a^c mod n.
 * 
 * @details
 * Implements `MODULAR-EXPONENTIATION` from Cormen, Section 31.6 Page 957.
*/
int mod_exponentiation(int a, unsigned b, int n) noexcept
{
    int c = 0; 
    int d = 1;
    for (unsigned k = 1 << 31; k > 0; k = k / 2)
    {
        c *= 2;
        d = ( d * d ) % n;
        if ( b & k )
        {
            c += 1;
            d = ( d * a ) % n;
        }
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
bool check_composite_from_witness(int n, int a) noexcept
{
    // figuring out what t and u have to be from n
    int m = n - 1;
    int t = 0;
    while (m % 2 == 0) 
    {
        ++t;
        m /= 2;
    }
    unsigned u = (unsigned)m;

    int x0 = mod_exponentiation(a, u, n); 
    int x1; 
    for (int i = 0; i < t; ++i) 
    { 
        x1 = (x0 * x0) % n; 
        if ( x1 == 1 && x0 != 1 && x0 != n - 1 )
        {
            return true;
        }
        x0 = x1; 
    } 
    return ( x1 != 1 );
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
bool miller_rabin(int n, int s) noexcept
{
    // false if number is even or less than 2
    if (n % 2 == 0 || n < 2) 
    { 
        return false;
    } 

    // looping through max number of iterations
    for (int k = 0; k < s; ++k)
    {
        // generates random number between 1 and n - 1
        int a = (rand() % ( n - 1 )) + 1;

        // return false if number is composite
        if (check_composite_from_witness(n, a))
        {
           return false;
        } 
    }
    return true;
}

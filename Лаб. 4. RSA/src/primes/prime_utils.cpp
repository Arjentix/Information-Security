/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "prime_utils.h"

#include <random>
#include <algorithm>

#include <boost/random.hpp>

namespace {

std::random_device device;
std::default_random_engine generator(device());

/**
 * @brief   Get the GCD of two numbers using modulus algorithm
 * 
 * @param   a   first number
 * @param   b   second number
 * @return  the GCD of a and b
 */
BigInteger GetGcdByModulus(BigInteger a, BigInteger b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }

    return std::max(a, b);
}

/**
 * @brief   Generate 256 bit random prime candidate
 * 
 * @return  prime candidate 
 */
BigInteger GeneratePrimeCandidate() {
    using boost::multiprecision::bit_set;

    const int kNumberOfBits = 256;

    using Generator = boost::random::independent_bits_engine<
        boost::random::mt19937, kNumberOfBits, BigInteger>;
    Generator generator(device());
    boost::random::uniform_int_distribution<BigInteger> distribution(
        0, BigInteger(1) << kNumberOfBits);

    BigInteger n = distribution(generator);

    // Setting first and last bits to 1
    bit_set(n, 0);
    bit_set(n, kNumberOfBits - 1);

    return n;
}

/**
 * @brief   Check if number is prime
 * 
 * @details Uses Miller-Rabin test
 * 
 * @param   n   number expected to be prime
 * @param   k   try count for Miller-Rabin test
 * 
 * @return  true    if n is prime
 * @return  false   if n is not prime
 */
bool IsPrime(const BigInteger& n, int k = 5) {
    if (n == 2 || n == 3) {
        return true;
    }
    if (n <= 1 || n % 2 == 0) {
        return false;
    }

    BigInteger s = 0;
    BigInteger r = n - 1;
    while ((r & 1) == 0) {
        s += 1;
        r /= 2;
    }

    std::uniform_int_distribution<BigInteger> distribution(2, n - 1);
    for (int i = 0; i < k; ++i) {
        BigInteger a = distribution(generator);
        BigInteger x = primes::ModPow(a, r, n);
        if ((x != 1) && (x != n - 1)) {
            BigInteger j = 1;
            while ((j < s) && (x != n - 1)) {
                x = primes::ModPow(x, BigInteger(2), n);
                if (x == 1) {
                    return false;
                }
                j += 1;
            }
            if (x != n - 1) {
                return false;
            }
        }
    }

    return true;
}

}  // namespace

namespace primes {

BigInteger RandomPrime() {
    BigInteger n = GeneratePrimeCandidate();
    while (!IsPrime(n)) {
        n = GeneratePrimeCandidate();
    }

    return n;
}

BigInteger FindRandomCoprime(const BigInteger& n) {
    std::uniform_int_distribution<BigInteger> distribution(1, n);

    BigInteger coprime = distribution(generator);
    while (GetGcdByModulus(coprime, n) != 1) {
        coprime = distribution(generator);
    }

    return coprime;
}

BigInteger FindModularMultiplicativeInverse(BigInteger a, BigInteger m) {
    BigInteger m0 = m;
    BigInteger y = 0;
    BigInteger x = 1;

    if (m == 1) {
        return 0;
    }

    while (a > 1) {
        // q is quotient
        BigInteger q = a / m;

        BigInteger t = m;

        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;

        // Update x and y
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}

}  // namespace primes

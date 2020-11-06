/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include "big_integer.h"

/**
 * @brief   Contains utilities that are useful when working with prime numbers
 */
namespace primes {

BigInteger RandomPrime();

BigInteger FindRandomCoprime(const BigInteger& n);

BigInteger FindModularMultiplicativeInverse(BigInteger n, BigInteger modulus);

/**
* @brief   Compute base^exp % modulus expression
* 
* @param   base    number to be powered
* @param   exp     power degree
* @param   modulus modulus
* 
* @return  the result of base^exp % modulus
*/
template <typename T>
T ModPow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }

    if (result < 0) {
        result = modulus + result;
    }

    return result;
}

}  // namespace primes

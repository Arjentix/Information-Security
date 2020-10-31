'''
@author: Polyakov Daniil
@mail: arjentix@gmail.com
@github: Arjentix
@date: 26.09.2020
@copyright: Copyright 2020 Polyakov Daniil
'''

import sys
import sympy

def get_safe_prime(prime_number):
    N = 2 * prime_number + 1
    if sympy.isprime(N):
        return N, sympy.primitive_root(N)
       


def main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <number of primes>')
        return

    print('{')
    first = True
    for i in range(1, int(sys.argv[1])):
        prime_number = sympy.prime(i)
        N = 2 * prime_number + 1
        if sympy.isprime(N):
            if not first:
                print(',')
            print(f'    {{{N}, {sympy.primitive_root(N)}}}', end='')
            first = False
    print('\n}')

if __name__ == '__main__':
    main()

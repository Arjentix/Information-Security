'''
@author: Polyakov Daniil
@mail: arjentix@gmail.com
@github: Arjentix
@date: 26.09.2020
@copyright: Copyright 2020 Polyakov Daniil
'''

import sys
import sympy

def get_primitive_root(prime_number):
    for num in range(1, prime_number):
        rests = []
        success = True
        for degree in range(1, prime_number):
            rest = pow(num, degree) % prime_number
            if rest not in rests:
                rests.append(rest)
            else:
                success = False
                break
        if success:
            return num
    return -1
       


def main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <number of primes>')
        return

    print('{')
    first = True
    for i in range(1, int(sys.argv[1])):
        if not first:
            print(',')
        prime_number = sympy.prime(i)
        primitive_root = get_primitive_root(prime_number)
        print(f'    {{{prime_number}, {primitive_root}}}', end='')
        first = False
    print('\n}')

if __name__ == '__main__':
    main()

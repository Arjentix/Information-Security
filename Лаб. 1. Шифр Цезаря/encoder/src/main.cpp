/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 10.09.20
 */

#include <iostream>
#include <fstream>
#include <random>

#include "caesar/encode.h"

int main(int argc, char** argv) {
    using namespace std;

    random_device r;
    default_random_engine generator(r());
    uniform_int_distribution<int> distribution(1, 32);
    int offset = distribution(generator); // Getting random offset
    cout << "Key = " << offset << endl;

    if (argc == 1) {
        caesar::Encode(offset);
    } else if (argc == 2) {
        wifstream input(argv[1]);
        caesar::Encode(offset, input);
    } else if (argc == 4 && string(argv[2]) == "-o") {
        wifstream input(argv[1]);
        wofstream output(argv[3]);
        caesar::Encode(offset, input, output);
        output << "lol" << endl;
    } else {
        cout << "Usage: " << argv[0] << " [file] [-o <output>]" << endl;
        return -1;
    }

    return 0;
}

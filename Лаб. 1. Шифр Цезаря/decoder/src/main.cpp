/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 13.09.2020
 */

#include <iostream>
#include <fstream>

#include "caesar/decode.h"

int main(int argc, char** argv) {
    using namespace std;

    if (argc == 2) {
        wifstream stats_input(argv[1]);
        caesar::Decode(stats_input);
    } else if (argc == 3) {
        wifstream stats_input(argv[1]);
        wifstream input(argv[2]);
        caesar::Decode(stats_input, input);
    } else if (argc == 5 && string(argv[3]) == "-o") {
        wifstream stats_input(argv[1]);
        wifstream input(argv[2]);
        wofstream output(argv[4]);
        caesar::Decode(stats_input, input, output);
    } else {
        cout << "Usage: " << argv[0]
             << " <stats_file> [file.encrypted] [-o <output>]" << endl;
        return -1;
    }

    return 0;
}

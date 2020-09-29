/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "caesar.h"

namespace caesar {

std::string Encode(std::string str, const int key) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalpha(str[i])) {
            continue;
        }

        int k = key % 26;

        if (isupper(str[i])) {
            str[i] += k;
            if (str[i] > 'Z') {
                str[i] = 'A' + (str[i] - 'Z') - 1;
            }
        } else {
            if ((str[i] + k > 'z') || (str[i] + k < 'a')) {
                k -= 'z' - str[i];
                str[i] = 'a' + k - 1;
            } else {
                str[i] += k;
            }
        }
    }

    return str;
}

std::string Decode(std::string str, const int key) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalpha(str[i])) {
            continue;
        }

        char enc = str[i] - key % 26;
        if (isupper(str[i])) {
            if (enc < 'A') {
                enc = 'Z' - (('A' - enc) - 1);
            }
        } else {
            if (enc < 'a') {
                enc = 'z' - (('a' - enc) - 1);
            }
        }

        str[i] = enc;
    }

    return str;
}

}  // namespace caesar

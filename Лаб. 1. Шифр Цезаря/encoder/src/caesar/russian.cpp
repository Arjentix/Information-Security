/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 12.09.20
 */

#include "russian.h"

namespace {

const int kCapitalPrefix = 208; // Prefix of russian capital letters
const int kCapitalACode = 144; // Value of 'А'
const int kCapitalYaCode = 175; // Value of 'Я'

const int kLowerAtoPePrefix = 208; // Prefix of russian lower letters between ['а', 'п']
const int kLowerACode = 176; // Value of 'а'
const int kLowerPeCode = 191; // Value of 'п'

const int kLowerErToYaPrefix = 209; // Prefix of russian lower letters between ['р', 'я']
const int kLowerErCode = 128; // Value of 'р'
const int kLowerYaCode = 143; // Value of 'я'

/**
 * @brief   Checks if value is in range [left, right]
 * 
 * @param   value   value to be checked
 * @param   left    left border
 * @param   right   right border
 * 
 * @return  true if value belongs to the range and false otherwise
 */
template<typename T>
bool ValueInRange(T value, T left, T right) {
    return value >= left && value <= right;
}

/**
 * @brief   Checks if UTF-8 char represents russian character between ['а', 'п']
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's belongs to range and false otherwise
 */
bool IsBetweenAandPe(const russian::Utf8Char& ch) {
    return ch.first == kLowerAtoPePrefix &&
           ValueInRange(static_cast<int>(ch.second), kLowerACode, kLowerPeCode);
}

/**
 * @brief   Checks if UTF-8 char represents russian character between ['р', 'я']
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's belongs to range and false otherwise
 */
bool IsBetweenErAndYa(const russian::Utf8Char& ch) {
    return ch.first == kLowerErToYaPrefix &&
           ValueInRange(static_cast<int>(ch.second), kLowerErCode, kLowerYaCode);
}

} // namespace

namespace russian {


bool IsCapitalLetter(const Utf8Char& ch) {
    return ch.first == kCapitalPrefix &&
           ValueInRange(static_cast<int>(ch.second), kCapitalACode, kCapitalYaCode);
}

Utf8Char NextCapital(Utf8Char capital_letter, int offset) {
    offset %= 33;

    if (!IsCapitalLetter({capital_letter.first, capital_letter.second + offset})) {
        capital_letter.second = kCapitalACode +
                                (offset - (kCapitalYaCode - capital_letter.second) - 1);
    } else {
        capital_letter.second += offset;
    }

    return capital_letter;
}

bool IsLowerLetter(const Utf8Char& ch) {
    return IsBetweenAandPe(ch) || IsBetweenErAndYa(ch);
}

Utf8Char NextLower(Utf8Char lower_letter, int offset) {
    offset %= 33;

    while (IsLowerLetter(lower_letter) &&
           !IsLowerLetter({lower_letter.first, lower_letter.second + offset})) {
        if (IsBetweenAandPe(lower_letter)) {
            lower_letter.first = kLowerErToYaPrefix;
            offset -= (kLowerPeCode - lower_letter.second) + 1;
            lower_letter.second = kLowerErCode;
        } else if (IsBetweenErAndYa(lower_letter)) {
            lower_letter.first = kLowerAtoPePrefix;
            offset -= (kLowerYaCode - lower_letter.second) + 1;
            lower_letter.second = kLowerACode;
        }
    }

    lower_letter.second += offset;

    return lower_letter;
}

} // namespace russian

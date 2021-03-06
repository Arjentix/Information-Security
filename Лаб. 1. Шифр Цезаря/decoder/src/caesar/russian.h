/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 12.09.20
 */

#pragma once

#include <utility>

namespace russian {

using Utf8Char = std::pair<wchar_t, wchar_t>;

struct Utf8CharCompare {
    bool operator()(const Utf8Char& left, const Utf8Char& right) const;
};

/**
 * @brief   Checks if UTF-8 char represents a capital russian letter
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's capital russian letter and false otherwise
 */
bool IsCapitalLetter(const Utf8Char& ch);

/**
 * @brief   Coverts lower russian letter to capital
 * 
 * @param   ch  lower letter
 * 
 * @return  the same letter, but in capital register
 */
Utf8Char ToCapital(const Utf8Char& ch);


/**
 * @brief   Checks if UTF-8 char represents russian lower letter
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's russian lower letter and false otherwise
 */
bool IsLowerLetter(const Utf8Char& ch);

/**
 * @brief   Gets previous russian lower letter
 * 
 * @param   lower_letter    lower letter to begin
 * @param   offset          number of steps
 * 
 * @return  lower letter in offset steps back
 */
Utf8Char PrevLower(Utf8Char lower_letter, int offset);

/**
 * @brief   Coverts capital russian letter to lower 
 * 
 * @param   ch  capital letter
 * 
 * @return  the same letter, but in lower register
 */
Utf8Char ToLower(const Utf8Char& ch);


/**
 * @brief   Finds number of steps from first letter to second
 * 
 * @param   first   letter to begin steps
 * @param   second  letter to end steps
 * 
 * @return  number of steps from first to second
 */
int Diff(const Utf8Char& first, const Utf8Char& second);

} // namespace russian

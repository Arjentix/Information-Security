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

/**
 * @brief   Checks if UTF-8 char represents a capital russian letter
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's capital russian letter and false otherwise
 */
bool IsCapitalLetter(const Utf8Char& ch);

/**
 * @brief   Gets next russian capital letter
 * 
 * @param   capital_letter  capital letter to begin
 * @param   offset          number of steps
 * 
 * @return  capital letter in offset steps
 */
Utf8Char NextCapital(Utf8Char capital_letter, int offset);


/**
 * @brief   Checks if UTF-8 char represents russian lower letter;
 * 
 * @param   ch   UTF-8 char (pair of wide chars)
 * 
 * @return  true if it's russian lower letter and false otherwise
 */
bool IsLowerLetter(const Utf8Char& ch);

/**
 * @brief   Gets next russian lower letter
 * 
 * @param   lower_letter    lower letter to begin
 * @param   offset          number of steps
 * 
 * @return  lower letter in offset steps
 */
Utf8Char NextLower(Utf8Char lower_letter, int offset);

} // namespace russian

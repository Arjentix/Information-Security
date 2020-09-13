/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 10.09.20
 */

#pragma once

#include <iostream>

namespace caesar {

/**
 * @brief   Encodes all input characters with Caesar's cipher
 * 
 * @param   offset  offset for Caesar's cipher
 * @param   input   stream of input characters
 * @param   output  output stream
 */
void Encode(int offset, std::wistream& input = std::wcin, std::wostream& output = std::wcout);

} // namespace caesar

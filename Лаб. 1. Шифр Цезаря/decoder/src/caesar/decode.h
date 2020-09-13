/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 13.09.2020
 */

#pragma once

#include <iostream>

namespace caesar {

/**
 * @brief   Decodes input encoded with Caesar's cipher. Uses frequency analysis
 * 
 * @param   stats_input input stream to be analysed for general letters frequency
 * @param   input       encoded input stream
 * @param   output      output stream
 */
void Decode(std::wistream& stats_input, std::wistream& input = std::wcin,
            std::wostream& output = std::wcout);

} // namespace caesar

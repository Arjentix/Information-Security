/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <string>

namespace caesar {

/**
 * @brief   Encode str with shift equals to key
 * 
 * @param   str string to encode
 * @param   key shift of Caesar's algorithm
 * 
 * @return encoded string
 */
std::string Encode(std::string str, int key);

/**
 * @brief   Decode str sifted with key steps
 * 
 * @param   str string to decode
 * @param   key shift of Caesar's algorithm
 * 
 * @return decoded string
 */
std::string Decode(std::string str, int key);

}  // namespace caesar

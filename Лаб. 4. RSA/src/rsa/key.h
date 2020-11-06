/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <utility>
#include <string>

#include "big_integer.h"

namespace rsa {

/**
 * @brief   An RSA private or public key
 */
using Key = std::pair<BigInteger, BigInteger>;

/**
 * @brief   Constructs RSA key from string
 * 
 * @param   str string with key in format <BigInteger, BigInteger>
 * @return  RSA key
 */
Key KeyFromString(const std::string& str);

/**
 * @brief   Converts RSA key to string
 * 
 * @param   key RSA key
 * @return  string in format <BigInteger, BigInteger>
 */
std::string KeyToString(const Key& key);

}  // namespace rsa

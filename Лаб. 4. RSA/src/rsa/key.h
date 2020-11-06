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

using Key = std::pair<BigInteger, BigInteger>;

Key KeyFromString(const std::string& str);

std::string KeyToString(const Key& key);

}  // namespace rsa

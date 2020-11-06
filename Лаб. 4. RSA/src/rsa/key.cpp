/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "key.h"

#include <sstream>

namespace rsa {

Key KeyFromString(const std::string& str) {
    Key key;
    std::istringstream iss(str);

    iss.ignore(1);
    iss >> key.first;
    iss.ignore(2);
    iss >> key.second;

    return key;
}

std::string KeyToString(const Key& key) {
    std::ostringstream oss;
    oss << "<" << key.first << ", " << key.second << ">";

    return oss.str();
}

}  // namespace rsa

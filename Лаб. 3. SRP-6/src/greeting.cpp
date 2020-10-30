/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "greeting.h"

namespace {

std::string greetingMes = "";

}  // namespace

void SetGreeting(const std::string& greeting) {
    greetingMes = greeting;
}

std::string GetGreeting() {
    return greetingMes;
}

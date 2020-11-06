/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "alice.h"

#include <string>

namespace {

/**
 * @brief   Some codes for terminal to provide colors
 */
const std::string kAliceColorCode = "\033[31m";
const std::string kExtraTextColorCode = "\033[90m";
const std::string kNormalColorCode = "\033[0m";

}  // namespace

namespace rsa {

Alice::Alice(sock::Socket& socket, std::ostream& log_stream) :
Communicant(socket, log_stream) {}

void Alice::Communicate() {
    SetGreeting(kAliceColorCode + "Alice: " + kNormalColorCode);

    Key bob_public_key = KeyFromString(ReadAndConfirm(1024));

    std::string mes;
    std::cout << "Enter message: ";
    std::getline(std::cin, mes);
    SendAndLog(Encrypt(mes, bob_public_key));
}

}  // namespace rsa

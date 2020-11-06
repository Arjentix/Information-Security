/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "bob.h"

namespace {

/**
 * @brief   Some codes for terminal to provide colors
 */
const std::string kBobColorCode = "\033[36m";
const std::string kExtraTextColorCode = "\033[90m";
const std::string kNormalColorCode = "\033[0m";

}  // namespace

namespace rsa {

Bob::Bob(sock::Socket& socket, std::ostream& log_stream) :
Communicant(socket, log_stream) {}

void Bob::Communicate() {
    SetGreeting(kBobColorCode + "Bob: " + kNormalColorCode);

    auto [private_key, public_key] = GenerateKeys();

    SendAndLog(KeyToString(public_key));
    const int32_t kCharCount = 32'768;
    std::string mes = Decrypt(ReadAndConfirm(kCharCount), private_key);
    std::cout << GetGreeting() << kExtraTextColorCode << "[Got message '"
              << mes << "']" << kNormalColorCode << std::endl;
}

}  // namespace rsa

/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "communicant.h"

#include <utility>
#include <thread>
#include <tuple>
#include <sstream>

#include "ng.h"

namespace {
    const std::string kConfirmationMessage = "OK";
    const std::string kEndMessage = "END";

    const std::pair<int, int> kNAndGPair = GenerateNAndG();
}  // namespace

const srp_6::Communicant::BigInteger srp_6::Communicant::_N = kNAndGPair.first;
const srp_6::Communicant::BigInteger srp_6::Communicant::_g = kNAndGPair.second;
const srp_6::Communicant::BigInteger srp_6::Communicant::_k =
    srp_6::Communicant::HashArgs(srp_6::Communicant::_N,
                                 srp_6::Communicant::_g);

namespace srp_6 {

EndOfCommunicationException::EndOfCommunicationException(const char* what):
std::runtime_error(what) {}

Communicant::Communicant(sock::Socket& socket, std::ostream& log_stream) :
_log_stream(log_stream),
_socket(socket),
_greeting("") {}

std::string Communicant::BigIntegerToString(const BigInteger& i) {
    std::ostringstream oss;
    oss << i;
    return oss.str();
}
void Communicant::SendAndLog(std::string_view mes) {
    _socket.Send(mes);
    _log_stream << _greeting << mes << std::endl;

    CheckConfirmation();
}

void Communicant::CheckConfirmation() {
    while (_socket.Good()) {
        std::string confirmation = _socket.Read();
        if (confirmation == kConfirmationMessage) {
            return;
        }
        if (confirmation == kEndMessage) {
            throw EndOfCommunicationException(
                "Communicant ended the connection");
        }
    }

    throw std::runtime_error("Can't receive confirmation message");
}

std::string Communicant::Read() {
    std::string str = _socket.Read();
    if (str == kEndMessage) {
        throw EndOfCommunicationException("Communicant ended the connection");
    }

    return str;
}
std::string Communicant::ReadAndConfirm() {
    std::string str = Read();
    Confirm();

    return str;
}

void Communicant::Confirm() {
    _socket.Send(kConfirmationMessage);
}

void Communicant::EndCommunication() {
    _socket.Send(kEndMessage);
}

std::string Communicant::GetGreeting() {
    return _greeting;
}

void Communicant::SetGreeting(std::string greeting) {
    _greeting = std::move(greeting);
}

}  // namespace srp_6

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

namespace srp_6 {

Communicant::Communicant(sock::Socket& socket, std::ostream& log_stream) :
_log_stream(log_stream),
_socket(socket),
_greeting("") {}

void Communicant::SendAndLog(std::string_view mes) {
    _socket.Send(mes);
    _log_stream << _greeting << mes << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    CheckConfirmation();
}

void Communicant::CheckConfirmation() {
    while (_socket.Good()) {
        std::string ok = _socket.Read();
        if (ok == "OK") {
            return;
        }
    }

    throw std::runtime_error("Can't receive OK message");
}

std::string Communicant::ReadAndConfirm() {
    std::string str = _socket.Read();
    Confirm();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    return str;
}

void Communicant::Confirm() {
    _socket.Send("OK");
}

std::string Communicant::GetGreeting() {
    return _greeting;
}

void Communicant::SetGreeting(std::string greeting) {
    _greeting = std::move(greeting);
}

}  // namespace srp_6

/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 25.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "sock.h"

#include <sys/socket.h>
#include <unistd.h>

#include <memory>
#include <stdexcept>
#include <iostream>

namespace sock {

Socket::Socket(const int descriptor) :
_descriptor(descriptor),
_is_good(true) {}

std::string Socket::Read(const int n) {
    std::unique_ptr<char> buf_ptr(new char[n]);
    if (recv(_descriptor, buf_ptr.get(), n, 0) < 0) {
        _is_good = false;
    }

    return std::string(buf_ptr.get());
}

void Socket::Send(std::string_view str) {
    send(_descriptor, str.data(), str.length(), 0);
}

std::pair<Socket, Socket> CreateSocketPair() {
    int sockets_descr[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets_descr) == -1) {
        throw std::runtime_error("Failed to create socket pair");
    }

    return {Socket(sockets_descr[0]), Socket(sockets_descr[1])};
}

}  // namespace sock

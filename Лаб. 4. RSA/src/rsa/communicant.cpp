/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "communicant.h"

#include "big_integer.h"
#include "primes/prime_utils.h"

namespace {

const std::string kConfirmationMessage = "OK";

}  // namespace

namespace rsa {

Communicant::Communicant(sock::Socket& socket, std::ostream& log_stream) :
_socket(socket),
_greeting(""),
_log_stream(log_stream) {}

void Communicant::SendAndLog(std::string_view mes) {
    _socket.Send(mes);
    _log_stream << _greeting << mes << std::endl;

    CheckConfirmation();
}

std::string Communicant::ReadAndConfirm(const int n) {
    std::string str = Read(n);
    Confirm();

    return str;
}

std::string Communicant::GetGreeting() {
    return _greeting;
}

void Communicant::SetGreeting(std::string greeting) {
    _greeting = std::move(greeting);
}

std::pair<Key, Key> Communicant::GenerateKeys() {
    BigInteger p = primes::RandomPrime();
    BigInteger q = primes::RandomPrime();
    BigInteger n = p * q;
    BigInteger phi = (p - 1) * (q - 1);
    BigInteger d = primes::FindRandomCoprime(phi);
    BigInteger e = primes::FindModularMultiplicativeInverse(d, phi);

    return {Key(d, n), Key(e, n)};  // private and public
}

std::string Communicant::Encrypt(std::string_view mes, const Key& key) {
    std::ostringstream oss;
    for (char ch : mes) {
        oss << primes::ModPow(BigInteger(ch),
                              key.first,
                              key.second) << " ";
    }

    return oss.str();
}

std::string Communicant::Decrypt(const std::string& mes, const Key& key) {
    std::ostringstream oss;
    std::istringstream iss(mes);
    while (iss) {
        BigInteger i;
        iss >> i;
        oss << primes::ModPow(i, key.first, key.second).convert_to<char>();
        iss.ignore(1);
    }

    return oss.str();
}


void Communicant::CheckConfirmation() {
    while (_socket.Good()) {
        std::string confirmation = _socket.Read();
        if (confirmation == kConfirmationMessage) {
            return;
        }
    }

    throw std::runtime_error("Can't receive confirmation message");
}

std::string Communicant::Read(const int n) {
    std::string str = _socket.Read(n);

    return str;
}

void Communicant::Confirm() {
    _socket.Send(kConfirmationMessage);
}

}  // namespace rsa

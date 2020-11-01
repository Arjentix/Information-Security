/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "server.h"

#include <string>
#include <sstream>
#include <limits>
#include <thread>

#include "ng.h"

namespace {

/**
 * @brief   Some codes for terminal to provide colors
 */
const std::string kServerColorCode = "\033[36m";
const std::string kExtraTextColorCode = "\033[90m";
const std::string kNormalColorCode = "\033[0m";

std::random_device r;
std::default_random_engine generator(r());

}  // namespace

namespace srp_6 {

Server::Server(sock::Socket& socket, std::ostream& log_stream) :
Communicant(socket, log_stream) {}

void Server::Communicate() {
    SetGreeting("🤖 " + kServerColorCode + "Server: " + kNormalColorCode);

    try {
        RegisterUser();
        LoginUser();
    } catch (EndOfCommunicationException& ex) {
        throw std::runtime_error("Connection was broken by Client");
    }
}

void Server::RegisterUser() {
    using namespace std;

    _username = ReadAndConfirm();
    _salt = ReadAndConfirm();
    _password_verifier = BigInteger(ReadAndConfirm());
    cout << GetGreeting() << kExtraTextColorCode
         << "[Got username = '" << _username
         << "', salt = '" << _salt
         << "', password verifier = " << _password_verifier  << "]"
         << kNormalColorCode << endl;
    Confirm();
}

void Server::LoginUser() {
    using namespace std;

    // First round
    const string username = Read();
    if (username != _username) {
        std::cout << GetGreeting() << "Wrong username!❌" << endl;
        EndCommunication();
        return;
    }
    Confirm();

    const BigInteger A(Read());
    if (A == 0) {
        cout << GetGreeting() << "Wrong Client logging number!❌" << endl;
        EndCommunication();
        return;
    }
    Confirm();

    const uint32_t kMinRandomNumber = 1;
    const uint32_t kMaxRandomNumber = std::numeric_limits<uint32_t>::max();
    uniform_int_distribution<uint32_t> distribution(kMinRandomNumber,
                                                    kMaxRandomNumber);
    const BigInteger b = distribution(generator);
    const BigInteger B = (_k * _password_verifier + ModPow(_g, b, _N)) % _N;
    SendAndLog(_salt);
    SendAndLog(BigIntegerToString(B));

    const BigInteger scrambler = HashArgs(A, B);
    if (scrambler == 0) {
        cout << GetGreeting() << "Wrong scrambler!❌" << endl;
        EndCommunication();
        return;
    }

    const BigInteger S = ModPow(A * ModPow(_password_verifier, scrambler, _N),
                                b, _N);
    const BigInteger K = HashArgs(S);  // key
    CheckConfirmation();
    cout << GetGreeting() << kExtraTextColorCode << "[K = " << K << "]"
         << kNormalColorCode << endl;

    // Second round
    const BigInteger M = HashArgs(HashArgs(_N) ^ HashArgs(_g),
                                  HashArgs(username), _salt, A, B, K);
    Confirm();
    const BigInteger client_M(Read());
    if (M != client_M) {
        cout << GetGreeting() << "Wrong password!❌" << endl;
        EndCommunication();
        return;
    }
    Confirm();

    const BigInteger R = HashArgs(A, M, K);
    CheckConfirmation();
    SendAndLog(BigIntegerToString(R));
}

}  // namespace srp_6

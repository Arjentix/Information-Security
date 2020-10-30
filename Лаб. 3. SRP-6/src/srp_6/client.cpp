/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "client.h"

#include <sstream>
#include <tuple>

#include "ng.h"

namespace {

std::random_device r;
std::default_random_engine generator(r());

std::string RandomString() {
    const int kMinLength = 32;
    const int kMaxLength = 128;
    std::uniform_int_distribution<int> int_distribution(kMinLength, kMaxLength);
    const int str_length = int_distribution(generator);

    const int kAsciiSymbolsStart = 33;
    const int kAsciiSymbolsEnd = 126;
    std::uniform_int_distribution<char> char_distribution(kAsciiSymbolsStart,
                                                            kAsciiSymbolsEnd);

    std::ostringstream oss;
    for (int i = 0; i < str_length; ++i) {
        oss << char_distribution(generator);
    }

    return oss.str();
}

}  // namespace

namespace srp_6 {

Client::Client(sock::Socket& socket, std::ostream& log_stream) :
Communicant(socket, log_stream) {
    std::tie(_N, _g) = GenerateNAndG();
}

void Client::Communicate() {
    SetGreeting("🦊 You: ");
    RegisterUser();
    // LoginUser();
}

void Client::RegisterUser() {
    using namespace std;

    SendAndLog(to_string(_N));
    SendAndLog(to_string(_g));

    CheckConfirmation();
    string username;
    cout << "📖 Registration\nEnter username: ";
    cin >> username;
    SetGreeting("🦊 " + username + ": ");

    string password;
    cout << "Enter password🔑 : ";
    cin >> password;

    const string salt = RandomString();
    const int x = HashArgs(salt, password);
    const int password_verifier = ModPow(_g, x, _N);

    SendAndLog(username);
    SendAndLog(salt);
    SendAndLog(to_string(password_verifier));
}

}  // namespace srp_6

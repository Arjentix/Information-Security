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

/**
 * @brief   Some codes for terminal to provide colors
 */
const std::string kClientColorCode = "\033[31m";
const std::string kExtraTextColorCode = "\033[90m";
const std::string kNormalColorCode = "\033[0m";

std::random_device r;
std::default_random_engine generator(r());

/**
 * @brief   Generate random string of length in range [32, 128]
 * 
 * @return  random string
 */
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
Communicant(socket, log_stream) {}

void Client::Communicate() {
    SetGreeting("🦊 You: ");

    std::cout << "Using N = " << _N << ", g = " << _g
              << ", k = " << _k << std::endl;

    try {
        RegisterUser();
        LoginUser();
    } catch (EndOfCommunicationException& ex) {
        throw std::runtime_error("Connection was broken by Server");
    }
}

void Client::RegisterUser() {
    using namespace std;

    string username;
    cout << "\n📖 Registration\nEnter username: ";
    cin >> username;
    SetGreeting("🦊 " + kClientColorCode + username + ": " + kNormalColorCode);

    string password;
    cout << "🔑 Enter password: ";
    cin >> password;

    const string salt = RandomString();
    const BigInteger x = HashArgs(salt, password);
    const BigInteger password_verifier = ModPow(_g, x, _N);

    SendAndLog(username);
    SendAndLog(salt);
    SendAndLog(BigIntegerToString(password_verifier));
}

void Client::LoginUser() {
    using namespace std;

    // First round
    CheckConfirmation();
    string username;
    cout << "\n🚪 Logging\nEnter username: ";
    cin >> username;
    SetGreeting("🦊 " + kClientColorCode + username + ": " + kNormalColorCode);

    const uint32_t kMinRandomNumber = 1;
    const uint32_t kMaxRandomNumber = std::numeric_limits<uint32_t>::max();
    uniform_int_distribution<uint32_t> distribution(kMinRandomNumber,
                                                    kMaxRandomNumber);
    const BigInteger a = distribution(generator);
    const BigInteger A = ModPow(_g, a, _N);
    SendAndLog(username);
    SendAndLog(BigIntegerToString(A));

    const string salt = ReadAndConfirm();
    const BigInteger B(Read());
    if (B == 0) {
        cout << GetGreeting() << "❌ Wrong Server logging number!" << endl;
        EndCommunication();
        return;
    }
    Confirm();

    const BigInteger scrambler = HashArgs(A, B);
    if (scrambler == 0) {
        cout << GetGreeting() << "❌ Wrong scrambler!" << endl;
        EndCommunication();
        return;
    }

    string password;
    cout << "🔑 Enter password: ";
    cin >> password;

    const BigInteger x = HashArgs(salt, password);
    const BigInteger S = ModPow(B - _k * ModPow(_g, x, _N),
                                BigInteger(a + scrambler*x),
                                _N);
    const BigInteger K = HashArgs(S);  // key
    cout << GetGreeting() << kExtraTextColorCode << "[K = " << K << "]"
         << kNormalColorCode << endl;
    Confirm();

    // Second round
    const BigInteger M = HashArgs(HashArgs(_N) ^ HashArgs(_g),
                                  HashArgs(username), salt, A, B, K);
    CheckConfirmation();
    SendAndLog(BigIntegerToString(M));

    const BigInteger R = HashArgs(A, M, K);
    Confirm();
    const BigInteger server_R(Read());
    if (R != server_R) {
        EndCommunication();
        return;
    }
    Confirm();

    cout << "\n✅ You was successfully logged in!" << endl;
}

}  // namespace srp_6

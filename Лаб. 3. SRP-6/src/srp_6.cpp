/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "srp_6.h"

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <thread>
#include <utility>

#include "greeting.h"
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

uint32_t HashArgs() {
    return 0;
}

template <typename Arg1, typename... Args>
uint32_t HashArgs(const Arg1& arg1, const Args&... args) {
    const int p = 31;

    return p * std::hash<Arg1>()(arg1) + p * HashArgs(args...);
}

void Confirm(sock::Socket& socket) {
    socket.Send("OK");
}

std::string ReadAndConfirm(sock::Socket& socket) {
    std::string str = socket.Read();
    Confirm(socket);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    return str;
}

/**
 * @brief   Check if companion has send OK message otherwise throws a runtime_error 
 * 
 * @param   socket  socket to read message
 */
void CheckConfirmation(sock::Socket& socket) {
    while (socket.Good()) {
        std::string ok = socket.Read();
        if (ok == "OK") {
            return;
        }
    }

    throw std::runtime_error("Can't receive OK message");
}

/**
 * @brief   Send message to the socket and logs it to the os with leading greeting
 * 
 * @param   socket  socket to send message
 * @param   mes     message to be sended
 * @param   os      logging output stream
 */
void SendAndLog(sock::Socket& socket, std::string_view mes, std::ostream& os) {
    socket.Send(mes);
    os << GetGreeting() << mes << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    CheckConfirmation(socket);
}

/**
 * @brief   Compute base^exp % modulus expression
 * 
 * @param   base    number to be powered
 * @param   exp     power degree
 * @param   modulus modulus
 * 
 * @return  the result of base^exp % modulus
 */
template <typename T>
T ModPow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }

    return result;
}

void RegisterUser(sock::Socket& socket) {
    using namespace std;

    const auto [N, g] = GenerateNAndG();
    SendAndLog(socket, to_string(N), cout);
    SendAndLog(socket, to_string(g), cout);

    CheckConfirmation(socket);
    string username;
    cout << "Enter username: ";
    cin >> username;
    SetGreeting("🦊 " + username + ": ");

    string password;
    cout << "Enter password🔑 : ";
    cin >> password;

    const string salt = RandomString();
    const int x = HashArgs(salt, password);
    const int password_verifier = ModPow(g, x, N);

    SendAndLog(socket, username, cout);
    SendAndLog(socket, salt, cout);
    SendAndLog(socket, to_string(password_verifier), cout);
}

}  // namespace

namespace srp_6 {

void RunClient(sock::Socket& socket) {
    SetGreeting("🦊 You: ");
    RegisterUser(socket);
    // LoginUser(socket);
}

void RunServer(sock::Socket& socket) {
    SetGreeting("🤖 Server: ");

    const int N = atoi(ReadAndConfirm(socket).c_str());
    const int g = atoi(ReadAndConfirm(socket).c_str());
    std::cout << GetGreeting() << "Got N = " << N
              << ", g = " << g << std::endl;
    Confirm(socket);

    std::string username = ReadAndConfirm(socket);
    std::string salt = ReadAndConfirm(socket);
    int password_verifier = atoi(ReadAndConfirm(socket).c_str());
    std::cout << GetGreeting() << "Got username = '" << username
              << "', salt = '" << salt
              << "', password verifier = " << password_verifier << std::endl;
}

}  // namespace srp_6

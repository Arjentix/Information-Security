/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 26.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "alice_and_bob.h"

#include <iostream>
#include <utility>
#include <string>
#include <tuple>
#include <random>
#include <thread>
#include <cstdint>
#include <cctype>

#include "pg.h"

using namespace std;

namespace {

const int kMaxSecretKey = 1000;

string greeting = "";

random_device r;
default_random_engine generator(r());

/**
 * @brief   Gets random p in g according to Diffie-Hellman rules
 * 
 * @return  pair of p and g numbers
 */
pair<int, int> GetRandomPAndG() {
    uniform_int_distribution<int> distribution(0, pg.size() - 1);

    return pg[distribution(generator)];
}

/**
 * @brief   Generates random secret key in range [0, kMaxSecretKey]
 * 
 * @return  integer secret key
 */
int GenerateSecretKey() {
    uniform_int_distribution<int>
        natural_distribution(0, kMaxSecretKey);

    return natural_distribution(generator);
}

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

/**
 * @brief   Send message to the socket and logs it to the os with leading greeting
 * 
 * @param   socket  socket to send message
 * @param   mes     message to be sended
 * @param   os      logging output stream
 */
void SendAndLog(sock::Socket& socket, string_view mes, ostream& os) {
    socket.Send(mes);
    os << greeting << mes << endl;
    this_thread::sleep_for(chrono::milliseconds(20));
}

void AssertOk(sock::Socket& socket) {
    while (socket.Good()) {
        const string ok = socket.Read();
        if (ok == "OK") {
            return;
        }
    }

    throw runtime_error("Can't receive OK message");
}

string Encode(string str, const int key) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalpha(str[i])) {
            continue;
        }

        int k = key % 26;

        if (isupper(str[i])) {
            str[i] += k;
            if (str[i] > 'Z') {
                str[i] = 'A' + (str[i] - 'Z') - 1;
            }
        } else {
            if ((str[i] + k > 'z') || (str[i] + k < 'a')) {
                k -= 'z' - str[i];
                str[i] = 'a' + k - 1;
            } else {
                str[i] += k;
            }
        }
    }

    return str;
}

string Decode(string str, const int key) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isalpha(str[i])) {
            continue;
        }

        char enc = str[i] - key % 26;
        if (isupper(str[i])) {
            if (enc < 'A') {
                enc = 'Z' - (('A' - enc) - 1);
            }
        } else {
            if (enc < 'a') {
                enc = 'z' - (('a' - enc) - 1);
            }
        }

        str[i] = enc;
    }

    return str;
}

}  // namespace

namespace alice_and_bob {

void RunAlice(sock::Socket& socket) {
    greeting = "👩 Alice: ";
    int p;
    int g;
    tie(p, g) = GetRandomPAndG();
    cout << greeting << "[p = " << p << ", g = " << g << "]" << endl;
    SendAndLog(socket, to_string(p), cout);
    AssertOk(socket);
    SendAndLog(socket, to_string(g), cout);
    AssertOk(socket);

    int a = GenerateSecretKey();
    cout << greeting << "[a = " << a << "]" << endl;

    int A = ModPow(g, a, p);
    cout << greeting << "[A = " << A << "]" << endl;
    SendAndLog(socket, to_string(A), cout);
    AssertOk(socket);

    string str = socket.Read();
    SendAndLog(socket, "OK", cout);
    int B = atoi(str.c_str());
    cout << greeting << "[Received: B = " << B << "]" << endl;

    int K = ModPow(B, a, p);
    cout << greeting << "[🔑 K = " << K << "]" << endl;

    this_thread::sleep_for(chrono::milliseconds(10));
    while (socket.Good()) {
        cout << greeting;
        getline(cin, str);
        if (str == "END") {
            socket.Send(str);
            break;
        }
        socket.Send(Encode(str, K));

        this_thread::sleep_for(chrono::milliseconds(10));

        str = socket.Read();
        if (str == "END") {
            break;
        }
        cout << greeting << "[Received: \"" << str
             << "\", decoded: " << Decode(str, K) << "]" << endl;
    }
}

void RunBob(sock::Socket& socket) {
    greeting = "👨 Bob: ";
    string str = socket.Read();
    int p = atoi(str.c_str());
    SendAndLog(socket, "OK", cout);

    str = socket.Read();
    SendAndLog(socket, "OK", cout);
    int g = atoi(str.c_str());
    cout << greeting << "[Received: p = " << p << ", g = " << g << "]" << endl;

    int b = GenerateSecretKey();
    cout << greeting << "[b = " << b << "]" << endl;

    str = socket.Read();
    SendAndLog(socket, "OK", cout);
    int A = atoi(str.c_str());
    cout << greeting << "[Received: A = " << A << "]" << endl;

    int B = ModPow(g, b, p);
    cout << greeting << "[B = " << B << "]" << endl;
    SendAndLog(socket, to_string(B), cout);
    AssertOk(socket);

    int K = ModPow(A, b, p);
    cout << greeting << "[🔑 K = " << K << "]" << endl;

    while (socket.Good()) {
        str = socket.Read();
        if (str == "END") {
            break;
        }
        cout << greeting << "[Received: \"" << str
             << "\", decoded: " << Decode(str, K) << "]" << endl;

        cout << greeting;
        getline(cin, str);
        if (str == "END") {
            socket.Send(str);
            break;
        }
        socket.Send(Encode(str, K));

        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

}  // namespace alice_and_bob

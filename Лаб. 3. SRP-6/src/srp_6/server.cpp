/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include "server.h"

#include <sstream>
#include <tuple>

#include "ng.h"

namespace {

std::random_device r;
std::default_random_engine generator(r());

}  // namespace

namespace srp_6 {

Server::Server(sock::Socket& socket, std::ostream& log_stream) :
Communicant(socket, log_stream) {}

void Server::Communicate() {
    RegisterUser();
    // LoginUser();
}

void Server::RegisterUser() {
    using namespace std;
    SetGreeting("🤖 Server: ");

    const int N = atoi(ReadAndConfirm().c_str());
    const int g = atoi(ReadAndConfirm().c_str());
    cout << GetGreeting() << "Got N = " << N
         << ", g = " << g << endl;
    Confirm();

    string username = ReadAndConfirm();
    string salt = ReadAndConfirm();
    int password_verifier = atoi(ReadAndConfirm().c_str());
    cout << GetGreeting() << "Got username = '" << username
         << "', salt = '" << salt
         << "', password verifier = " << password_verifier << std::endl;
}

void Server::LoginUser() {
    using namespace std;
}

}  // namespace srp_6

/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 25.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "sock.h"
#include "alice_and_bob.h"

int main() {
    using namespace std;

    try {
        auto sockets = sock::CreateSocketPair();

        int fork_res = fork();
        if (fork_res < 0) {
            throw std::runtime_error("Failed to fork");
        }

        if (fork_res == 0) {  // Child
            alice_and_bob::RunAlice(sockets.first);
        } else {  // Parent
            alice_and_bob::RunBob(sockets.second);
        }
    } catch (std::exception& err) {
        cerr << err.what() << endl;
        return -1;
    } catch (...) {
        cerr << "Undefined error" << endl;
        return -2;
    }

    return 0;
}

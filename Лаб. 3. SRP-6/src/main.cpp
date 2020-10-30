/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "sock.h"
#include "srp_6.h"

int main() {
    using namespace std;

    try {
        auto sockets = sock::CreateSocketPair();

        int fork_res = fork();
        if (fork_res < 0) {
            throw std::runtime_error("Failed to fork");
        }

        if (fork_res == 0) {  // Child
            srp_6::RunClient(sockets.first);
        } else {  // Parent
            srp_6::RunServer(sockets.second);
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

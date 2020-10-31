/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <random>
#include <string>

#include "communicant.h"

namespace srp_6 {

class Server : public Communicant {
 public:
    Server(sock::Socket& socket, std::ostream& log_stream = std::cout);

    void Communicate() override;

 private:
    std::string _username;
    std::string _salt;
    BigInteger _password_verifier;

    void RegisterUser();
    void LoginUser();
};

}  // namespace srp_6

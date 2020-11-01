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
    /**
     * @brief   Construct a new Server object
     * 
     * @param   socket      socket to transfer and receive data
     * @param   log_stream  stream to log information
     */
    Server(sock::Socket& socket, std::ostream& log_stream = std::cout);

    /**
     * @brief   Run SRP-6 communication demonstration for Server side
     */
    void Communicate() override;

 private:
    std::string _username;
    std::string _salt;
    BigInteger _password_verifier;

    /**
     * @brief   Register user on the Server
     */
    void RegisterUser();

    /**
     * @brief   Login user on the Server
     */
    void LoginUser();
};

}  // namespace srp_6

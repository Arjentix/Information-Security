/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <random>

#include "communicant.h"

namespace srp_6 {

class Client : public Communicant {
 public:
    /**
     * @brief   Construct a new Client object
     * 
     * @param   socket      socket to transfer and receive data
     * @param   log_stream  stream to log information
     */
    Client(sock::Socket& socket, std::ostream& log_stream = std::cout);

    /**
     * @brief   Run SRP-6 communication demonstration for Client side
     */
    void Communicate() override;

 private:
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

/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <random>
#include <string>

#include "communicant.h"

namespace rsa {

class Bob : public Communicant {
 public:
    /**
     * @brief   Construct a new Bob object
     * 
     * @param   socket      socket to transfer and receive data
     * @param   log_stream  stream to log information
     */
    Bob(sock::Socket& socket, std::ostream& log_stream = std::cout);

    /**
     * @brief   Run SRP-6 communication demonstration for Bob side
     */
    void Communicate() override;

 private:
};

}  // namespace rsa

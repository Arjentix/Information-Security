/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 03.11.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <random>

#include "communicant.h"

namespace rsa {

class Alice : public Communicant {
 public:
    /**
     * @brief   Construct a new Alice object
     * 
     * @param   socket      socket to transfer and receive data
     * @param   log_stream  stream to log information
     */
    Alice(sock::Socket& socket, std::ostream& log_stream = std::cout);

    /**
     * @brief   Run SRP-6 communication demonstration for Alice side
     */
    void Communicate() override;

 private:
};

}  // namespace rsa

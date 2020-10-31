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
    Client(sock::Socket& socket, std::ostream& log_stream = std::cout);

    void Communicate() override;

 private:
    void RegisterUser();
    void LoginUser();
};

}  // namespace srp_6

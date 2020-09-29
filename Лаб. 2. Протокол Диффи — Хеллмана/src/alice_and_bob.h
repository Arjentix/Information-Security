/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 25.09.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include "sock.h"

namespace alice_and_bob {

/**
 * @brief   Run Alice sequence. Alice generates p and g
 * 
 * @param   socket  socket to write and receive data from Bob
 */
void RunAlice(sock::Socket& socket);

/**
 * @brief   Run Bob sequence
 * 
 * @param   socket  socket to write and receive data from Alice
 */
void RunBob(sock::Socket& socket);

}  // namespace alice_and_bob

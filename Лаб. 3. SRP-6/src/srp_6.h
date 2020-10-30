/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 29.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include "sock.h"

namespace srp_6 {

/**
 * @brief   Run Client sequence.
 * 
 * @details Asks user for username and password, registers it on the Server.
 *          Then again asks user for username and password and tries to login on
 *          the Server.
 * 
 * @param   socket  socket to write and receive data from Server
 */
void RunClient(sock::Socket& socket);

/**
 * @brief   Run Server sequence.
 * 
 * @param   socket  socket to write and receive data from Client
 */
void RunServer(sock::Socket& socket);

}  // namespace srp_6

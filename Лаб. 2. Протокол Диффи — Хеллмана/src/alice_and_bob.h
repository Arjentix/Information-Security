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

void RunAlice(sock::Socket& socket);
void RunBob(sock::Socket& socket);

}  // namespace alice_and_bob

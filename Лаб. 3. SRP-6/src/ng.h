/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#include <vector>
#include <utility>

#pragma once

/**
 * @brief   Generates N and g numbers for SRP-6 algorithm
 * 
 * @return  pair of N and g
 */
std::pair<int, int> GenerateNAndG();

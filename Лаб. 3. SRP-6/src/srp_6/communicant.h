/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 30.10.2020
 * @copyright: Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>

#include "sock/socket.h"
#include <boost/multiprecision/cpp_int.hpp>

namespace srp_6 {

class EndOfCommunicationException : public std::runtime_error {
 public:
    explicit EndOfCommunicationException(const char* what);
};

class Communicant {
 public:
    Communicant(sock::Socket& socket, std::ostream& log_stream = std::cout);

    virtual void Communicate() = 0;

 protected:
    using BigInteger = boost::multiprecision::cpp_int;

    static const BigInteger _N;
    static const BigInteger _g;
    static const BigInteger _k;
    std::ostream& _log_stream;

    std::string BigIntegerToString(const BigInteger& i);

    /**
     * @brief   Send message to the socket and logs it to the os with leading greeting
     * 
     * @param   mes     message to be sended
     */
    void SendAndLog(std::string_view mes);

    /**
     * @brief   Check if companion has send OK message otherwise throws a runtime_error 
     * 
     * @param   socket  socket to read message
     */
    void CheckConfirmation();

    std::string Read();

    std::string ReadAndConfirm();

    void Confirm();

    void EndCommunication();

    std::string GetGreeting();

    void SetGreeting(std::string greeting);

    inline static uint32_t HashArgs() {
       return 0;
    }

    template <typename Arg1, typename... Args>
    static uint32_t HashArgs(const Arg1& arg1, const Args&... args) {
       const int p = 31;

       return p * std::hash<Arg1>()(arg1) + p * HashArgs(args...);
    }

   /**
    * @brief   Compute base^exp % modulus expression
    * 
    * @param   base    number to be powered
    * @param   exp     power degree
    * @param   modulus modulus
    * 
    * @return  the result of base^exp % modulus
    */
    template <typename T>
    T ModPow(T base, T exp, T modulus) {
        base %= modulus;
        T result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = (result * base) % modulus;
            }
            base = (base * base) % modulus;
            exp >>= 1;
        }

        if (result < 0) {
            result = modulus + result;
        }

        return result;
    }

 private:
    sock::Socket& _socket;
    std::string _greeting;
};

}  // namespace srp_6

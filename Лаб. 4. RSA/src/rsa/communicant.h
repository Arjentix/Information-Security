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
#include <utility>

#include "sock/socket.h"
#include "key.h"

namespace rsa {

class Communicant {
 public:
    Communicant(sock::Socket& socket, std::ostream& log_stream = std::cout);

    virtual void Communicate() = 0;

 protected:
    /**
     * @brief   Send message to the socket, log it with leading greeting and check confirmation from the other side
     * 
     * @details Waits from confirmation after sending message
     * 
     * @param   mes     message to be sended
     */
    void SendAndLog(std::string_view mes);

    /**
     * @brief   Read() and Confirm() together
     * 
     * @see     Read(), Confirm()
     * 
     * @param  n  number of characters to read
     * 
     * @return  read string
     */
    std::string ReadAndConfirm(int n = 256);

    /**
     * @brief   Get greeting message
     * 
     * @return  string with greeting message
     */
    std::string GetGreeting();

    /**
     * @brief   Set the Greeting message
     * 
     * @param   greeting    message with greeting
     */
    void SetGreeting(std::string greeting);


    std::pair<Key, Key> GenerateKeys();

    std::string Encrypt(std::string_view mes, const Key& key);
    std::string Decrypt(const std::string& mes, const Key& key);

 private:
    sock::Socket& _socket;
    std::string _greeting;
    std::ostream& _log_stream;

    /**
     * @brief   Check if companion has send OK message
     * 
     * @throw   std::runtime_error if received some other message
     * 
     * @param   socket  socket to read message
     */
    void CheckConfirmation();

    /**
     * @brief   Read message from socket
     * 
     * @param  n  number of characters to read
     * 
     * @return  read string
     */
    std::string Read(int n);

    /**
     * @brief   Send confirmation message
     */
    void Confirm();
};

}  // namespace rsa

/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 25.09.2020
 * @copyright Copyright 2020 Polyakov Daniil
 */

#pragma once

#include <string>
#include <string_view>
#include <utility>

namespace sock {

class Socket {
 public:
    /**
     * @brief   Reads n chars
     * 
     * @param   n   number of chars to read. Default is 256
     * 
     * @return  string with n chars
     */
    std::string Read(int n = 256);

    /**
     * @brief   Sends string
     * 
     * @param   str string to send
     */
    void Send(std::string_view str);


    /**
     * @brief   Check if socket is good
     * 
     * @return  true if good and false otherwise
     */
    inline bool Good() const {
        return _is_good;
    }

 private:
  /**
     * @param   descriptor  socket descriptor
     */
  explicit Socket(int descriptor);

  friend std::pair<Socket, Socket> CreateSocketPair();

  int _descriptor;
  bool _is_good;
};

/**
 * @brief   Creates Unix domain sockets that can handle bi-directional data
 * 
 * @return  pair of sockets. Data written to one of them can be read from other
 */
std::pair<Socket, Socket> CreateSocketPair();

}  // namespace sock

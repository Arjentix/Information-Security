cmake_minimum_required(VERSION 3.10.0)
project(rsa VERSION 0.1.0)

set(THIS rsa)

set(SOURCE
    src/main.cpp
    src/sock/socket.cpp
    src/primes/prime_utils.cpp
    src/rsa/key.cpp
    src/rsa/communicant.cpp
    src/rsa/alice.cpp
    src/rsa/bob.cpp
)

set(BUILD_FLAGS "-Wall -Wextra -pedantic -Werror")
set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin")

find_package(Boost REQUIRED)

add_executable(${THIS} ${SOURCE})

target_include_directories(${THIS} PUBLIC
  "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(${THIS} PRIVATE Boost::headers)

set_target_properties(${THIS} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
  COMPILE_FLAGS ${BUILD_FLAGS}
)

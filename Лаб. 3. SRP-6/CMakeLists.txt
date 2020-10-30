cmake_minimum_required(VERSION 3.10.0)
project(srp_6 VERSION 0.1.0)

set(THIS srp_6)

set(SOURCE
    src/main.cpp
    src/sock/socket.cpp
    src/srp_6/communicant.cpp
    src/srp_6/client.cpp
    src/srp_6/server.cpp
    src/srp_6/ng.cpp
)

set(BUILD_FLAGS "-Wall -Wextra -pedantic -Werror")

set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin")

add_executable(${THIS} ${SOURCE})

target_include_directories(${THIS} PUBLIC
  "${PROJECT_SOURCE_DIR}/src"
)

set_target_properties(${THIS} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
  COMPILE_FLAGS ${BUILD_FLAGS}
)

cmake_minimum_required(VERSION 3.10.0)

set(THIS decoder)

set(SOURCE
    src/main.cpp
    src/caesar/decode.cpp
    src/caesar/russian.cpp
)

set(BUILD_FLAGS "-Wall -Wextra -pedantic -Werror")

set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin")

add_executable(${THIS} ${SOURCE})

set_target_properties(${THIS} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
  COMPILE_FLAGS ${BUILD_FLAGS}
)

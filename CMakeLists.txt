cmake_minimum_required(VERSION 3.13)
project(TpCppM1S1)

set(CMAKE_CXX_STANDARD 17)
set(SRC_PATH src/)

set(SRCS
        ${SRC_PATH}/main.cpp
        ${SRC_PATH}/Program.cpp
        ${SRC_PATH}/Expr.cpp
        ${SRC_PATH}/Token.cpp)

set(HEADERS
        ${SRC_PATH}/Program.hpp
        ${SRC_PATH}/Expr.hpp
        ${SRC_PATH}/Token.hpp)

add_executable(TpCppM1S1 ${SRCS} ${HEADERS})
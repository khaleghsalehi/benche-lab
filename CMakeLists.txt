cmake_minimum_required(VERSION 3.21)
project(parraller C)

set(CMAKE_C_STANDARD 11)

add_executable(parraller
        src/benchmark.c
        src/benchmark.h
        src/lib/safe/util.h
        src/lib/modbus/connection.h)

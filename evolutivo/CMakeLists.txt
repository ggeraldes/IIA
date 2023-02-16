cmake_minimum_required(VERSION 3.24)
project(evolutivo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(evolutivo
        algoritmo.c
        algoritmo.h
        main.c
        utils.c
        utils.h
        funcao.c
        funcao.h)
